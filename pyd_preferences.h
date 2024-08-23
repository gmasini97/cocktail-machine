#ifndef PYD_PREFERENCES_H
#define PYD_PREFERENCES_H

#include <Preferences.h> // https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences

#include "config.h"

class PYD_Preferences
{
  public:
    int16_t   bottleContent[BOTTLES_NUM];     // Number corresponding to the content of the bottle
    int16_t   bottleQuantity[BOTTLES_NUM];    // Quantity of liquid remaining in the bottle [mL]
    float     bottlePosition[BOTTLES_NUM];    // Position of the bottle along the axis [mm]
    int16_t   pourFullQuantity;               // Quantity of liquid the dispenser can pour when full [mL]
    int16_t   pourFullTime;                   // Time the dispenser takes to pour when full [ms]
    int16_t   pourRefillTime;                 // Time the dispenser takes to refill [ms]
    int16_t   pourDeadTime;                   // Time the dispenser takes to start pouring [ms]
    float     pourRate;                       // Rate at which the dispenser pours liquid [mL/s]
    int16_t   servoPourAngle;                 // Servo position when pouring [degrees]
    int16_t   servoIdleAngle;                 // Servo position when resting [degrees]
    int16_t   servoIdleTime;                  // Time the takes to return to idle position [ms]
    float     glassAccessPosition;            // Position of the glass access [mm]
    
    PYD_Preferences() {};

    bool begin(const char* name);
    void end();

    void loadAll();
    void saveAll();

  private:
    Preferences mPreferences;
};

extern PYD_Preferences Prefs;

#endif /* PYD_PREFERENCES_H */