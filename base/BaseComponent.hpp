#ifndef __UIKIT_BASE_COMPONENTBASE__
#define __UIKIT_BASE_COMPONENTBASE__

#include <inttypes.h>
#include <TFT_eSPI.h>

#include "../helpers/Colors.hpp"
#include "../theme/default.hpp"
#include "../tools/wifi/WiFiConnection.hpp"

class BaseComponent : public WiFiConnectionInterface
{
protected:
  TFT_eSPI *_tft;
  char _id[50];
  WiFiConnection *_wifi = NULL;

  uint16_t _x = 0;
  uint16_t _y = 0;
  uint16_t _w = 0;
  uint16_t _h = 0;
  uint16_t _vX = 0;
  uint16_t _vY = 0;
  uint16_t _vW = 0;
  uint16_t _vH = 0;
  bool _shouldRedraw = false;
  bool _isVisible = true;
  bool _isReady = false;
  bool _isDisabled = false;
  void *_pointer = NULL;
  size_t _wifiDelegateId;

  COLOR _backDisabledColor = COLOR_LIGHT_GRAY;
  COLOR _textDisabledColor = COLOR_DARK_GRAY;

  virtual void onWiFiEvent(arduino_event_id_t event) {}

public:
  virtual ~BaseComponent();
  BaseComponent();
  BaseComponent(TFT_eSPI *tft, const char *id);

  bool isReady();
  const char *getId();
  void setWiFi(WiFiConnection *wifi);
  void setParentViewport(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
  void setDimensions(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
  void setIsVisible(bool _isVisible = true);
  void setDisabled(bool isDisabled = true);
  void setDisabledColors(COLOR _backColor = COLOR_LIGHT_GRAY, COLOR _textColor = COLOR_DARK_GRAY);
  void setPointer(void *ptr);
  void *getPointer();

  // virtual void releaseTimeClient() {}

  virtual void draw(bool forceRedraw = false) = 0;
  virtual void updateState() = 0;
};

#endif
