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
  string _id;
  ScreenInterface *_delegate = NULL;

  bool _onBackground = false;
  bool _shouldRedraw = false;

  uint32_t _contentX;
  uint32_t _contentY;
  uint32_t _contentW;
  uint32_t _contentH;

  virtual void updateState() = 0;
  virtual void drawContent() = 0;

private:
  TFT_eSPI *_tft = NULL;
  uint32_t _x;
  uint32_t _y;
  uint32_t _w;
  uint32_t _h;

  char _title[50];
  bool _closeBtn = false;
  bool _titleBar = true;

  void drawScreen();
  void drawTitleBar();

public:
  Screen() {}
  Screen(TFT_eSPI *tft, const char *title);
  ~Screen() {}

  virtual void setDelegate(ScreenInterface *delegate);
  void showScreen(bool forceRedraw = false, bool titleBar = true, bool closeBtn = true, bool onBackground = false);
};

#endif