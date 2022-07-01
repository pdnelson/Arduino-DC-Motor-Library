// This library was written to control a DC motor connected to an H-bridge.
// This is the same library used in the Automatic Record Player project (https://github.com/pdnelson/Automatic-Record-Player)
//
// 2022 Patrick Nelson

#include "arduino.h"

#ifndef DcMotor_h
#define DcMotor_h

#define MOTOR_STOP_SPEED 0
#define MOTOR_MAX_SPEED 1024

class DcMotor {
    public:

        // Constructor. Calling this automatically sets motorDirectionPin1 and motorDirectionPin2's pinMode to OUTPUT.
        DcMotor(uint8_t motorDirectionPin1, uint8_t motorDirectionPin2);

        // Move the motor one direction or the other, immediately, at top speed.
        // If changing directions, the stop() command will be executed first with a delay. The reason for this is because, otherwise, the
        // transistors could short together.
        // direction - Which direction you want the motor to spin.
        void immediateStart(bool direction);

        // If the motor is attached to a PWM pin, then it can be moved with a PWM wave with this method.
        // This will immediately begin moving the motor at the set speed.
        // direction - Which direction you want the motor to spin.
        // pwmWave - How fast the motor should spin once it reaches its desired speed, between 0 and 1024.
        void immediateStart(bool direction, uint16_t pwmWave);

        // Move the motor in one direction or the other, gradually increasing speed until the top speed is reached. This is a blocking call,
        // meaning it will hold up the program until the motor has reached full speed.
        // direction - Which direction you want the motor to spin.
        // msToStart - How long it should take the motor to reach its top speed.
        void controlledStart(bool direction, uint16_t msToStart);

        // Move the motor in one direction or the other, gradually increasing speed until the pwm speed is reached. This is a blocking call,
        // meaning it will hold up the program until the motor has reached full speed.
        // direction - Which direction you want the motor to spin.
        // pwmWave - How fast the motor should spin once it reaches its desired speed, between 0 and 1024.
        // msToStart - How long it should take the motor to reach its top speed.
        void controlledStart(bool direction, uint16_t pwmWave, uint16_t msToStart);
        
        // This brings the motor to an immediate stop, no matter what direction it is traveling. A short delay will be applied after the motor is stopped to prevent any shorting.
        void immediateStop();

        // This will slow the motor down until it reaches a complete stop. A short delay will be applied after the motor is stopped to prevent any shorting.
        // This is a blocking call, meaning it will hold up the program until the motor has reached full speed.
        // msToStop - How long it should take the motor to slow down completely.
        void controlledStop(uint16_t msToStop);

        // Set the delay, in microseconds, that occurs after the stop() command is executed. This is to account for propagation delay. 
        void setDelayMicros(uint16_t delayMicros);

    private:        
        // The speed, between 0 and 1024, that the motor is traveling. 0 is totally stopped, and 1024 is full speed.
        uint16_t speed;

        // Pins that correspond to the motor's direction pins. Only one of these will ever be HIGH at a time.
        uint8_t motorDirectionPin1;
        uint8_t motorDirectionPin2;

        // The amount of time, in microseconds, to wait after a stop command is executed. This is to account for propagation delay.
        uint16_t delayMicros;
};

#endif
