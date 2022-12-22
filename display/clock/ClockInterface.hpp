#ifndef __UIKIT_DISPLAY_CLOCK_INTERFACE__
#define __UIKIT_DISPLAY_CLOCK_INTERFACE__

#include "ClockBase.hpp"

typedef struct
{
  int hour;
  int minute;
  int second;

  bool triggered;
  bool repeat;

  size_t lastTime;

  void setHour(int h) { hour = h; }
  void setMinute(int m) { minute = m; }
  void setSecond(int s) { second = s; }
  void setRepeat(bool r) { repeat = r; }
} ClockAlarm;

typedef struct
{
  int interval;
  bool repeat;
  size_t lastTime;

  void setInterval(int i) { interval = i; }
  void setRepeat(bool r) { repeat = r; }
} ClockTimer;

class ClockInterface
{
public:
  virtual void onClockInterval(const char *id, size_t intervalId) {}
  virtual void onClockAlarm(const char *id, size_t alarmId) {}
};

#endif
