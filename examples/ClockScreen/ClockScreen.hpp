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

#ifndef __UIKIT_EXAMPLE_CLOCKSCREEN__
#define __UIKIT_EXAMPLE_CLOCKSCREEN__

#include <string>

#include "TFT_eSPI_UIKit.hpp"

using namespace std;

class ClockScreen : public Screen, public WiFiConnectionInterface, public ClockInterface
{
private:
  void drawContent();
  void updateState();

  WiFiConnection *_wifi = NULL;
  DigitalClock dClock;
  size_t _wifiId = 0;

  // Interfaces
  void onWiFiEvent(arduino_event_id_t event);
  void onClockInterval(const char *id, size_t intervalId);
  void onClockAlarm(const char *id, size_t alarmId);

public:
  ClockScreen() {}
  ~ClockScreen();
  ClockScreen(TFT_eSPI *tft, WiFiConnection *wifi, const char *title);
};

#endif
