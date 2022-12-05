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
 *   #include "TestScreen.hpp"
 *
 *   TFT_eSPI tft = TFT_eSPI();
 *   TestScreen testScreen;
 *
 * In your setup() method:
 *   tft.init();
 *   tft.setRotation(1);
 *   testScreen = TestScreen(&tft, "Testing!!");
 *
 * And in your loop() method:
 *   testScreen.showScreen();
 *
 *
 * You will see on your TFT creen several UI components
 *
 */

#ifndef __UIKIT_EXAMPLE_TESTSCREEN__
#define __UIKIT_EXAMPLE_TESTSCREEN__

#include <string>

#include "TFT_eSPI_UIKit.hpp"

using namespace std;

class TestScreen : public Screen
{
private:
  void drawContent();
  void updateState();

  Button normalButton;
  Button textButton;
  ToggleButton toggleButton;
  List aList;
  ProgressBar progressBar;
  Led redLed;
  Led greenLed;
  Label label;

  // Interfaces
  // void onScreenClose(const char *id);

public:
  TestScreen() {}
  TestScreen(TFT_eSPI *tft, const char *title);
};

#endif
