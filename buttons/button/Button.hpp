#ifndef __UIKIT_BUTTONS_BUTTON__
#define __UIKIT_BUTTONS_BUTTON__

#include <TFT_eSPI.h>
#include "../../theme/default.hpp"
#include "../../fonts/Fonts.hpp"
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
  // TFT_eSPI *_tft;
  // char _id[30];
  char _label[30];

  ButtonInterface *_delegate = NULL;
  bool _isTouching = false;
  bool _isPressed = false;
  bool _shouldRedraw = false;
  ButtonMode _mode = BUTTON_MODE_NORMAL;
  bool _hasCustomColor = false;

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