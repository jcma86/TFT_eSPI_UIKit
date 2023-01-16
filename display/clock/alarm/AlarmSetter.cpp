#include "AlarmSetter.hpp"

AlarmSetter::AlarmSetter(TFT_eSPI *tft, ClockBase *clock, const char *id) : BaseComponent(tft, id)
{
  _clock = clock;
  _isReady = true;

  ClockAlarm alarm;
  alarm.hour = 7;
  alarm.minute = 0;
  alarm.second = 0;
  alarm.duration = 16;
  alarm.units = 2;
  alarm.repeat = true;
  alarm.isEnabled = true;
  alarm.lastTime = now();
  _alarmStruct = _clock->addAlarm(alarm, id);

  _shouldRedraw = true;
}

alarm_struct *AlarmSetter::getAlarmStruct()
{
  return _alarmStruct;
}

void AlarmSetter::setAlarm(ClockAlarm alarm)
{
  setAlarm(alarm.hour, alarm.minute, alarm.second, alarm.duration, alarm.units, alarm.repeat, alarm.isEnabled, alarm.pointer);
  _shouldRedraw = true;
}

void AlarmSetter::setAlarm(unsigned char h, unsigned char m, unsigned char s, size_t duration, int units, bool repeat, bool enabled, void *ptr)
{
  if (!_isReady)
    return;

  _alarmStruct->alarm.lastTime = now();
  _alarmStruct->alarm.hour = h;
  _alarmStruct->alarm.minute = m;
  _alarmStruct->alarm.second = s;
  _alarmStruct->alarm.duration = duration;
  _alarmStruct->alarm.units = units;
  _alarmStruct->alarm.repeat = repeat;
  _alarmStruct->alarm.isEnabled = enabled;
  _alarmStruct->alarm.pointer = ptr;

  _shouldRedraw = true;
}

void AlarmSetter::setAlarmMessages(const char *msgS, const char *msgD)
{
  _alarmStruct->alarm.setMessages(msgS, msgD);
}

void AlarmSetter::setRepeat(bool repeat)
{
  if (!_isReady)
    return;

  _alarmStruct->alarm.repeat = repeat;
  _shouldRedraw = true;
}

void AlarmSetter::setEnabled(bool isEnabled)
{
  if (!_isReady)
    return;

  _alarmStruct->alarm.isEnabled = isEnabled;
  _shouldRedraw = true;
}

void AlarmSetter::setHour(unsigned char hour)
{
  if (!_isReady)
    return;

  _alarmStruct->alarm.hour = hour;
  _shouldRedraw = true;
}

void AlarmSetter::setMinute(unsigned char minute)
{
  if (!_isReady)
    return;

  _alarmStruct->alarm.minute = minute;
  _shouldRedraw = true;
}

void AlarmSetter::setSecond(unsigned char second)
{
  if (!_isReady)
    return;

  _alarmStruct->alarm.second = second;
  _shouldRedraw = true;
}

void AlarmSetter::setInterval(unsigned long duration)
{
  if (!_isReady)
    return;

  _alarmStruct->alarm.duration = duration;
  _shouldRedraw = true;
}

void AlarmSetter::setAlarmPointer(void *ptr)
{
  if (!_isReady)
    return;
  _alarmStruct->alarm.pointer = ptr;
}

void AlarmSetter::setDelegate(ClockInterface *delegate)
{
  _delegate = delegate;
}

void AlarmSetter::updateState()
{
  if (!_isReady)
    return;

  _switchState.setState(0, _alarmStruct->alarm.repeat);
  _switchState.setState(1, _alarmStruct->alarm.isEnabled);
  _switchState.setState(2, _alarmStruct->alarm.startNextTime);

  _stepH.updateState();
  _stepM.updateState();
  _stepS.updateState();
  _stepD.updateState();
  _stepDM.updateState();
  _switchState.updateState();

  draw();
}

