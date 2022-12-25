#include "ClockBase.hpp"

ClockBase::ClockBase(TFT_eSPI *tft, const char *id) : BaseComponent(tft, id)
{
  strcpy(_server, "ntp0.ntp-servers.net");
  _shouldRedraw = true;
  _isReady = true;
}

ClockBase::~ClockBase()
{
  releaseTimeClient();
  if (_wifi)
    _wifi->removeDelegate(_wifiDelegateId);
}

long ClockBase::secondsToNext(int hr, int mn, int sc)
{
  int currentSec = (hour() * SECS_PER_HOUR) + (minute() * SECS_PER_MIN) + (second());
  int desiredSec = (hr * SECS_PER_HOUR) + (mn * SECS_PER_MIN) + (sc);

  if (currentSec == desiredSec)
    return 0;
  else if (desiredSec > currentSec)
    return desiredSec - currentSec;

  return ((SECS_PER_DAY - currentSec) + desiredSec);
}

long ClockBase::secondsToAlarm(ClockAlarm alarm)
{
  return secondsToNext(alarm.hour, alarm.minute, alarm.second);
}

void ClockBase::setManualTime(int h, int m, int s, int day, int month, int year)
{
  releaseTimeClient();
  setTime(h, m, s, day, month, year);
  _manual = true;
  _started = true;
  _shouldRedraw = true;
}

void ClockBase::setAutomaticTime()
{
  _manual = false;
  _shouldRedraw = true;
}

void ClockBase::setWiFi(WiFiConnection *wifi)
{
  _wifi = wifi;
  if (_wifi)
    _wifiDelegateId = _wifi->setDelegate(this, _id);
}

void ClockBase::startTimeClient()
{
  if (_timeClient)
    releaseTimeClient();

  if (_wifi && _wifi->isConnected() && !_manual)
  {
    _timeClient = new NTPClient(_ntpUDP, _server, _offset, _updateInterval);
    _timeClient->end();
    _timeClient->begin();
  }

  _started = true;
}

void ClockBase::releaseTimeClient()
{
  if (_timeClient)
  {
    _timeClient->end();
    delete _timeClient;
    _timeClient = NULL;
  }
  _started = false;
}

void ClockBase::setNTPServer(const char *serverName)
{
  releaseTimeClient();
  strcpy(_server, serverName);
}

void ClockBase::setUpdateInterval(unsigned long updateInterval)
{
  releaseTimeClient();
  _updateInterval = updateInterval;
}

unsigned long ClockBase::getCurrentTime()
{
  return now();
}

void ClockBase::setOffset(long offset)
{
  releaseTimeClient();
  _offset = offset;
}

void ClockBase::setDelegate(ClockInterface *delegate)
{
  _delegate = delegate;
}

timer_struct *ClockBase::addTimer(ClockTimer timer, const char *description)
{
  size_t id = _alarmTimerCounter;

  timer_struct newTimer;
  newTimer.id = id;
  strcpy(newTimer.description, description);
  newTimer.timer = timer;
  newTimer.timer.lastTime = now();

  _timers.push_back(newTimer);

  _alarmTimerCounter++;
  return &_timers[id];
}

alarm_struct *ClockBase::addAlarm(ClockAlarm alarm, const char *description)
{
  size_t id = _alarmTimerCounter;

  alarm_struct newAlarm;
  newAlarm.id = id;
  strcpy(newAlarm.description, description);
  newAlarm.alarm = alarm;
  newAlarm.alarm.triggered = false;
  newAlarm.alarm.lastTime = now();

  _alarms.push_back(newAlarm);

  _alarmTimerCounter++;
  return &_alarms[id];
}

void ClockBase::updateAlarm(size_t id, ClockAlarm alarm)
{
  bool found = false;
  size_t i = 0;
  for (i = 0; i < _alarms.size(); i += 1)
  {
    if (_alarms[i].id == id)
    {
      found = true;
      break;
    }
  }
  if (!found)
    return;

  _alarms[i].alarm = alarm;
}

void ClockBase::removeTimer(size_t id)
{
  for (size_t i = 0; i < _timers.size(); i += 1)
  {
    if (_timers[i].id == id)
    {
      _timers.erase(_timers.begin() + i);
      break;
    }
  }
}

void ClockBase::removeAlarm(size_t id)
{
  for (size_t i = 0; i < _alarms.size(); i += 1)
  {
    if (_alarms[i].id == id)
    {
      _alarms.erase(_alarms.begin() + i);
      break;
    }
  }
}

void ClockBase::processTimersAndAlarms()
{
  if (!_delegate)
    return;

  time_t current = now();
  for (size_t i = 0; i < _timers.size(); i += 1)
  {
    ClockTimer *timer = &_timers[i].timer;
    if (!timer->isActive)
      continue;

    if (current - timer->lastTime >= timer->interval)
    {
      timer->lastTime = current;
      _delegate->onClockTimer(_id, &_timers[i]);
      if (!timer->repeat)
        timer->isActive = false;
    }
  }

  for (size_t i = 0; i < _alarms.size(); i += 1)
  {
    ClockAlarm *alarm = &_alarms[i].alarm;
    if (!alarm->isActive)
      continue;

    bool done = alarm->triggered && current - alarm->lastTime >= alarm->duration;
    if (alarm->lastTime != now() && (secondsToAlarm((*alarm)) <= 0 || done))
    {
      alarm->lastTime = now();
      alarm->triggered = !done;
      _delegate->onClockAlarm(_id, &_alarms[i], done);
      if (!alarm->repeat && done)
        alarm->isActive = false;
    }
  }
}

void ClockBase::setPosition(int16_t x, uint16_t y)
{
  _x = x;
  _y = y;
  _shouldRedraw = true;
}

void ClockBase::updateState()
{
  if (!_isReady)
    return;

  if (!_started)
  {
    startTimeClient();
    return;
  }

  if (!_manual && _wifi && _wifi->isConnected() && _timeClient->update())
    setTime(_timeClient->getEpochTime());

  _h = hour();
  _m = minute();
  _s = second();

  processTimersAndAlarms();
  updateClockState();
}

// Interface
void ClockBase::onWiFiEvent(arduino_event_id_t event)
{
  Serial.print(_id);
  Serial.print(" --> WiFi Event: ");
  Serial.println(_wifi->getEventDescription(event));
  startTimeClient();
  _shouldRedraw = true;
}
