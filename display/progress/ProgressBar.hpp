#ifndef __UIKIT_DISPLAY_PROGRESS_BAR__
#define __UIKIT_DISPLAY_PROGRESS_BAR__

#include "../../base/BaseComponent.hpp"
#include "../label/Label.hpp"

class ProgressBar : public BaseComponent
{
private:
  bool _hidePercent = false;
  float _value = 0.0;
  float _min = 0.0;
  float _max = 100.0;
  Label _lblPercent;
  COLOR _startColor = PROGRESS_BAR_COLOR_A;
  COLOR _endColor = PROGRESS_BAR_COLOR_B;
  COLOR _borderColor = PROGRESS_BAR_BORDER_COLOR;
  COLOR _fontColor = PROGRESS_BAR_FONT_COLOR;

public:
  ProgressBar() {}
  // ~ProgressBar() {}
  ProgressBar(TFT_eSPI *tft, const char *id);

  void hidePercent(bool hidePercent = true);
  void setRange(float min = 0.0, float max = 100.0);
  void setValue(float value = 100.0);
  void setColor(COLOR color);
  void setColor(COLOR color, COLOR fontColor);
  void setColor(COLOR color, COLOR fontColor, COLOR borderColor);
  void setFontColor(COLOR color);
  void setBorderColor(COLOR color);
  void setGradientColor(COLOR start, COLOR end);

  void clearCustomColor();

  void updateState();
  void draw(bool forceRedraw = false);
};

#endif