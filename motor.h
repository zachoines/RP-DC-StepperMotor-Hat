#pragma once
#include "PWM.h"
#include "MotorConfigStruct.h"

class Motor {

private:
    int Enable = 0;
    int IN1 = 0;
    int IN2 = 0;
    int speed = 0;
    int duration = 0;

    PWM* pulseWidthModulator = nullptr;

    int release();
    int updateSpeed();
    void runMotor();

public:
    // Default constructor. Pass in motor config.
    Motor(MCS motor, PWM* pulseWidthModulator);

    int forward();
    int reverse();
    int stop();
    void setSpeed(int s);
    void setDuration(int d);
    int getSpeed();
    int getDuration();

};

