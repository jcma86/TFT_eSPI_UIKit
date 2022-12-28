#ifndef __UIKIT_BASE_TOUCHABLE__
#define __UIKIT_BASE_TOUCHABLE__

#include <TFT_eSPI.h>
#include "BaseComponent.hpp"

class TouchableComponent : public BaseComponent
{
protected:
  bool _touchableEnabled = true;
  virtual void processTouch();

private:
  uint16_t _touchX, _touchY;
  uint16_t _prevTouchX, _prevTouchY;
  bool _onTouchStart = false;
  bool _touchStartedOutside = false;
  bool _isTouching = false;

  unsigned long lastTouch = 0;
  unsigned long currentTouch = 0;

  virtual void onTouch() {}
  virtual void onTouchStart() {}
  virtual void onTouchEnd() {}
  virtual void onTouchCancel() {}

  bool isValidTouch(uint16_t x, uint16_t y);

public:
  TouchableComponent() {}
  TouchableComponent(TFT_eSPI *tft, const char *id) : BaseComponent(tft, id){};
  // ~TouchableComponent() {}

  bool isTouching();
};

#endif
