#include <iostream>
#include <iomanip>
#include <stdio.h>

#include <wiringPiI2C.h>
#include <wiringPi.h>

#include "motorkit.h"
#include "motor.h"
#include "PWM.h"
#include "MotorConfigStruct.h"


// # Motor 1 is channels 9 and 10 with 8 held high.
// # Motor 2 is channels 11 and 12 with 13 held high.
// # Motor 3 is channels 3 and 4 with 2 held high.
// # Motor 4 is channels 5 and 6 with 7 held high.


Motorkit::Motorkit() {
    pulseWidthModulator = new PWM(0x60);
}

Motorkit::~Motorkit() {
    for (int i = 0; i < 4; i++) {
        if (motors[i] != nullptr) {
            delete motors[i];
        }
    }
 
    delete pulseWidthModulator;
}

int Motorkit::initMotor(int motorNumber) {
    
    MCS motor;
    
    if (motorNumber > 4 || motorNumber < 1) {
        printf("Invalid motor number '%d'. Must be between 1 and 4 inclusive. \n", motorNumber);
        return 1;
    }
    
    if (enabledMotors[motorNumber - 1] != 0) {
        printf("Motor %d already initialized \n", motorNumber);
        return -1;
    }
    
    switch(motorNumber){
        // Motor 1
        case 1:
            motor.enable = 8;
            motor.input1 = 10;
            motor.input2 = 9;
            motor1 = new Motor(motor, pulseWidthModulator);
            motors[0] = motor1;
            enabledMotors[0] = 1;
            return 0;
        // Motor 2
        case 2:
            motor.enable = 13;
            motor.input1 = 11;
            motor.input2 = 12;
            motor2 = new Motor(motor, pulseWidthModulator);
            motors[1] = motor2;
            enabledMotors[1] = 2;
            return 0;
        // Motor 3
        case 3:
            motor.enable = 2;
            motor.input1 = 4;
            motor.input2 = 3;
            motor3 = new Motor(motor, pulseWidthModulator);
            motors[2] = motor3;
            enabledMotors[2] = 3;
            return 0;
        // Motor 4
        case 4:
            motor.enable = 7;
            motor.input1 = 5;
            motor.input2 = 6;
            motor4 = new Motor(motor, pulseWidthModulator);
            motors[3] = motor4;
            enabledMotors[3] = 4;
            return 0;
    
    }
    
    return -1; 
}

int Motorkit::performTask(int motorNumber, Task t) {
    if (motorNumber > 4 || motorNumber < 1) {
        printf("Invalid motor number '%d'. Must be between 1 and 4 inclusive. \n", motorNumber);
        return -1;
    }
    
    if (enabledMotors[motorNumber - 1] == 0) {
        printf("Motor %d not initialized \n", motorNumber);
        return 1;
    }

    switch (t) {
  
        case FORWARD:
            if (motors[motorNumber - 1]->forward()) {
                return -1;
            }
            return 0;

        case REVERSE:
            if (motors[motorNumber - 1]->reverse()) {
                return -1;
            }
            return 0;

        case STOP:
            if (motors[motorNumber - 1]->stop()) {
                return -1;
            }
            return 0;

        default:
            printf("Error. Supplied motor action is invalid! \n");
            return -1;
    }
}

int Motorkit::setSpeed(int motorNumber, int speed) {
    if (motorNumber > 4 || motorNumber < 1) {
        printf("Invalid motor number '%d'. Must be between 1 and 4 inclusive. \n", motorNumber);
    }
    
    if (enabledMotors[motorNumber - 1] == 0) {
        printf("Motor %d not initialized \n", motorNumber);
        return 1;
    }

    motors[motorNumber - 1]->setSpeed(speed);
    return 0;
}
    
int Motorkit::setDuration(int motorNumber, int duration) {
    if (motorNumber > 4 || motorNumber < 1) {
        printf("Invalid motor number '%d'. Must be between 1 and 4 inclusive. \n", motorNumber);
        return -1;
    }
    
   if (enabledMotors[motorNumber - 1] == 0) {
        printf("Motor %d not initialized \n", motorNumber);
        return -1;
    }

    motors[motorNumber - 1]->setDuration(duration);
    return 0;
}
    
    
