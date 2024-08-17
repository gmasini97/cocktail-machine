#ifndef PYD_PREFERENCES_H
#define PYD_PREFERENCES_H

#include <Preferences.h>

#include "config.h"

class PYD_Preferences
{
  public:
    int16_t   bottleContent[BOTTLES_NUM];       // Number corresponding to the content of the bottle
    int16_t   bottleQuantity[BOTTLES_NUM];      // Quantity of liquid remaining in the bottle [mL]
    float     bottlePosition[BOTTLES_NUM];      // Position of the bottle along the axis [mm]
    int16_t   pourRefillTime;                   // Time the dispenser takes to refill [ms]
    int16_t   pourDeadTime;                     // Time the dispenser takes to start pouring [ms]
    float     pourRate;                         // Rate at which the dispenser pours liquid [mL/s]
    int16_t   servoPourAngle;                   // Servo position when pouring [degrees]
    int16_t   servoIdleAngle;                   // Servo position when resting [degrees]
    
    PYD_Preferences();

    bool begin();
    void end();

    void loadAll();
    void saveAll();

  private:
    Preferences prefs;
};

#endif /* CALIBRATION_H */