#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include "motor.h"
#include "MotorConfigStruct.h"
#include "PWM.h"

/*
        # An explanation of motor circuitry and operation.

        ## Motor1 functions:
        
                ### Enable:
                * 12v supplied = enabled
                * ground = Disabled
                * PWM = Speed control
                
                ### Forward:
                * input1 = 12 volts
                * input2 = Ground

                ### Reverse:
                * input1 = Ground
                * input2 = 12 volts
        
        ## Motor2 functions:

                ### Enable:
                * 12v supplied = enabled
                * ground = Disabled
                * PWM = Speed control
                
                ### Forward:
                * input1 = 12 volts
                * input2 = Ground

                ### Reverse:
                * input1 = Ground
                * input2 = 12 volts 
        
        ## PWM
        * controls speed of motor by sending pulses to enable input
        ### Faster
        * Wider pulses
        * Hold high for full speed
        ### Slower
        * Send shorter wavelength pulses
        * HOld low to stop

*/

Motor::Motor(MCS motor, PWM* pulseWidthModulator) {
        this->pulseWidthModulator = pulseWidthModulator;
        Enable = motor.enable;
        IN1 = motor.input1;
        IN2 = motor.input2;
        speed = 0;
        duration = 0;
        release();
      
}

int Motor::release() {
        
        if (pulseWidthModulator->setPin(IN2, 0) || pulseWidthModulator->setPin(IN1, 0)) {
                return -1;
        }
    
        return 0;
}

int Motor::forward() {

        if (pulseWidthModulator->setPin(IN2, 0) || pulseWidthModulator->setPin(IN1, 1)) {
                return -1;
        }
        
        if (duration > 0){
                runMotor();
        }
        

        return 0;

}

int Motor::reverse() {

        if (pulseWidthModulator->setPin(IN2, 1) || pulseWidthModulator->setPin(IN1, 0)) {
                return -1;
        }

        if (duration > 0){
                runMotor();
        }
        
        return 0;
}

void Motor::runMotor() {
     delay(duration);
     release();   
}

int Motor::stop() {
        return release();
}


int Motor::updateSpeed() {
        
        return pulseWidthModulator->setPWM(Enable, 0, speed * 16);
}

void Motor::setSpeed(int s) {
        bool upperbound = 255 >= s;
        bool lowerbound = 0 <= s;
        if(!upperbound || !lowerbound){
                printf("Error. Bounds must be between 0 and 255 inclusive. Received %d. \n", speed);
                return;
        }
        speed = s;
        //updateSpeed();
        pulseWidthModulator->setPWM(Enable, 0, speed * 16);
}

void Motor::setDuration(int d) {
        duration = d;
}

int Motor::getSpeed() {
        return speed;
}

int Motor::getDuration() {
        return duration;
}