#ifndef __UIKIT_DISPLAY_CLOCK_INTERFACE__
#define __UIKIT_DISPLAY_CLOCK_INTERFACE__

#include "ClockBase.hpp"
#include "ClockAlarmTimer.hpp"

class ClockInterface
{
public:
  virtual void onClockTimer(const char *clockId, timer_struct *timer, void *ptr = NULL) {}
  virtual void onClockAlarm(const char *clockId, alarm_struct *alarm, bool intervalComplete = false, void *ptr = NULL) {}
  virtual void onAlarmChange(const char *alarmSetterId, alarm_struct *alarm, void *ptr = NULL) {}
};

#endif
