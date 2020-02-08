#pragma once

#include "motor.h"
#include "PWM.h"
#include "MotorConfigStruct.h"

enum Task {
   FORWARD,
   REVERSE,
   STOP,
};

class Motorkit
{
     private:
        int enabledMotors[4] = { 0 };
        Motor* motors[4] = { nullptr };
        int i2c;

        PWM *pulseWidthModulator = nullptr;
        Motor* motor1 = nullptr;
        Motor* motor2 = nullptr;
        Motor* motor3 = nullptr;
        Motor* motor4 = nullptr;
          
     public:

        int speed;
        int duration;

        Motorkit();
        ~Motorkit();

        int initMotor(int motorNumber);
        int performTask(int motorNumber, Task t);
        int setSpeed(int motorNumber, int speed);
        int setDuration(int motorNumber, int duration);
     
};
 
