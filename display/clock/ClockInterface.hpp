#ifndef __UIKIT_DISPLAY_CLOCK_INTERFACE__
#define __UIKIT_DISPLAY_CLOCK_INTERFACE__

#include "ClockBase.hpp"

typedef struct
{
  int hour;
  int minute;
  int second;
} ClockAlarm;

class ClockInterface
{
public:
  virtual void onClockInterval(const char *id, size_t intervalId) {}
  virtual void onClockAlarm(const char *id, size_t alarmId) {}
};

#endif
