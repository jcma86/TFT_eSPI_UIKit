#ifndef __UIKIT_DISPLAY_CLOCK_INTERFACE__
#define __UIKIT_DISPLAY_CLOCK_INTERFACE__

#include "ClockBase.hpp"

typedef struct
{
  int interval = 15 * 60;
  bool repeat = true;
  size_t lastTime = now();
  bool isActive = true;
  void *pointer = NULL;

  void setInterval(int i) { interval = i; }
  void setRepeat(bool r) { repeat = r; }
  void setIsActive(bool a) { isActive = a; }
  void setPointer(void *p) { pointer = p; }
} ClockTimer;

typedef struct
{
  int hour = 8;
  int minute = 0;
  int second = 0;

  bool isActive = true;
  bool triggered = false;
  bool repeat = true;

  size_t lastTime = now();
  size_t duration = 15 * 60; // 15 minutes

  void *pointer = NULL;

  void setHour(int h) { hour = h; }
  void setIsActive(bool a) { isActive = a; }
  void setMinute(int m) { minute = m; }
  void setSecond(int s) { second = s; }
  void setRepeat(bool r) { repeat = r; }
  void setDuration(size_t d) { duration = d; }
  void setPointer(void *p) { pointer = p; }
} ClockAlarm;

typedef struct
{
  int id;
  char description[50];
  ClockTimer timer;
} timer_struct;

typedef struct
{
  int id;
  char description[50];
  ClockAlarm alarm;
} alarm_struct;

class ClockInterface
{
public:
  virtual void onClockTimer(const char *clockId, timer_struct *timer) {}
  virtual void onClockAlarm(const char *clockId, alarm_struct *alarm, bool intervalComplete = false) {}
};

#endif
