#include "NumericInput.hpp"

NumericInput::NumericInput(TFT_eSPI *tft, const char *id) : BaseComponent(tft, id)
{
  strcpy(_intPart, "");
  strcpy(_decPart, "");
  _isReady = true;
  _shouldRedraw = true;
}

void NumericInput::setDelegate(InputInterface *delegate)
{
  _delegate = delegate;
}

void NumericInput::setInitialValue(float initialValue)
{
  clearValueLabel();
  _initialValue = initialValue;
  char value[20];
  sprintf(value, "%.4f", initialValue);
  strncpy(_intPart, value, strlen(value) - 5);
  strncpy(_decPart, &value[strlen(value) - 4], 4);

  _hasDecimal = atoi(_decPart) > 0;
  if (_hasDecimal)
  {
    int i = 3;
    while (i >= 0)
    {
      if (_decPart[i] != '0')
        break;
      _decPart[i] = '\0';
      i--;
    }
  }
  if (_intPart[0] == '-')
  {
    _isNegative = true;
    strncpy(_intPart, &_intPart[1], strlen(_intPart) - 1);
    _intPart[strlen(_intPart) - 1] = '\0';
  }

  _shouldRedraw = true;
}

void NumericInput::show(bool isVisible)
{
  _isVisible = isVisible;
  _shouldRedraw = isVisible;
}

void NumericInput::updateState()
{
  if (!_isReady || !_isVisible)
    return;

  _valueLbl.updateState();
  _numberBtns.updateState();
  _symbolBtn.updateState();
  _doneBtn.updateState();
  _cancelBtn.updateState();
  draw();
}

void NumericInput::draw(bool forceRedraw)
{
  bool force = forceRedraw || _shouldRedraw;
  if (!_isReady || !force || !_isVisible)
    return;

  int32_t w = 205;
  int32_t h = 180;
  int32_t vx = (_vX + _vW / 2) - (w / 2);
  int32_t vy = (_vY + _vH / 2) - (h / 2);

  _tft->resetViewport();
  _tft->setViewport(vx, vy, w, h);
  _tft->fillRect(0, 0, w, h, SCREEN_BACKGROUND_COLOR);
  _tft->frameViewport(COLOR_BLACK, -2);

  if (!_valueLbl.isReady())
  {
    _valueLbl = Label(_tft, "LblNumericInput");
    _valueLbl.setParentViewport(vx, vy, w, h);
  }
  if (!_numberBtns.isReady())
  {
    _numberBtns = SwitchGroup(_tft, "NumbersGroup");
    _numberBtns.setBehaveAsButtons();
    _numberBtns.setParentViewport(vx, vy, w, h);
    _numberBtns.setButtonWidth(35);
    _numberBtns.setDelegate(this);
    char btn[3];
    for (int i = 0; i < 10; i += 1)
    {
      sprintf(btn, "%d", i);
      _numberBtns.addButton(btn, btn);
    }
  }
  if (!_symbolBtn.isReady())
  {
    _symbolBtn = SwitchGroup(_tft, "SymbolsGroup");
    _symbolBtn.setBehaveAsButtons();
    _symbolBtn.setParentViewport(vx, vy, w, h);
    _symbolBtn.setButtonWidth(35);
    _symbolBtn.setDelegate(this);

    _symbolBtn.addButton("-", "-");
    _symbolBtn.addButton(".", ".");
    _symbolBtn.addButton("<", "<");
    _symbolBtn.addButton("c", "C");
  }
  if (!_doneBtn.isReady())
  {
    _doneBtn = Button(_tft, "btnDone");
    _doneBtn.setParentViewport(vx, vy, w, h);
    _doneBtn.setDelegate(this);
  }
  if (!_cancelBtn.isReady())
  {
    _cancelBtn = Button(_tft, "btnCancel");
    _cancelBtn.setParentViewport(vx, vy, w, h);
    _cancelBtn.setDelegate(this);
  }

  char value[20];
  getValueLabel(value);
  _tft->drawRect(5, 5, w - 10, 25, COLOR_BLACK);
  _valueLbl.setPosition(w - 10, 10, TR_DATUM);
  _valueLbl.setLabel(value);
  _valueLbl.draw(force);

  _numberBtns.setDimensions(5, 35, w - 10, 80);
  _numberBtns.draw(force);

  _symbolBtn.setDimensions(5, 105, w - 10, 35);
  _symbolBtn.draw(force);

  _doneBtn.setDimensions((w / 2) - 95, 140, 90, 35);
  _doneBtn.draw("Done", force);

  _cancelBtn.setDimensions((w / 2) + 5, 140, 90, 35);
  _cancelBtn.draw("Cancel", force);

  _shouldRedraw = false;
}

void NumericInput::getValueLabel(char *labelOutput)
{
  strncpy(labelOutput, "\0", 20);

  if (_isNegative)
    sprintf(labelOutput, "-");

  sprintf(labelOutput, "%s%s", labelOutput, _intPart);
  if (_hasDecimal)
    sprintf(labelOutput, "%s.%s", labelOutput, _decPart);
}

void NumericInput::clearValueLabel()
{
  strncpy(_intPart, "", 10);
  strncpy(_decPart, "", 7);

  _hasDecimal = false;
  _isNegative = false;
}

// Interfaces
void NumericInput::onButtonTouch(const char *id)
{
  if (!_delegate)
    return;

  if (strcmp(id, "btnDone") == 0)
  {
    char value[20];
    getValueLabel(value);
    _delegate->onInputComplete(_id, value);
  }
  if (strcmp(id, "btnCancel") == 0)
  {
    _delegate->onInputCancel(_id);
  }
}

void NumericInput::onSwitch(const char *id, int btnIndex, std::vector<bool> states)
{
  if (strcmp(id, "NumbersGroup") == 0)
  {
    if (!_hasDecimal && strlen(_intPart) < 7)
    {
      if (btnIndex == 0 && strlen(_intPart) == 0)
        return;

      sprintf(_intPart, "%s%d", _intPart, btnIndex);
    }
    else if (_hasDecimal && strlen(_decPart) < 4)
      sprintf(_decPart, "%s%d", _decPart, btnIndex);
  }
  else if (strcmp(id, "SymbolsGroup") == 0)
  {
    if (btnIndex == 0)
      _isNegative = !_isNegative;
    else if (btnIndex == 1)
    {
      if (strlen(_decPart) == 0)
        _hasDecimal = !_hasDecimal;
      if (_hasDecimal && strlen(_intPart) == 0)
        sprintf(_intPart, "0");
    }
    else if (btnIndex == 2)
    {
      if (_hasDecimal && strlen(_decPart) > 0)
        _decPart[strlen(_decPart) - 1] = '\0';
      else if (_hasDecimal)
        _hasDecimal = false;
      else if (strlen(_intPart) > 0)
        _intPart[strlen(_intPart) - 1] = '\0';
    }
    else if (btnIndex == 3)
    {
      clearValueLabel();
    }
  }

  char value[20];
  getValueLabel(value);
  if (_valueLbl.isReady())
  {
    _valueLbl.clearWithColor();
    _valueLbl.setLabel(value);
  }
}