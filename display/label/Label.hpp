#ifndef __UIKIT_DISPLAY_LABEL__
#define __UIKIT_DISPLAY_LABEL__

#include "../../base/BaseComponent.hpp"

class Label : public BaseComponent
{
private:
  COLOR _color = LABEL_COLOR;
  uint8_t _datum = BL_DATUM;
  char _label[100];

public:
  ~Label() {}
  Label() {}
  Label(TFT_eSPI *tft, const char *id);

  void setColor(COLOR label = LABEL_COLOR);
  void setLabel(const char *label);
  void clearWithColor(COLOR color = SCREEN_BACKGROUND_COLOR);
  void setPosition(int16_t x, uint16_t y, uint8_t datum = BL_DATUM);

  void updateState();
  void draw(bool forceRedraw = false);
};

#endif