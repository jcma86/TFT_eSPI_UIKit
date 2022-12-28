#ifndef __UIKIT_BUTTONS_BUTTONBASE__
#define __UIKIT_BUTTONS_BUTTONBASE__

#include <TFT_eSPI.h>
#include "../base/TouchableComponent.hpp"
#include "ButtonInterface.hpp"

class ButtonBase : public TouchableComponent
{
public:
  ButtonBase() {}
  ButtonBase(TFT_eSPI *tft, const char *id) : TouchableComponent(tft, id) {}
  // virtual ~ButtonBase() {}

  virtual void setDelegate(ButtonInterface *delegate) = 0;
  virtual void updateState() = 0;
  virtual void setLabel(const char *label) = 0;
  virtual void draw(bool forceRedraw = false) = 0;
  virtual void draw(const char *label, bool forceRedraw = false) {}
};

#endif