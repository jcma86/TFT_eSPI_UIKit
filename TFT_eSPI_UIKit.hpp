#ifndef __TFT_ESPI_UIKIT__
#define __TFT_ESPI_UIKIT__

#include "FS.h"
#include <SPI.h>
#include <TFT_eSPI.h>

#include "fonts/Fonts.hpp"
#include "helpers/Colors.hpp"
#include "theme/default.hpp"

#include "base/BaseComponent.hpp"
#include "base/TouchableComponent.hpp"

#include "buttons/ButtonBase.hpp"
#include "buttons/ButtonInterface.hpp"
#include "buttons/button/Button.hpp"
#include "buttons/stepper/StepperInterface.hpp"
#include "buttons/stepper/Stepper.hpp"
#include "buttons/toggle/ToggleButton.hpp"
#include "buttons/toggle/ToggleButtonInterface.hpp"
#include "buttons/switchGroup/SwitchGroup.hpp"
#include "buttons/switchGroup/SwitchGroupInterface.hpp"

#include "display/led/Led.hpp"
#include "display/progress/ProgressBar.hpp"
#include "display/label/Label.hpp"
#include "display/meter/MeterBase.hpp"
#include "display/meter/analog/AnalogMeter.hpp"
#include "display/meter/digital/DigitalMeter.hpp"
#include "display/clock/ClockBase.hpp"
#include "display/clock/alarm/AlarmSetter.hpp"
#include "display/clock/ClockAlarmTimer.hpp"
#include "display/clock/digital/DigitalClock.hpp"
#include "display/clock/ClockInterface.hpp"

#include "inputs/numeric/NumericInput.hpp"
#include "inputs/InputInterface.hpp"

#include "list/List.hpp"
#include "list/ListInterface.hpp"

#include "screen/Screen.hpp"
#include "screen/ScreenInterface.hpp"

#include "tools/tft/CalibrateTouch.hpp"
#include "tools/wifi/WiFiConnection.hpp"
#endif