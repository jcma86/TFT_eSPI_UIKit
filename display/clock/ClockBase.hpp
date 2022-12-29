#ifndef __UIKIT_DISPLAY_CLOCK_BASE__
#define __UIKIT_DISPLAY_CLOCK_BASE__

#include <vector>
#include <TimeLib.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "../../base/BaseComponent.hpp"
#include "ClockAlarmTimer.hpp"
#include "ClockInterface.hpp"

class ClockBase : public BaseComponent
{
protected:
  NTPClient *_timeClient = NULL;
  WiFiUDP _ntpUDP;

  char _server[100];

  bool _started = false;
  bool _manual = false;
  unsigned long _updateInterval = 60000;
  long _offset = 3600 * 3;
  size_t _alarmTimerCounter = 0;

  int _h;
  int _m;
  int _s;

  ClockInterface *_delegate = NULL;
  std::vector<timer_struct *> _timers;
  std::vector<alarm_struct *> _alarms;

  virtual void updateClockState() {}

  void startTimeClient();
  void releaseTimeClient();
  void processTimersAndAlarms();

  void onWiFiEvent(arduino_event_id_t event);

public:
  ClockBase() {}
  ClockBase(TFT_eSPI *tft, const char *id);
  ~ClockBase();

  void setNTPServer(const char *serverName);
  void setUpdateInterval(unsigned long updateInterval);
  void setOffset(long offset = 3600 * 3);

  void setManualTime(int h, int m, int s, int day, int month, int year);
  void setAutomaticTime();

  void setDelegate(ClockInterface *delegate);
  timer_struct *addTimer(ClockTimer timer, const char *description);
  alarm_struct *addAlarm(ClockAlarm alarm, const char *description);
  std::vector<alarm_struct *> getActiveAlarms();
  void removeTimer(size_t id);
  void removeAlarm(size_t id);
  void updateAlarm(size_t id, ClockAlarm alarm);
  unsigned long getCurrentTime();
  long secondsToNext(int hour, int min, int sec);
  long secondsToAlarm(ClockAlarm alarm);
  long secondsFromPrev(int hour, int min, int sec);
  long secondsFromAlarm(ClockAlarm alarm);

  void setPosition(int16_t x, uint16_t y);
  void updateState();
  virtual void draw(bool forceRedraw = false){};
};

#endif
