#ifndef __UIKIT_BUTTONS_STEPPER__
#define __UIKIT_BUTTONS_STEPPER__

#include <inttypes.h>
#include <TFT_eSPI.h>
#include <vector>

#include "../../base/BaseComponent.hpp"
#include "../button/Button.hpp"
#include "../ButtonInterface.hpp"
#include "../../display/label/Label.hpp"

#include "StepperInterface.hpp"

#include "../../helpers/Colors.hpp"
#include "../../theme/default.hpp"

class Stepper : public BaseComponent, public ButtonInterface
{
private:
  StepperInterface *_delegate = NULL;
  uint16_t _btnW = BUTTON_HEIGHT;
  uint16_t _btnH = BUTTON_HEIGHT;
  int _step = 1;
  int _min = 0;
  int _max = 100;
  int _current = -1;
  bool _vertical = false;
  bool _repeating = false;
  bool _cycle = true;
  bool _updated = false;
  bool _sideMode = false;
  bool _left = false;
  unsigned long _lastCheck = 0;
  bool _stringsMode = false;
  char _format[10] = "%d";
  std::vector<const char *> _strings;

  Button _btnUp;
  Button _btnDown;
  Label _lblValue;

  COLOR _btnColor = COLOR_PRIMARY;
  COLOR _btnTextColor = COLOR_BLACK;
  COLOR _labelColor = COLOR_BLACK;
  COLOR _bgColor = COLOR_WHITE;

  Button _button;

  void onButtonTouch(const char *btnId, void *ptr = NULL);
  void onButtonTouchEnd(const char *btnId, void *ptr = NULL) {}
  void onButtonTouchStart(const char *btnId, void *ptr = NULL);
  void onButtonTouchCancel(const char *btnId, void *ptr = NULL) {}

  void moveStepper(bool up = true);

public:
  Stepper() {}
  Stepper(TFT_eSPI *tft, const char *id);

  void setDelegate(StepperInterface *delegate);

  void setValue(int value);
  void setStep(int step);
  void setRange(int min, int max);
  void setVertical(bool vertical = true);
  void setSideMode(bool sideMode = true, bool left = false);
  void setButtonSize(uint16_t w = BUTTON_HEIGHT, uint16_t h = BUTTON_HEIGHT);
  void setCustomColors(COLOR btnColor, COLOR btnTextColor, COLOR textColor);
  void setStringsMode(bool stringsMode = true);
  void addString(const char *str);
  void setNumberFormat(const char *format);
  void clearStrings();
  int getValue();

  void updateState();
  void draw(bool forceRedraw = false);
};

#endif
