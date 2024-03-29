#include "Screen.hpp"

Screen::Screen(TFT_eSPI *tft, const char *title)
{
  _tft = tft;
  strcpy(_title, title);
  strcpy(_id, title);

  _shouldRedraw = true;

  _x = 0;
  _y = 0;
  uint8_t rot = _tft->getRotation();
  _w = rot == 1 || rot == 3 ? TFT_HEIGHT : TFT_WIDTH;
  _h = rot == 1 || rot == 3 ? TFT_WIDTH : TFT_HEIGHT;
}

void Screen::setWiFi(WiFiConnection *wifi)
{
  _wifi = wifi;
  _shouldRedraw = true;
}

void Screen::setDelegate(ScreenInterface *delegate)
{
  _delegate = delegate;
}

void Screen::drawTitleBar()
{
  if (_fullScreen)
    return;
  if (_titleBar)
  {
    _tft->setTextColor(TITLE_BAR_FONT_COLOR);
    _tft->setTextSize(TITLE_BAR_FONT_SIZE);
    _tft->setFreeFont(&TITLE_BAR_FONT_FAMILY);

    char title[80];
    if (_shouldRedraw)
    {
      snprintf(title, 80, "%s", _title);
      _tft->fillRect(0, 0, _w, TITLE_BAR_HEIGHT, TITLE_BAR_COLOR);
      _tft->setTextDatum(ML_DATUM);
      _tft->drawString(title, PADDING_NORMAL, (TITLE_BAR_HEIGHT / 2) - 3);
    }
    if (!_clock.isReady())
    {
      _clock = DigitalClock(_tft, "TitleBarClock");
      _clock.setParentViewport(0, 0, _w, TITLE_BAR_HEIGHT);
      _clock.setFont(&IBMPlexMono_Regular6pt8b);
      _clock.setDatum(MR_DATUM);
      _clock.setColors(TITLE_BAR_FONT_COLOR, TITLE_BAR_COLOR);
    }

    _clock.setWiFi(_wifi);
    _clock.setPosition(_w - PADDING_NORMAL, TITLE_BAR_HEIGHT / 2 - 3);
    _clock.draw(_shouldRedraw);
  }
}

void Screen::drawScreen()
{
  if (_tft == NULL || _onBackground)
    return;

  uint8_t bWidth = 0; //_border ? UI_BORDER_WIDTH : 0;
  uint32_t offset = _titleBar && !_fullScreen ? TITLE_BAR_HEIGHT + bWidth : 0;

  uint32_t x = _x + bWidth;
  uint32_t y = _y + bWidth;
  uint32_t w = _w - (2 * bWidth);
  uint32_t h = _h - (2 * bWidth);

  _tft->resetViewport();
  _tft->setViewport(x, y, w, h);
  if (_shouldRedraw)
  {
    _tft->fillScreen(SCREEN_BACKGROUND_COLOR);
    _tft->frameViewport(COLOR_BLACK, -bWidth);
  }
  drawTitleBar();

  // if (_btnClose.isReady())
  // {
  //   _btnClose.updateState();
  // }

  _contentX = x;
  _contentY = y + offset;
  _contentW = w;
  _contentH = h - offset;
  _tft->setViewport(_contentX, _contentY, _contentW, _contentH);
  if (_shouldRedraw)
  {
    _tft->fillRect(0, 0, _contentW, _contentH, SCREEN_BACKGROUND_COLOR);
  }

  drawContent();
}

void Screen::showTime(bool showTime)
{
  _showTime = showTime;
  _shouldRedraw = true;
}

void Screen::setFullScreen(bool fullScreen)
{
  _fullScreen = fullScreen;
  _shouldRedraw = true;
}

void Screen::setOnBackground(bool onBackground)
{
  _onBackground = onBackground;
}

void Screen::screenStateUpdate()
{
  if (_clock.isReady())
    _clock.updateState();
}

void Screen::showScreen(bool forceRedraw, bool titleBar, bool closeBtn)
{
  _shouldRedraw = _shouldRedraw || _forceRedraw || forceRedraw;

  _titleBar = titleBar;
  _closeBtn = closeBtn;

  screenStateUpdate();
  updateState();
  drawScreen();

  _shouldRedraw = false || _forceRedraw;
  _forceRedraw = false;
}
