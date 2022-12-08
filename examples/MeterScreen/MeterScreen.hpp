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
 *   #include "MeterScreen.hpp"
 *
 *   TFT_eSPI tft = TFT_eSPI();
 *   MeterScreen meterScreen;
 *
 * In your setup() method:
 *   tft.init();
 *   tft.setRotation(1);
 *   meterScreen = MeterScreen(&tft, "Meter!!");
 *
 * And in your loop() method:
 *   meterScreen.showScreen();
 *
 *
 * You will see on your TFT creen several UI components
 *
 */

#ifndef __UIKIT_EXAMPLE_METERCREEN__
#define __UIKIT_EXAMPLE_METERCREEN__

#include <string>

#include "TFT_eSPI_UIKit.hpp"

using namespace std;

class MeterScreen : public Screen
{
private:
  void drawContent();
  void updateState();

  AnalogMeter analogMeter;
  DigitalMeter digitalMeter;
  SwitchGroup group;

  // Interfaces
  // void onScreenClose(const char *id);

public:
  MeterScreen() {}
  MeterScreen(TFT_eSPI *tft, const char *title);
};

#endif
