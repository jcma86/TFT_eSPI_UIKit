#ifndef __UIKIT_BASE_COMPONENTBASE__
#define __UIKIT_BASE_COMPONENTBASE__

#include <inttypes.h>
#include <TFT_eSPI.h>

#include "../helpers/Colors.hpp"
#include "../theme/default.hpp"

class BaseComponent
{
protected:
  TFT_eSPI *_tft;
  char _id[30];

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

public:
  BaseComponent() {}
  BaseComponent(TFT_eSPI *tft, const char *id);

  bool isReady();
  void setParentViewport(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
  void setDimensions(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
  void setIsVisible(bool _isVisible = true);

  virtual void updateState() = 0;
};

#endif
