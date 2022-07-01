// This library was written to control a DC motor connected to an H-bridge.
// This is the same library used in the Automatic Record Player project (https://github.com/pdnelson/Automatic-Record-Player)
//
// 2022 Patrick Nelson

#include "DcMotor.h"

DcMotor::DcMotor(uint8_t motorDirectionPin1, uint8_t motorDirectionPin2) {
  this->speed = MOTOR_STOP_SPEED;
  this->motorDirectionPin1 = motorDirectionPin1;
  this->motorDirectionPin2 = motorDirectionPin2;
  this->delayMicros = 15;
}

void DcMotor::immediateStart(bool direction) {
  if(this->speed == MOTOR_STOP_SPEED) this->immediateStop();

  digitalWrite(this->motorDirectionPin1, direction);
  digitalWrite(this->motorDirectionPin2, !direction);

  this->speed = MOTOR_MAX_SPEED;
}

void DcMotor::immediateStart(bool direction, uint16_t pwmWave) {
  if(this->speed == MOTOR_STOP_SPEED) this->immediateStop();

  if(direction) {
    analogWrite(this->motorDirectionPin1, pwmWave);
    digitalWrite(this->motorDirectionPin2, LOW);
  }
  else {
    digitalWrite(this->motorDirectionPin1, LOW);
    analogWrite(this->motorDirectionPin2, pwmWave);
  }

  this->speed = pwmWave;
}

void DcMotor::controlledStart(bool direction, uint16_t msToStart) {
  // TODO: This is a bad implementation, and does not work correctly. This method needs completely re-done.

  this->speed = MOTOR_MAX_SPEED;

  // First calculate the number of steps until we reach the top speed
  // Steps are determined by 25ms intervals.
  uint16_t steps = msToStart / 25;

  // Increment is how many times we need to increase the speed until we reach the max (1024)
  uint16_t increment = 1024 / steps;

  uint16_t current = 0;

  for(int i = 0; i < steps; i++) {
    if(direction) {
      analogWrite(this->motorDirectionPin1, current);
      digitalWrite(this->motorDirectionPin2, LOW);
    }
    else {
      digitalWrite(this->motorDirectionPin1, LOW);
      analogWrite(this->motorDirectionPin2, current);
    }

    current += increment;
    delay(25);
  }

  // Finally, go to full speed (because we may be 1 or 2 away from 1024)
  digitalWrite(this->motorDirectionPin1, direction);
  digitalWrite(this->motorDirectionPin2, !direction);
}

void DcMotor::controlledStart(bool direction, uint16_t pwmWave, uint16_t msToStart) {
  // TODO: Implement
}

void DcMotor::immediateStop() {
  digitalWrite(this->motorDirectionPin1, LOW);
  digitalWrite(this->motorDirectionPin2, LOW);

  delayMicroseconds(this->delayMicros);

  this->speed = MOTOR_STOP_SPEED;
}

void DcMotor::controlledStop(uint16_t msToStop) {
  // TODO: Implement
}

void DcMotor::setDelayMicros(uint16_t delayMicros) {
  this->delayMicros = delayMicros;
}