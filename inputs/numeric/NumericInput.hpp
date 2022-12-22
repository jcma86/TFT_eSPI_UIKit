#ifndef __UIKIT_INPUTS_NUMERIC__
#define __UIKIT_INPUTS_NUMERIC__

#include "../../base/BaseComponent.hpp"
#include "../../display/label/Label.hpp"
#include "../../buttons/button/Button.hpp"
#include "../../buttons/ButtonInterface.hpp"
#include "../../buttons/switchGroup/SwitchGroup.hpp"
#include "../../buttons/switchGroup/SwitchGroupInterface.hpp"
#include "../InputInterface.hpp"

// typedef void (*setValueFunc)(float);

class NumericInput : public BaseComponent, public SwitchGroupInterface, public ButtonInterface
{
private:
  InputInterface *_delegate = NULL;
  float _initialValue;
  bool _allowNegative = true;
  bool _allowDecimal = true;
  bool _hasMaxLimit = false;
  bool _hasMinLimit = false;
  float _minLimit;
  float _maxLimit;
  bool _resetKeys = true;
  char _intPart[10];
  char _decPart[7];
  float *_output = NULL;
  std::function<void(float)> _setter = NULL;

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

  void allowDecimal(bool allow = true);
  void allowNegative(bool allow = true);
  void setMaxLimit(float max);
  void setMinLimit(float min);
  void clearLimits();
  void setDelegate(InputInterface *delegate);
  void setInitialValue(float initialValue);

  void updateState();
  void draw(bool forceRedraw = false);
  void hide();
  void show(float *output = NULL);
  void showWithSetter(std::function<void(float)> setterFunc);
};

#endif
