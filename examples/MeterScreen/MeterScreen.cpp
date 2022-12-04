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

#include "MeterScreen.hpp"

MeterScreen::MeterScreen(TFT_eSPI *tft, const char *title) : Screen(tft, title)
{
  _tft = tft;
  _shouldRedraw = true;
  strcpy(_title, title);
}

unsigned long t = 0;
void MeterScreen::updateState()
{
  analogMeter.updateState();
  if (millis() - t > 1000)
  {
    t = millis();
    analogMeter.setValue(random(-60, 60));
  }
}

void MeterScreen::drawContent()
{
  if (!_shouldRedraw)
    return;

  _tft->fillRect(0, 0, _contentW, _contentH, SCREEN_BACKGROUND_COLOR);
  _tft->resetViewport();

  if (!analogMeter.isReady())
  {
    Serial.printf("Yellow %x\n", getColorFromRGB(255, 255, 0));
    analogMeter = AnalogMeter(_tft, "AnalogMeter");
    analogMeter.setParentViewport(_contentX, _contentY, _contentW, _contentH);
    analogMeter.addRangeColor(std::pair<COLOR, MeterRange>(COLOR_RED, MeterRange{.min = -50.0, .max = -20.0}));
    analogMeter.addRangeColor(std::pair<COLOR, MeterRange>(COLOR_YELLOW, MeterRange{.min = -20.0, .max = 20.0}));
    analogMeter.addRangeColor(std::pair<COLOR, MeterRange>(COLOR_GREEN, MeterRange{.min = 20.0, .max = 50.0}));
    randomSeed(millis());
  }

  analogMeter.setDimensions(10, 10, 250, 120);
  analogMeter.setArcDegrees(150);
  analogMeter.setRange(-50.0, 50.0);
  analogMeter.setValue(30.0);
  analogMeter.draw(_shouldRedraw);
}
