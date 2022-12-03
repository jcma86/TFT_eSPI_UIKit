#ifndef __UIKIT_TOOLS_CALIBRATETOUCH__
#define __UIKIT_TOOLS_CALIBRATETOUCH__

#include <inttypes.h>
#include "FS.h"
#include <SPI.h>
#include <TFT_eSPI.h>

#ifndef CALIBRATION_FILE
#define CALIBRATION_FILE "/ScreenTouchCalibrationData"
#endif
#ifndef CALIBRATED
#define CALIBRATED "/ScreenTouchCalibrated"
#endif

#include "CalibrateTouch.hpp"

static bool calibrationComplete = false;

void deleteCalibrationData();
uint16_t *getCalibrationData();
bool needsToCalibrate();
bool touchCalibration(TFT_eSPI *tft);

#endif
