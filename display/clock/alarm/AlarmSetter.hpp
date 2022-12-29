#ifndef __UIKIT_DISPLAY_CLOCK_ALARM_SETTER__
#define __UIKIT_DISPLAY_CLOCK_ALARM_SETTER__

#include <vector>
#include <string.h>
#include "../ClockAlarmTimer.hpp"
#include "../ClockBase.hpp"
#include "../../../buttons/switchGroup/SwitchGroup.hpp"
#include "../../../buttons/switchGroup/SwitchGroupInterface.hpp"
#include "../../../buttons/stepper/Stepper.hpp"
#include "../../../buttons/stepper/StepperInterface.hpp"
#include "../../../base/BaseComponent.hpp"

class AlarmSetter : public BaseComponent, public StepperInterface, public SwitchGroupInterface
{
protected:
  ClockBase *_clock = NULL;
  alarm_struct *_alarmStruct = NULL;

  char _dMode = 0; // 0 - Seconds , 1- Minutes, 2 - Hours

  Stepper _stepH;
  Stepper _stepM;
  Stepper _stepS;
  Stepper _stepD;
  Stepper _stepDM;
  SwitchGroup _switchState;

  ClockInterface *_delegate = NULL;

  // Interfaces
  void onStepperValueChange(const char *id, int prev, int next, void *ptr = NULL);
  void onSwitch(const char *id, int btnIndex, std::vector<bool> states, void *ptr = NULL);

public:
  AlarmSetter() {}
  AlarmSetter(TFT_eSPI *tft, ClockBase *clock, const char *id);

  void setAlarm(ClockAlarm alarm);
  void setAlarm(unsigned char h, unsigned char m, unsigned char s, size_t duration, int units = 0, bool repeat = true, bool enabled = true, void *ptr = NULL);
  void setAlarmMessages(const char *msgStart, const char *msgDone);
  void setRepeat(bool repeat = true);
  void setEnabled(bool isEnabled = true);
  void setHour(unsigned char hour);
  void setMinute(unsigned char minute);
  void setSecond(unsigned char second);
  void setInterval(unsigned long updateInterval);
  void setAlarmPointer(void *ptr = NULL);

  void setDelegate(ClockInterface *delegate);

  alarm_struct *getAlarmStruct();

  void updateState();
  void draw(bool forceRedraw = false);
};

#endif
