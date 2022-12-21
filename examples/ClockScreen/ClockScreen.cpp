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
 *   #include "ClockScreen.hpp"
 *
 *   TFT_eSPI tft = TFT_eSPI();
 *   WiFiConnection &wifi = WiFiConnection::getInstance();
 *   ClockScreen clockScreen;
 *
 * In your setup() method:
 *   tft.init();
 *   tft.setRotation(1);
 *   wifi.connectToWiFi("WiFiSSID", "Password");
 *   clockScreen = ClockScreen(&tft, &wifi, "Meter!!");
 *
 * And in your loop() method:
 *   clockScreen.showScreen();
 *
 *
 * You will see on your TFT creen several UI components
 *
 */

#include "ClockScreen.hpp"

ClockScreen::ClockScreen(TFT_eSPI *tft, WiFiConnection *wifi, const char *title) : Screen(tft, title)
{
  _shouldRedraw = true;
  _wifi = wifi;
  if (_wifi)
    _wifiId = _wifi->setDelegate(this, _id);
}

ClockScreen::~ClockScreen()
{
  if (_wifi)
    _wifi->removeDelegate(_wifiId);
}

void ClockScreen::updateState()
{
  if (dClock.isReady())
    dClock.updateState();
}

void ClockScreen::drawContent()
{
  if (!_shouldRedraw)
    return;

  _tft->fillRect(0, 0, _contentW, _contentH, SCREEN_BACKGROUND_COLOR);
  _tft->resetViewport();

  if (!dClock.isReady())
  {
    dClock = DigitalClock(_tft, "DigitalClockScreen");
    dClock.setWiFi(_wifi);
    dClock.setParentViewport(_contentX, _contentY, _contentW, _contentH);
    dClock.setDelegate(this);
    ClockAlarm alarm;
    alarm.hour = 2;
    alarm.minute = 20;
    alarm.second = 27;
    dClock.addAlarm(alarm, false);
    dClock.addTimer(10, false);
    dClock.addTimer(15, true);
    dClock.addTimer(18, false);
    dClock.addTimer(8, true);
  }

  dClock.setPosition(20, 20);
  dClock.draw(_shouldRedraw);
}

// Interfaces
void ClockScreen::onWiFiEvent(arduino_event_id_t event)
{
  Serial.print("Screen wifi event --> ");
  Serial.println(event);
}

void ClockScreen::onClockInterval(const char *id, size_t intervalId)
{
  Serial.print("Clock Interval");
  Serial.println(intervalId);
}

void ClockScreen::onClockAlarm(const char *id, size_t alarmId)
{
  Serial.println("Clock Alarm");
}
