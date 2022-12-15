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

  _showNumericImputBtn.setDimensions(100, 90, 120, 35);
  _showNumericImputBtn.draw("Num Input", _shouldRedraw);
}

// Interfaces
void InputScreen::onButtonTouch(const char *id)
{
  if (strcmp(id, "btnShowNumInput") == 0 && _numericInput.isReady())
  {
    _onBackground = true;
    _numericInput.show(true);
  }
}

void InputScreen::onInputComplete(const char *btnId, const char *value)
{
  Serial.printf("Value -> %s\n", value);
  _numericInput.show(false);
  _onBackground = false;
  _forceRedraw = true;
}

void InputScreen::onInputCancel(const char *btnId)
{
  _numericInput.show(false);
  _onBackground = false;
  _forceRedraw = true;
}
