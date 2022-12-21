#ifndef __UIKIT_DISPLAY_CLOCK_BASE__
#define __UIKIT_DISPLAY_CLOCK_BASE__

#include <vector>
#include <TimeLib.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "../../base/BaseComponent.hpp"
#include "../../tools/wifi/WiFiConnection.hpp"
#include "ClockInterface.hpp"

typedef struct
{
  int id;
  long interval;
  bool repeat;

  unsigned long _lastTime;
} timer_struct;

typedef struct
{
  int id;
  ClockAlarm alarm;
  bool repeat;

  unsigned long _lastTime;
} alarm_struct;

class ClockBase : public BaseComponent, public WiFiConnectionInterface
{
protected:
  WiFiConnection *_wifi = NULL;
  NTPClient *_timeClient = NULL;
  WiFiUDP _ntpUDP;

  char _server[100];

  bool _started = false;
  unsigned long _updateInterval = 60000;
  unsigned long _lastTime = 0;
  unsigned long _currentTime = 0;
  unsigned long _lastUpdate = 0;
  long _offset = 3600 * 3;
  size_t _wifiDelegateId;

  int _h;
  int _m;
  int _s;

  ClockInterface *_delegate = NULL;
  std::vector<timer_struct> _timers;
  std::vector<alarm_struct> _alarms;

  virtual void updateClockState() {}

  void onWiFiEvent(arduino_event_id_t event);
  void startTimeClient();
  void releaseTimeClient();
  void processTimersAndAlarms();

public:
  ClockBase() {}
  ClockBase(TFT_eSPI *tft, const char *id);
  virtual ~ClockBase();

  void setWiFi(WiFiConnection *wifi);
  void setNTPServer(const char *serverName);
  void setUpdateInterval(unsigned long updateInterval);
  void setOffset(long offset = 3600 * 3);

  void setDelegate(ClockInterface *delegate);
  size_t addTimer(long intervalInSeconds, bool repeat);
  size_t addAlarm(ClockAlarm alarm, bool repeat);
  void removeTimer(size_t id);
  void removeAlarm(size_t id);
  unsigned long getCurrentTime();

  void setPosition(int16_t x, uint16_t y);
  void updateState();
  virtual void draw(bool forceRedraw = false) {}
};

#endif
