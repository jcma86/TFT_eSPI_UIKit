#ifndef __UIKIT_DISPLAY_LED__
#define __UIKIT_DISPLAY_LED__

#include "../../base/BaseComponent.hpp"

class Led : public BaseComponent
{
private:
  bool _state = false;
  COLOR _color = LED_ON_COLOR;
  COLOR _colorOff = LED_OFF_COLOR;

public:
  ~Led() {}
  Led() {}
  Led(TFT_eSPI *tft, const char *id);

  void turnOn();
  void turnOff();
  void setState(bool isOn = true);
  void setColor(COLOR on = LED_ON_COLOR, COLOR off = LED_OFF_COLOR);

  void updateState();
  void draw(bool forceRedraw = false);
};

#endif