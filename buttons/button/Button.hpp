#ifndef __UIKIT_BUTTONS_BUTTON__
#define __UIKIT_BUTTONS_BUTTON__

#include <TFT_eSPI.h>
#include "../../theme/default.hpp"
#include "../../fonts/Fonts.hpp"
#include "../ButtonBase.hpp"
#include "../ButtonInterface.hpp"

typedef enum
{
  NORMAL,
  TEXT,
} ButtonMode;

class Button : public ButtonBase
{
private:
  // TFT_eSPI *_tft;
  // char _id[30];
  char _label[30];

  ButtonInterface *_delegate = NULL;
  bool _isEnabled = true;
  bool _isPressed = false;
  bool _shouldRedraw = false;
  ButtonMode _mode = NORMAL;
  bool _hasCustomColor = false;

  COLOR _backNormal;
  COLOR _backPressed;
  COLOR _textNormal;
  COLOR _textPressed;

  void onTouch();
  void onTouchStart();
  void onTouchEnd();
  void onTouchCancel();
  void setIsPressed(bool isPressed = true);

public:
  Button();
  Button(TFT_eSPI *tft, const char *id, ButtonMode mode = NORMAL);

  void setDelegate(ButtonInterface *delegate);
  void setLabel(const char *label);
  const char *getLabel();
  void setIsEnabled(bool isEnabled = true);
  void setButtonMode(ButtonMode mode = NORMAL);
  void setCustomColors(COLOR backNormal, COLOR backPressed, COLOR textNormal, COLOR textPressed);
  void removeCustomColors();

  void updateState();
  void draw(const char *label, bool forceRedraw = false);
};

#endif