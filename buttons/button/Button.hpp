#ifndef __UIKIT_BUTTONS_BUTTON__
#define __UIKIT_BUTTONS_BUTTON__

#include <TFT_eSPI.h>
#include "../../theme/default.hpp"
#include "../../fonts/Fonts.hpp"
#include "../../display/label/Label.hpp"
#include "../ButtonBase.hpp"
#include "../ButtonInterface.hpp"

typedef enum
{
  BUTTON_MODE_NORMAL,
  BUTTON_MODE_TEXT,
} ButtonMode;

class Button : public ButtonBase
{
private:
  char _label[30];

  ButtonInterface *_delegate = NULL;
  bool _isTouching = false;
  bool _isPressed = false;
  ButtonMode _mode = BUTTON_MODE_NORMAL;
  bool _hasCustomColor = false;
  bool _hasShadow = false;
  uint8_t _radius = 5;
  Label _btnLabel;

  COLOR _backNormal;
  COLOR _backPressed;
  COLOR _textNormal;
  COLOR _textPressed;
  COLOR _backHover = COLOR_BLUE;
  COLOR _textHover = COLOR_BLACK;

  void onTouch();
  void onTouchStart();
  void onTouchEnd();
  void onTouchCancel();
  void setIsPressed(bool isPressed = true);

public:
  Button();
  Button(TFT_eSPI *tft, const char *id, ButtonMode mode = BUTTON_MODE_NORMAL);

  void setDelegate(ButtonInterface *delegate);
  void setLabel(const char *label);
  void setShadow(bool hasShadow = true);
  void setRadius(uint8_t radius = 5);
  const char *getLabel();
  void setButtonMode(ButtonMode mode = BUTTON_MODE_NORMAL);
  void setHoverColors(COLOR backHover, COLOR textHover);
  void setCustomColors(COLOR backNormal, COLOR backPressed, COLOR textNormal, COLOR textPressed);
  void removeCustomColors();

  void updateState();
  void draw(bool forceRedraw = false);
  void draw(const char *label, bool forceRedraw = false);
};

#endif