void AlarmSetter::draw(bool forceRedraw)
{
  bool force = _shouldRedraw || forceRedraw;
  if (!force || !_isReady)
    return;

  _w = 200;
  _h = 120;

  _tft->resetViewport();
  _tft->setViewport(_x + _vX, _y + _vY, _w, _h);
  _tft->fillRect(0, 0, _w, _h, COLOR_WHITE);
  _tft->frameViewport(COLOR_BLACK, 1);

  if (!_stepH.isReady())
  {
    _stepH = Stepper(_tft, "AlarmStepper_h");
    _stepH.setParentViewport(_x + _vX, _y + _vY, _w, _h);
    _stepH.setNumberFormat("%02d");
    _stepH.setRange(0, 23);
    _stepH.setDelegate(this);
    _stepH.setSideMode(true);
    _stepH.setButtonSize(25);
    _stepH.setCustomColors(COLOR_SECONDARY, COLOR_DARK_GRAY, COLOR_BLACK);
  }
  if (!_stepM.isReady())
  {
    _stepM = Stepper(_tft, "AlarmStepper_m");
    _stepM.setParentViewport(_x + _vX, _y + _vY, _w, _h);
    _stepM.setNumberFormat("%02d");
    _stepM.setRange(0, 59);
    _stepM.setDelegate(this);
    _stepM.setSideMode(true);
    _stepM.setButtonSize(25);
    _stepM.setCustomColors(COLOR_SECONDARY, COLOR_DARK_GRAY, COLOR_BLACK);
  }
  if (!_stepS.isReady())
  {
    _stepS = Stepper(_tft, "AlarmStepper_s");
    _stepS.setParentViewport(_x + _vX, _y + _vY, _w, _h);
    _stepS.setNumberFormat("%02d");
    _stepS.setRange(0, 59);
    _stepS.setDelegate(this);
    _stepS.setSideMode(true);
    _stepS.setButtonSize(25);
    _stepS.setCustomColors(COLOR_SECONDARY, COLOR_DARK_GRAY, COLOR_BLACK);
  }
  if (!_stepD.isReady())
  {
    _stepD = Stepper(_tft, "AlarmStepper_d");
    _stepD.setParentViewport(_x + _vX, _y + _vY, _w, _h);
    _stepD.setRange(0, 1000);
    _stepD.setDelegate(this);
    _stepD.setSideMode(true);
    _stepD.setButtonSize(25);
    _stepD.setCustomColors(COLOR_SECONDARY, COLOR_DARK_GRAY, COLOR_BLACK);
  }
  if (!_stepDM.isReady())
  {
    _stepDM = Stepper(_tft, "AlarmStepper_dm");
    _stepDM.setParentViewport(_x + _vX, _y + _vY, _w, _h);
    _stepDM.setDelegate(this);
    _stepDM.setSideMode(true);
    _stepDM.setStringsMode(true);
    _stepDM.addString("sec");
    _stepDM.addString("min");
    _stepDM.addString("hrs");
    _stepDM.addString("days");
    _stepDM.setButtonSize(25);
    _stepDM.setCustomColors(COLOR_SECONDARY, COLOR_DARK_GRAY, COLOR_BLACK);
  }
  if (!_switchState.isReady())
  {
    _switchState = SwitchGroup(_tft, "AlarmStepper_state");
    _switchState.setParentViewport(_x + _vX, _y + _vY, _w, _h);
    _switchState.setButtonWidth(60);
    _switchState.setCustomColors(COLOR_GREEN, COLOR_RED, COLOR_BLACK, COLOR_BLACK);
    _switchState.setIsHorizontal();
    _switchState.setAllowMultiSelection();
    _switchState.setDelegate(this);
    _switchState.addButton("AlarmStepper_repeat", "Re");
    _switchState.addButton("AlarmStepper_active", "En");
    _switchState.addButton("AlarmStepper_next", "Sch");
  }

  _stepH.setDisabled(_isDisabled);
  _stepM.setDisabled(_isDisabled);
  _stepS.setDisabled(_isDisabled);
  _stepD.setDisabled(_isDisabled);
  _stepDM.setDisabled(_isDisabled);
  _switchState.setDisabled(_isDisabled);

  _stepH.setDimensions(5, 5, 35, 35);
  _stepM.setDimensions(70, 5, 35, 35);
  _stepS.setDimensions(135, 5, 35, 35);
  _stepD.setDimensions(5, 45, 70, 35);
  _stepDM.setDimensions(100, 45, 70, 35);
  _switchState.setDimensions(5, 85, 190, 35);

  _stepH.setValue(_alarmStruct->alarm.hour);
  _stepM.setValue(_alarmStruct->alarm.minute);
  _stepS.setValue(_alarmStruct->alarm.second);
  _stepD.setValue(_alarmStruct->alarm.duration);
  _stepDM.setValue(_alarmStruct->alarm.units);

  _switchState.setState(0, _alarmStruct->alarm.repeat);
  _switchState.setState(1, _alarmStruct->alarm.isEnabled);
  _switchState.setState(2, _alarmStruct->alarm.startNextTime);

  _stepH.draw(force);
  _stepM.draw(force);
  _stepS.draw(force);
  _stepD.draw(force);
  _stepDM.draw(force);
  _switchState.draw(force);

  _shouldRedraw = false;
}

// Interfaces
void AlarmSetter::onStepperValueChange(const char *id, int prev, int next, void *ptr)
{
  if (strcmp(id, "AlarmStepper_h") == 0)
    _alarmStruct->alarm.hour = next;
  if (strcmp(id, "AlarmStepper_m") == 0)
    _alarmStruct->alarm.minute = next;
  if (strcmp(id, "AlarmStepper_s") == 0)
    _alarmStruct->alarm.second = next;
  if (strcmp(id, "AlarmStepper_d") == 0)
    _alarmStruct->alarm.duration = next;
  if (strcmp(id, "AlarmStepper_dm") == 0)
    _alarmStruct->alarm.units = next;

  // _alarmStruct->alarm.lastTime = now();
}

void AlarmSetter::onSwitch(const char *id, int btnIndex, std::vector<bool> states, void *ptr)
{
  if (btnIndex == 0)
    _alarmStruct->alarm.repeat = states[0];
  else if (btnIndex == 1)
    _alarmStruct->alarm.isEnabled = states[1];
  else if (btnIndex == 2)
    _alarmStruct->alarm.startNextTime = states[2];

  // _alarmStruct->alarm.lastTime = now();
}
