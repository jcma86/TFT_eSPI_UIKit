#ifndef __UIKIT_SCREEN__
#define __UIKIT_SCREEN__

#include <inttypes.h>
#include <string>
#include <time.h>

#include <TFT_eSPI.h>

#include "ScreenInterface.hpp"
#include "../helpers/Colors.hpp"
#include "../fonts/Fonts.hpp"
#include "../theme/default.hpp"
#include "../display/clock/digital/DigitalClock.hpp"
#include "../tools/wifi/WiFiConnection.hpp"

#ifndef TFT_WIDTH
#define TFT_WIDTH 320
#endif
#ifndef TFT_HEIGHT
#define TFT_HEIGHT 240
#endif

using namespace std;

class Screen
{
protected:
  TFT_eSPI *_tft = NULL;
  WiFiConnection *_wifi = NULL;
  char _id[50];
  ScreenInterface *_delegate = NULL;

  bool _onBackground = false;
  bool _shouldRedraw = false;
  bool _fullScreen = false;
  bool _forceRedraw = false;

  uint32_t _contentX;
  uint32_t _contentY;
  uint32_t _contentW;
  uint32_t _contentH;

  virtual void updateState() = 0;
  virtual void drawContent() = 0;

private:
  uint32_t _x;
  uint32_t _y;
  uint32_t _w;
  uint32_t _h;

  char _title[50];
  bool _closeBtn = false;
  bool _titleBar = true;
  bool _showTime = false;

  DigitalClock _clock;

  void screenStateUpdate();
  void drawScreen();
  void drawTitleBar();

public:
  Screen() {}
  Screen(TFT_eSPI *tft, const char *title);
  ~Screen() {}

  virtual void handleInterruption(int pin, void *param) {}

  void setFullScreen(bool fullScreen = true);
  void showTime(bool showTime = true);
  void setWiFi(WiFiConnection *wifi);
  virtual void setDelegate(ScreenInterface *delegate);
  void setOnBackground(bool onBackground = true);
  void showScreen(bool forceRedraw = false, bool titleBar = true, bool closeBtn = true);
};

#endif