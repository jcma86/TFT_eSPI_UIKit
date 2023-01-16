#ifndef __UIKIT_DISPLAY_LABEL__
#define __UIKIT_DISPLAY_LABEL__

#include "../../base/BaseComponent.hpp"
#include "LabelStyle.hpp"

class Label : public BaseComponent
{
private:
  COLOR _color = LABEL_FONT_COLOR;
  COLOR _bgColor = COLOR_WHITE;
  char _label[100];
  bool _hasBg = false;

public:
  Label() {}
  Label(TFT_eSPI *tft, const char *id);

  void setLabel(const char *label);
  void setDatum(uint8_t datum = BL_DATUM);
  void setFontColor(COLOR label = LABEL_FONT_COLOR);
  void clearWithColor(COLOR color = SCREEN_BACKGROUND_COLOR);
  void setPosition(int16_t x, uint16_t y);

  void updateState();
  void draw(bool forceRedraw = false);
};

#endif