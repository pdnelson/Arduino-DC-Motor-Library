#include "DcMotor.h"

// This enum intends to give more meaning to the DcMotor arguments, since
// passing "true" or "false" is not very descriptive.
enum LinearActuatorDirection : bool {
    In = false,
    Out = true
};

// These must be PWM pins if a speed is chosen, like in this example.
#define MOTOR_DIR_1 5
#define MOTOR_DIR_2 6

// Constructor only takes the two pins as arguments.
DcMotor linearActuator = DcMotor(MOTOR_DIR_1, MOTOR_DIR_2); 

void setup() {
  // Both pins must be output, because the DcMotor library writes to them.
  pinMode(MOTOR_DIR_1, OUTPUT);
  pinMode(MOTOR_DIR_2, OUTPUT);
}

void loop() {

  // Start the linear actuator at speed 100/1024.
  linearActuator.immediateStart(LinearActuatorDirection::In, 100);
  delay(2000);

  // Stop linear actuator.
  linearActuator.immediateStop();
  delay(250);

  // Start linear actuator at full speed.
  linearActuator.immediateStart(LinearActuatorDirection::Out);
  delay(2000);

  // Stop linear actuator.
  linearActuator.immediateStop();
  delay(250);
}