#include "DigitalClock.hpp"

void DigitalClock::set12HourMode(bool is12hourMode)
{
  _is12h = is12hourMode;
  _shouldRedraw = true;
}

void DigitalClock::showSeconds(bool showSeconds)
{
  _showSeconds = showSeconds;
  _shouldRedraw = true;
}

void DigitalClock::updateClockState()
{
  char time[15];
  char am[4];
  char sec[5];

  int h = _h;
  sprintf(am, "");
  sprintf(sec, "");
  if (_is12h)
  {
    h = _h > 12 ? _h - 12 : _h;
    sprintf(am, "%s", _h > 11 ? " pm" : " am");
  }
  if (_showSeconds)
    sprintf(sec, ":%02d", _s);

  sprintf(time, "%02d:%02d%s%s", h, _m, sec, am);

  if (strcmp(time, _time) != 0 && _timeLbl.isReady())
  {
    _timeLbl.clearWithColor(SCREEN_BACKGROUND_COLOR);
    _timeLbl.setLabel(time);
    strcpy(_time, time);

    _timeLbl.updateState();
  }

  draw();
}

void DigitalClock::draw(bool forceRedraw)
{
  bool force = _shouldRedraw || forceRedraw;
  if (!_isReady || !force)
    return;

  _tft->resetViewport();
  _tft->setViewport(_vX, _vY, _vW, _vH);

  if (!_timeLbl.isReady())
  {
    _timeLbl = Label(_tft, "DigitalClock");
    _timeLbl.setParentViewport(_vX + _x, _vY + _y, _vW, _vH);
    _timeLbl.setPosition(0, 0, TL_DATUM);
  }

  _timeLbl.draw();
  _shouldRedraw = false;
}
