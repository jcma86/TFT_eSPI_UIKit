#ifndef __UIKIT_BUTTONS_TOGGLE__
#define __UIKIT_BUTTONS_TOGGLE__

#include <inttypes.h>
#include <TFT_eSPI.h>

#include "../../base/BaseComponent.hpp"
#include "../button/Button.hpp"
#include "../ButtonInterface.hpp"
#include "ToggleButtonInterface.hpp"

#include "../../helpers/Colors.hpp"
#include "../../theme/default.hpp"

class ToggleButton : public BaseComponent, public ButtonInterface
{
private:
  ToggleButtonInterface *_delegate = NULL;
  bool _state = false;
  char _labelON[30];
  char _labelOFF[30];

  COLOR _backONColor = TOGGLE_BUTTON_ON_BACKGROUND_COLOR;
  COLOR _backOFFColor = TOGGLE_BUTTON_OFF_BACKGROUND_COLOR;
  COLOR _fontONColor = TOGGLE_BUTTON_ON_TEXT_COLOR;
  COLOR _fontOFFColor = TOGGLE_BUTTON_OFF_TEXT_COLOR;

  Button _button;

  void onButtonTouch(const char *btnId);
  void onButtonTouchEnd(const char *btnId) {}
  void onButtonTouchStart(const char *btnId) {}
  void onButtonTouchCancel(const char *btnId) {}

public:
  ToggleButton() {}
  ToggleButton(TFT_eSPI *tft, const char *id);

  void setDelegate(ToggleButtonInterface *delegate);
  void setState(bool state = true);
  void setCustomColors(COLOR backgroundOn, COLOR backgroundOff, COLOR textOn, COLOR textOff);
  void clearCustomColors();
  void setLabels(const char *labelON, const char *labelOFF);
  bool getState();
  const char *getLabel(bool onLabel = true);

  void updateState();
  void draw(bool forceRedraw = false);
};

#endif