#ifndef CONFIG_H
#define CONFIG_H

// Machine Settings
#define BOTTLES_NUM 8
#define STEPPER1_MAX_TRAVEL_MM 1000

// Menu
#define MAX_DEPTH 3

// Default Preferences
#define DEFAULT_BOTTLE_QUANTITY   0       // mL
#define DEFAULT_BOTTLE_POSITION   0       // mm
#define DEFAULT_POUR_REFILL_TIME  5000    // ms
#define DEFAULT_POUR_DEAD_TIME    1000    // ms
#define DEFAULT_POUR_RATE         12.0    // mL/s
#define DEFAULT_SERVO_POUR_ANGLE  60      // degrees
#define DEFAULT_SERVO_IDLE_ANGLE  40      // degrees
#define DEFAULT_AUTO_SAVE         false   //

// I2C Display
#define DISPLAY_PIN_SDA 21
#define DISPLAY_PIN_SCL 22
#define DISPLAY_COLS    20
#define DISPLAY_ROWS    4

// Rotary Encoder
#define ENCODER_PIN_CLK 12
#define ENCODER_PIN_DT  14
#define ENCODER_PIN_SW0 13

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
#define STEPPER1_REVERSE_DIRECTION true    // true or false
#define STEPPER1_SPEED_IN_HZ 1600
#define STEPPER1_ACCELERATION 1000

// Stepper Motor 2
#define STEPPER2_PIN_STEP 16
#define STEPPER2_PIN_DIRECTION 4
#define STEPPER2_PIN_ENABLE 27
#define STEPPER2_PIN_ENDSTOP 34
#define STEPPER2_ENDSTOP_ACTIVE_LOW 0       // 0 or 1
#define STEPPER2_REVERSE_DIRECTION true    // true or false
#define STEPPER2_SPEED_IN_HZ 1600
#define STEPPER2_ACCELERATION 1000

// Servo Motor Pouring
#define SERVO_PIN 25

// Servo Motor 2
#define SERVO2_PIN 26

// Auxiliary
#define AUX1_PIN 1
#define AUX2_PIN 3

#endif /* CONFIG_H */
