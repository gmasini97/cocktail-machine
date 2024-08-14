#ifndef CONFIG_H
#define CONFIG_H

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
#define STEPPER1_PIN_STEP 16
#define STEPPER1_PIN_DIRECTION 4
#define STEPPER1_PIN_ENABLE 27
#define STEPPER1_PIN_ENDSTOP 34
#define STEPPER1_ENDSTOP_ACTIVE_LOW 0       // 0 or 1
#define STEPPER1_REVERSE_DIRECTION true    // true or false
#define STEPPER1_SPEED_IN_HZ 1600
#define STEPPER1_ACCELERATION 1000

// Servo Motor Pouring
#define SERVO_PIN 25

// Servo Motor 2
#define SERVO2_PIN 26

// Auxiliary
#define AUX1_PIN 1
#define AUX2_PIN 3

#endif /* CONFIG_H */
