#ifndef CONFIG_H
#define CONFIG_H

// Machine Settings
#define SERIAL_BAUD_RATE 115200
#define BOTTLES_NUM 8

// Menu
#define MENU_MAX_DEPTH 3

// Preferences
#define PREFERENCES_NAMESPACE           "cocktail"
#define DEFAULT_BOTTLE_QUANTITY         0           // mL
#define DEFAULT_BOTTLE_POSITION         0           // mm
#define DEFAULT_POUR_FULL_QUANTITY      25          // mL
#define DEFAULT_POUR_FULL_TIME          3000        // ms
#define DEFAULT_POUR_REFILL_TIME        5000        // ms
#define DEFAULT_POUR_DEAD_TIME          1000        // ms
#define DEFAULT_POUR_RATE               12.0        // mL/s
#define DEFAULT_SERVO_POUR_ANGLE        60          // degrees
#define DEFAULT_SERVO_IDLE_ANGLE        40          // degrees
#define DEFAULT_SERVO_IDLE_TIME         1000        // ms
#define DEFAULT_GLASS_ACCESS_POSITION   0           // mm
#define DEFAULT_UPDATE_CHECK            0           // 0=manual, 1=at-boot
#define DEFAULT_UPDATE_CHANNEL          0           // 0=stable, 1=beta, 2=dev
#define DEFAULT_AUTO_SAVE               false       // true or false

// I2C Display
#define DISPLAY_PIN_SDA 21
#define DISPLAY_PIN_SCL 22
#define DISPLAY_COLS    20
#define DISPLAY_ROWS    4

// Rotary Encoder
#define ENCODER_PIN_A       12
#define ENCODER_PIN_B       14
#define ENCODER_PIN_BUTTON  13

// RFID Reader SPI (RC522)
#define RFID_PIN_MOSI  23
#define RFID_PIN_MISO  19
#define RFID_PIN_CLK   18
#define RFID_PIN_CS    5
#define RFID_PIN_RESET 17

// Sonar 1
#define SONAR1_PIN_TRIG 33
#define SONAR1_PIN_ECHO 39

// Sonar 2
#define SONAR2_PIN_TRIG 32
#define SONAR2_PIN_ECHO 36

// Stepper Motor Linear Axis
#define STEPPER1_PIN_STEP 2
#define STEPPER1_PIN_DIRECTION 15
#define STEPPER1_PIN_ENABLE 27
#define STEPPER1_PIN_ENDSTOP 35
#define STEPPER1_ENDSTOP_ACTIVE_LOW 0       // 0 or 1
#define STEPPER1_REVERSE_DIRECTION true     // true or false
#define STEPPER1_SPEED 100                  // mm/s
#define STEPPER1_SPEED_HOMING 10            // mm/s
#define STEPPER1_ACCELERATION 500           // mm/s^2
#define STEPPER1_MAX_TRAVEL_MM 785          // mm
#define STEPPER1_STEPS_MM 80                // 1/mm

// Stepper Motor 2
#define STEPPER2_PIN_STEP 16
#define STEPPER2_PIN_DIRECTION 4
#define STEPPER2_PIN_ENABLE 27
#define STEPPER2_PIN_ENDSTOP 34
#define STEPPER2_ENDSTOP_ACTIVE_LOW 0       // 0 or 1
#define STEPPER2_REVERSE_DIRECTION true     // true or false
#define STEPPER2_SPEED 100                  // mm/s
#define STEPPER2_SPEED_HOMING 10            // mm/s
#define STEPPER2_ACCELERATION 500           // mm/s^2
#define STEPPER2_MAX_TRAVEL_MM 1000         // mm
#define STEPPER2_STEPS_MM 80                // 1/mm

// Servo Motor Pouring
#define SERVO1_PIN 25

// Servo Motor 2
#define SERVO2_PIN 26

// Auxiliary
#define AUX1_PIN 1
#define AUX2_PIN 3

// Updates (OTA) Settings
#define UPDATE_URL_STABLE   "https://github.com/gmasini97/cocktail-machine/releases/download/main-stable/build.bin"
#define UPDATE_URL_BETA     "https://github.com/gmasini97/cocktail-machine/releases/download/main-beta/build.bin"
#define UPDATE_URL_DEV      "https://github.com/gmasini97/cocktail-machine/releases/download/main-dev/build.bin"

#endif /* CONFIG_H */
