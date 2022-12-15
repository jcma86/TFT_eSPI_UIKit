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

#ifndef __UIKIT_EXAMPLE_INPUTSCREEN__
#define __UIKIT_EXAMPLE_INPUTSCREEN__

#include <string>

#include "TFT_eSPI_UIKit.hpp"

using namespace std;

class InputScreen : public Screen, public InputInterface, public ButtonInterface
{
private:
  void drawContent();
  void updateState();

  NumericInput _numericInput;
  Button _showNumericImputBtn;
  // Interfaces
  // void onScreenClose(const char *id);
  void onButtonTouch(const char *id);
  void onInputComplete(const char *btnId, const char *value);
  void onInputCancel(const char *btnId);

public:
  InputScreen() {}
  InputScreen(TFT_eSPI *tft, const char *title);
};

#endif
