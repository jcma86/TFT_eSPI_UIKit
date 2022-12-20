#ifndef __UIKIT_TOOLS_WIFI_CONNECTION__
#define __UIKIT_TOOLS_WIFI_CONNECTION__

#include <vector>
#include <WiFi.h>

typedef void (*onWiFiEventCallback)(arduino_event_id_t event);
class WiFiConnectionInterface
{
public:
  WiFiConnectionInterface() {}
  virtual ~WiFiConnectionInterface() {}
  virtual void onWiFiEvent(arduino_event_id_t event) = 0;
};

typedef struct
{
  size_t id;
  WiFiConnectionInterface *delegate;
} delegate_struct;

typedef struct
{
  size_t id;
  onWiFiEventCallback callback;
} callback_struct;

class WiFiConnection
{
private:
  bool _isReady = false;
  bool _init = false;
  unsigned long _lastAttempt = 0;
  char _ssid[50];
  char _pass[50];
  std::vector<callback_struct> _callback;
  std::vector<delegate_struct> _delegate;
  wifi_event_id_t _onEventsId;

  WiFiConnection();
  ~WiFiConnection();

public:
  static WiFiConnection &getInstance()
  {
    static WiFiConnection instance;
    return instance;
  }

  WiFiConnection(WiFiConnection const &) = delete;
  WiFiConnection &operator=(const WiFiConnection &) = delete;

  const char *getEventDescription(arduino_event_id_t event);
  wl_status_t getWiFiStatus();
  const char *getWiFiStatusDescription(wl_status_t status = WiFi.status());
  size_t setDelegate(WiFiConnectionInterface *delegate);
  size_t setCallback(onWiFiEventCallback callback);
  void removeCallback(size_t id);
  void removeDelegate(size_t id);
  std::vector<callback_struct> getCallbacks();
  std::vector<delegate_struct> getDelegates();
  WiFiConnection::init(const char *ssid, const char *password);
  void connectToWiFi(const char *ssid, const char *password);
  bool isConnected();
};

#endif
