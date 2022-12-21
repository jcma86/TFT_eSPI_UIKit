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

size_t ClockBase::addTimer(long intervalInSeconds, bool repeat)
{
  size_t id = _timers.size();
  timer_struct timer;
  timer.id = id;
  timer.interval = intervalInSeconds;
  timer.repeat = repeat;
  timer._lastTime = millis() / 1000;
  _timers.push_back(timer);
  return id;
}

size_t ClockBase::addAlarm(ClockAlarm alarm, bool repeat)
{
  size_t id = _alarms.size();
  alarm_struct newAlarm;
  newAlarm.id = id;
  newAlarm.alarm.hour = alarm.hour;
  newAlarm.alarm.minute = alarm.minute;
  newAlarm.alarm.second = alarm.second;
  newAlarm.repeat = repeat;
  newAlarm._lastTime = 0;

  _alarms.push_back(newAlarm);
  return id;
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

  unsigned long mi = millis() / 1000;
  for (size_t i = 0; i < _timers.size(); i += 1)
  {
    if (mi - _timers[i]._lastTime >= _timers[i].interval)
    {
      _timers[i]._lastTime = mi;
      _delegate->onClockInterval(_id, _timers[i].id);
      if (!_timers[i].repeat)
      {
        _timers.erase(_timers.begin() + i);
        i -= 1;
      }
    }
  }

  for (size_t i = 0; i < _alarms.size(); i += 1)
  {
    ClockAlarm alarm = _alarms[i].alarm;
    if (_alarms[i]._lastTime != now() && alarm.hour == _h && alarm.minute == _m && alarm.second == _s)
    {
      _alarms[i]._lastTime = now();
      _delegate->onClockAlarm(_id, _alarms[i].id);
      if (!_alarms[i].repeat)
      {
        _alarms.erase(_alarms.begin() + i);
        i -= 1;
      }
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
