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

#include "TestScreen.hpp"

TestScreen::TestScreen(TFT_eSPI *tft, const char *title) : Screen(tft, title)
{
  _shouldRedraw = true;
}

void TestScreen::updateState()
{
  normalButton.updateState();
  textButton.updateState();
  aList.updateState();
  toggleButton.updateState();
  progressBar.updateState();
  greenLed.updateState();
  redLed.updateState();
  // Serial.println("update state TestScreen");
}

void TestScreen::drawContent()
{
  if (_shouldRedraw)
  {
    _tft->fillRect(0, 0, _contentW, _contentH, SCREEN_BACKGROUND_COLOR);
    _tft->resetViewport();

    if (!normalButton.isReady())
    {
      normalButton = Button(_tft, "TestScreen_SomeButton");
      normalButton.setParentViewport(_contentX, _contentY, _contentW, _contentH);
    }
    if (!textButton.isReady())
    {
      textButton = Button(_tft, "TestScreen_SomeTextButton", TEXT);
      textButton.setParentViewport(_contentX, _contentY, _contentW, _contentH);
    }
    if (!aList.isReady())
    {
      aList = List(_tft, "TestScreen_SomeList");
      aList.setParentViewport(_contentX, _contentY, _contentW, _contentH);
      aList.addItem("First");
      aList.addItem("Second");
      aList.addItem("Third");
      aList.addItem("Fourth");
      aList.addItem("Fifth");
    }

    if (!toggleButton.isReady())
    {
      toggleButton = ToggleButton(_tft, "Toggle!!");
      toggleButton.setParentViewport(_contentX, _contentY, _contentW, _contentH);
      toggleButton.setLabels("ON", "OFF");
    }

    if (!progressBar.isReady())
    {
      progressBar = ProgressBar(_tft, "A Progress Bar");
      progressBar.setParentViewport(_contentX, _contentY, _contentW, _contentH);
    }

    if (!greenLed.isReady())
    {
      greenLed = Led(_tft, "GreenLed");
      greenLed.setParentViewport(_contentX, _contentY, _contentW, _contentH);
      greenLed.setColor(getColorFromRGB(0, 255, 0));
      greenLed.turnOn();
    }
    if (!redLed.isReady())
    {
      redLed = Led(_tft, "RedLed");
      redLed.setParentViewport(_contentX, _contentY, _contentW, _contentH);
      redLed.setColor(getColorFromRGB(255, 0, 0));
      redLed.turnOn();
    }
    if (!label.isReady())
    {
      label = Label(_tft, "Label");
      label.setParentViewport(_contentX, _contentY, _contentW, _contentH);
    }

    normalButton.setDimensions(10, 10, 120, 30);
    normalButton.setDisabled(_isDisabled);
    normalButton.draw("Button!", _shouldRedraw);

    textButton.setDimensions(10, 50, 120, 30);
    textButton.setDisabled(_isDisabled);
    textButton.draw("Text Button!", _shouldRedraw);

    aList.setDimensions(10, 90, 200, 0);
    aList.setDisabled(_isDisabled);
    aList.setNumOfVisibleRows(3);
    aList.draw(_shouldRedraw);

    toggleButton.setDimensions(150, 10, 60, 30);
    toggleButton.setDisabled(_isDisabled);
    toggleButton.draw(_shouldRedraw);

    progressBar.setDimensions(10, 200, 300, 30);
    progressBar.setValue(80.7);
    progressBar.draw(_shouldRedraw);

    greenLed.setDimensions(220, 10, 5, 5);
    greenLed.draw(_shouldRedraw);

    redLed.setDimensions(220, 40, 5, 5);
    redLed.draw(_shouldRedraw);

    label.setPosition(230, 18);
    label.setLabel("Test!!");
    label.draw(_shouldRedraw);
  }
}
