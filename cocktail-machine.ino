#include "pyd_stepper.h"
#include "pyd_servo.h"
#include "config.h"

FastAccelStepperEngine engine = FastAccelStepperEngine();

PYD_Stepper *carriage;
PYD_Servo *servo;

void setup() {
  Serial.begin(115200);
  Serial.println("Engine init");
  engine.init();
  Serial.println("Carriage creation");
  carriage = new PYD_Stepper(
    &engine,
    STEPPER1_PIN_STEP,
    STEPPER1_PIN_DIRECTION,
    STEPPER1_PIN_ENABLE,
    STEPPER1_PIN_ENDSTOP,
    STEPPER1_ENDSTOP_ACTIVE_LOW,
    STEPPER1_REVERSE_DIRECTION
  );
  Serial.println("Carriage set dynamics");
  carriage->setDynamics(STEPPER1_SPEED_IN_HZ, STEPPER1_ACCELERATION);
  Serial.println("Carriage home");
  carriage->home();

  servo = new PYD_Servo(SERVO_PIN);
  servo->test();
}

void loop() {
  delay(1000);
}
