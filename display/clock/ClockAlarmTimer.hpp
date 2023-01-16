#ifndef __UIKIT_DISPLAY_CLOCK_ALARM_TIMER__
#define __UIKIT_DISPLAY_CLOCK_ALARM_TIMER__

#include <TimeLib.h>

typedef struct
{
  int interval = 15;
  int units = 1; // [0-3] Sec, Min, Hrs, Days
  bool repeat = true;
  size_t lastTime = now();
  bool isEnabled = true;
  void *pointer = NULL;
  char message[50];

  void setMessage(const char *msg) { strcpy(message, msg); };
  void setInterval(int i) { interval = i; }
  void setIntervalUnits(int u) { units = u; }
  void setRepeat(bool r) { repeat = r; }
  void setIsEnabled(bool a) { isEnabled = a; }
  void setPointer(void *p) { pointer = p; }
} ClockTimer;

typedef struct
{
  int hour = 8;
  int minute = 0;
  int second = 0;

  bool isEnabled = true;
  bool triggered = false;
  bool repeat = true;
  bool startNextTime = false;

  size_t lastTime = now();
  size_t duration = 15;
  int units = 1; // [0-3] Sec, Min, Hrs, Days

  char messageStart[30];
  char messageDone[30];

  void *pointer = NULL;

  void setHour(int h) { hour = h; }
  void setIsEnabled(bool e) { isEnabled = e; }
  void setMinute(int m) { minute = m; }
  void setSecond(int s) { second = s; }
  void setMessages(const char *start, const char *done)
  {
    strcpy(messageStart, start);
    strcpy(messageDone, done);
  };
  void setRepeat(bool r) { repeat = r; }
  void setDuration(size_t d) { duration = d; }
  void setPointer(void *p) { pointer = p; }
  void setDurationUnits(int u) { units = u; }
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

#endif