#ifndef __UIKIT_DISPLAY_LABEL__
#define __UIKIT_DISPLAY_LABEL__

#include "../../base/BaseComponent.hpp"

class Label : public BaseComponent
{
private:
  COLOR _color = LABEL_COLOR;
  uint8_t _datum = BL_DATUM;
  uint8_t *_font = (uint8_t *)LABEL_FONT_FAMILY;
  char _label[100];
  GFXfont *_fFont = NULL;
  bool _isFreeFont = false;

public:
  ~Label() {}
  Label() {}
  Label(TFT_eSPI *tft, const char *id);

  void setColor(COLOR label = LABEL_COLOR);
  void setLabel(const char *label);
  void setFont(const uint8_t font[]);
  void setFont(const GFXfont *font);
  void clearWithColor(COLOR color = SCREEN_BACKGROUND_COLOR);
  void setPosition(int16_t x, uint16_t y, uint8_t datum = BL_DATUM);

  void updateState();
  void draw(bool forceRedraw = false);
};

#endif