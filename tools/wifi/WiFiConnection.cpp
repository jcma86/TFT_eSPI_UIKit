#include "WiFiConnection.hpp"

void __onWiFi__(arduino_event_id_t event)
{
  WiFiConnection &wifi = WiFiConnection::getInstance();

  std::vector<callback_struct> callback = wifi.getCallbacks();
  std::vector<delegate_struct> delegate = wifi.getDelegates();

  for (size_t i = 0; i < callback.size(); i += 1)
    callback[i].callback(event);

  for (size_t i = 0; i < delegate.size(); i += 1)
    delegate[i].delegate->onWiFiEvent(event);
}

WiFiConnection::WiFiConnection()
{
  _onEventsId = WiFi.onEvent(&__onWiFi__, ARDUINO_EVENT_MAX);
}

WiFiConnection::~WiFiConnection()
{
  WiFi.removeEvent(_onEventsId);
}

const char *WiFiConnection::getEventDescription(arduino_event_id_t event)
{
  switch (event)
  {
  case 0:
    return "WiFi Event - Ready";
  case 1:
    return "WiFi Event - Scan done";
  case 2:
    return "WiFi Event - Start";
  case 3:
    return "WiFi Event - Stop";
  case 4:
    return "WiFi Event - Connected";
  case 5:
    return "WiFi Event - Disconnected";
  case 6:
    return "WiFi Event - Auth mode change";
  case 7:
    return "WiFi Event - Got IP";
  case 8:
    return "WiFi Event - Got IPv6";
  case 9:
    return "WiFi Event - Lost IP";
  }

  return "WiFi Event - No event description";
}

std::vector<delegate_struct> WiFiConnection::getDelegates()
{
  return _delegate;
}

size_t WiFiConnection::setDelegate(WiFiConnectionInterface *delegate, const char *subscriber)
{
  for (size_t i = 0; i < _delegate.size(); i += 1)
  {
    if (strcmp(subscriber, _delegate[i].subscriber) == 0)
      return i;
  }

  size_t id = _delegate.size();
  delegate_struct del;

  del.id = id;
  del.delegate = delegate;
  strcpy(del.subscriber, subscriber);
  _delegate.push_back(del);

  return id;
}

void WiFiConnection::removeDelegate(size_t id)
{
  for (size_t i = 0; i < _delegate.size(); i += 1)
  {
    if (_delegate[i].id == id)
    {
      _delegate.erase(_delegate.begin() + i);
      break;
    }
  }
}

size_t WiFiConnection::setCallback(onWiFiEventCallback callback, const char *subscriber)
{
  for (size_t i = 0; i < _callback.size(); i += 1)
  {
    if (strcmp(subscriber, _callback[i].subscriber) == 0)
      return i;
  }

  size_t id = _callback.size();
  callback_struct cal;

  cal.id = id;
  cal.callback = callback;
  strcpy(cal.subscriber, subscriber);

  _callback.push_back(cal);

  return id;
}

void WiFiConnection::removeCallback(size_t id)
{
  for (size_t i = 0; i < _delegate.size(); i += 1)
  {
    if (_callback[i].id == id)
    {
      _callback.erase(_callback.begin() + i);
      break;
    }
  }
}

std::vector<callback_struct> WiFiConnection::getCallbacks()
{
  return _callback;
}

void WiFiConnection::init(const char *ssid, const char *password)
{
  if (strcmp(_ssid, ssid) != 0 || strcmp(_pass, password) != 0)
    _init = false;

  if (_init)
    return;
  strcpy(_ssid, ssid);
  strcpy(_pass, password);

  WiFi.disconnect();
  WiFi.mode(wifi_mode_t::WIFI_MODE_STA);
  WiFi.begin(_ssid, _pass);
  _init = true;
  _lastAttempt = millis();
}

void WiFiConnection::connectToWiFi(const char *ssid, const char *password)
{
  if (!_init)
    init(ssid, password);

  if (millis() - _lastAttempt < 500)
    return;

  if (!isConnected() && WiFi.status() != WL_CONNECTED)
    if (WiFi.status() == WL_CONNECT_FAILED)
    {
      WiFi.begin(_ssid, _pass);
      _lastAttempt = millis();
    }
}

bool WiFiConnection::isConnected()
{
  return WiFi.status() == WL_CONNECTED;
}

wl_status_t WiFiConnection::getWiFiStatus()
{
  return WiFi.status();
}

const char *WiFiConnection::getWiFiStatusDescription(wl_status_t status)
{
  switch (status)
  {
  case 0:
    return "WiFi Status - Idle";
  case 1:
    return "WiFi Status - Available";
  case 2:
    return "WiFi Status - Completed";
  case 3:
    return "WiFi Status - Connected";
  case 4:
    return "WiFi Status - Connect failed";
  case 5:
    return "WiFi Status - Connection lost";
  case 6:
    return "WiFi Status - Disconnected";
  case 255:
    return "WiFi Status - No shield (for compatibility with WiFi Shield library)";
  }

  return "WiFi Status - Unknown status";
}
