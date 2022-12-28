/**
 * NOTE: Keep in mind that this library uses TFT_eSPI,
 * so, you need to configure the TFT pins as you would
 * normaly do.
 *
 * This example was created using an ILI9341 TFT screen,
 * (320x240) and ESP32 dev kit.
 *
 *
 * Add to your main file:
 *   #include "TFT_eSPI_UIKit.hpp"
 *   #include "InputScreen.hpp"
 *
 *   TFT_eSPI tft = TFT_eSPI();
 *   InputScreen inputScreen;
 *
 * In your setup() method:
 *   tft.init();
 *   tft.setRotation(1);
 *   inputScreen = InputScreen(&tft, "Meter!!");
 *
 * And in your loop() method:
 *   inputScreen.showScreen();
 *
 *
 * You will see on your TFT creen several UI components
 *
 */

#include "InputScreen.hpp"
#include <functional>

InputScreen::InputScreen(TFT_eSPI *tft, const char *title) : Screen(tft, title)
{
  _shouldRedraw = true;
}

unsigned long t = 0;
void InputScreen::updateState()
{
  if (_numericInput.isReady())
    _numericInput.updateState();

  if (_onBackground)
    return;

  if (_showNumericImputBtn.isReady())
    _showNumericImputBtn.updateState();

  if (_pBar.isReady())
    _pBar.updateState();
}

void InputScreen::drawContent()
{
  if (!_shouldRedraw)
    return;

  _tft->fillRect(0, 0, _contentW, _contentH, SCREEN_BACKGROUND_COLOR);
  _tft->resetViewport();

  if (!_numericInput.isReady())
  {
    _numericInput = NumericInput(_tft, "NumbericInput");
    _numericInput.setParentViewport(_contentX, _contentY, _contentW, _contentH);
    _numericInput.setDelegate(this);
    _numericInput.setInitialValue(-0.9);
  }
  if (!_showNumericImputBtn.isReady())
  {
    _showNumericImputBtn = Button(_tft, "btnShowNumInput");
    _showNumericImputBtn.setParentViewport(_contentX, _contentY, _contentW, _contentH);
    _showNumericImputBtn.setDelegate(this);
  }
  if (!_pBar.isReady())
  {
    _pBar = ProgressBar(_tft, "Progress");
    _pBar.setGradientColor(COLOR_COMPLEMENTARY_A, COLOR_GREEN);
    _pBar.setParentViewport(0, 0, 320, 240);
    _pBar.setDimensions(30, 160, 260, 20);
    _pBar.setRange(-100.0, 100.0);
    _pBar.setValue(0.0);
    // _pBar.hidePercent();
  }

  _showNumericImputBtn.setDimensions(100, 90, 120, 35);
  _showNumericInputBtn.setDisabled(_isDisabled);
  _showNumericImputBtn.draw("Num Input", _shouldRedraw);
  _pBar.draw(_shouldRedraw);
}

// Interfaces
void InputScreen::onButtonTouch(const char *id)
{
  if (strcmp(id, "btnShowNumInput") == 0 && _numericInput.isReady())
  {
    auto f = std::bind(&ProgressBar::setValue, &_pBar, std::placeholders::_1);
    _onBackground = true;
    _numericInput.showWithSetter(f);
  }
}

void InputScreen::onInputComplete(const char *btnId, const char *value)
{
  _numericInput.hide();
  _onBackground = false;
  _forceRedraw = true;
}

void InputScreen::onInputCancel(const char *btnId)
{
  _numericInput.hide();
  _onBackground = false;
  _forceRedraw = true;
}
