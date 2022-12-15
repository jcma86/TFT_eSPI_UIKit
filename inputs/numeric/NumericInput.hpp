#ifndef __UIKIT_INPUTS_NUMERIC__
#define __UIKIT_INPUTS_NUMERIC__

#include "../../base/BaseComponent.hpp"
#include "../../display/label/Label.hpp"
#include "../../buttons/button/Button.hpp"
#include "../../buttons/ButtonInterface.hpp"
#include "../../buttons/switchGroup/SwitchGroup.hpp"
#include "../../buttons/switchGroup/SwitchGroupInterface.hpp"
#include "../InputInterface.hpp"

class NumericInput : public BaseComponent, public SwitchGroupInterface, public ButtonInterface
{
private:
  InputInterface *_delegate = NULL;
  float _initialValue;
  char _intPart[10];
  char _decPart[7];

  bool _isNegative = false;
  bool _hasDecimal = false;
  bool _isVisible = false;

  Label _valueLbl;
  SwitchGroup _numberBtns;
  SwitchGroup _symbolBtn;
  Button _doneBtn;
  Button _cancelBtn;

  void getValueLabel(char *labelOutput);
  void clearValueLabel();
  void onSwitch(const char *id, int btnIndex, std::vector<bool> states);
  void onButtonTouch(const char *id);

public:
  ~NumericInput() {}
  NumericInput() {}
  NumericInput(TFT_eSPI *tft, const char *id);

  void setDelegate(InputInterface *delegate);
  void setInitialValue(float initialValue);

  void updateState();
  void draw(bool forceRedraw = false);
  void show(bool isVisible = true);
};

#endif
