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
  _shouldRedraw = true;
}

unsigned long t = 0;
void MeterScreen::updateState()
{
  analogMeter.updateState();
  digitalMeter.updateState();
  if (millis() - t > 10000)
  {
    t = millis();
    analogMeter.setValue(random(0, 55));
    digitalMeter.setValue(random(0, 55));
  }
  group.updateState();
}

void MeterScreen::drawContent()
{
  if (!_shouldRedraw)
    return;

  _tft->fillRect(0, 0, _contentW, _contentH, SCREEN_BACKGROUND_COLOR);
  _tft->resetViewport();

  if (!analogMeter.isReady())
  {
    analogMeter = AnalogMeter(_tft, "AnalogMeter");
    analogMeter.setParentViewport(_contentX, _contentY, _contentW, _contentH);
    analogMeter.addRangeColor(std::pair<COLOR, MeterRange>(COLOR_RED, MeterRange{.min = -50.0, .max = -20.0}));
    analogMeter.addRangeColor(std::pair<COLOR, MeterRange>(COLOR_YELLOW, MeterRange{.min = -20.0, .max = 20.0}));
    analogMeter.addRangeColor(std::pair<COLOR, MeterRange>(COLOR_GREEN, MeterRange{.min = 20.0, .max = 50.0}));
    randomSeed(millis());
  }

  if (!digitalMeter.isReady())
  {
    digitalMeter = DigitalMeter(_tft, "DigitalMeter");
    digitalMeter.setParentViewport(_contentX, _contentY, _contentW, _contentH);
    digitalMeter.setColor(COLOR_BLACK);
  }

  if (!group.isReady())
  {
    group = SwitchGroup(_tft, "Group");
    group.setParentViewport(_contentX, _contentY, _contentW, _contentH);
    group.setButtonWidth(35);
    group.addButton("0", "0");
    group.addButton("1", "1");
    group.addButton("2", "2");
    group.addButton("3", "3");
    group.addButton("4", "4");
    group.addButton("5", "5");
    // group.setAllowMultiSelection();
  }

  analogMeter.setPosition(10, 10);
  analogMeter.setRange(-30.0, 40.0);
  analogMeter.setValue(30.0);
  analogMeter.setUnits("\u00b0C");
  analogMeter.setTitle("Analog Meter");
  analogMeter.draw(_shouldRedraw);

  digitalMeter.setPosition(320, 10);
  digitalMeter.draw(_shouldRedraw);

  group.setDimensions(10, 160, 310, 90);
  group.draw(_shouldRedraw);
}
