#pragma once

#include <wiringPiI2C.h>
#include <time.h>
#include <math.h>

class PWM {
    public:
        

        const short PWM_M1_PWM = 8;
        const short PWM_M1_IN2 = 9;
        const short PWM_M1_IN1 = 10;
        const short PWM_M2_PWM = 13;
        const short PWM_M2_IN2 = 12;
        const short PWM_M2_IN1 = 11;
        const short PWM_M3_PWM = 2;
        const short PWM_M3_IN2 = 3;
        const short PWM_M3_IN1 = 4;
        const short PWM_M4_PWM = 7;
        const short PWM_M4_IN2 = 6;
        const short PWM_M4_IN1 = 5;

        const short PWM_FREQUENCY = 1600.0;
        const short PWM_PRESCALE = 0xFE;

        const short PWM_MODE1 = 0x00;
        const short PWM_MODE2 = 0x01;
        const short PWM_LED0_ON_L = 0x06;
        const short PWM_LED0_ON_H = 0x07;
        const short PWM_LED0_OFF_L = 0x08;
        const short PWM_LED0_OFF_H = 0x09;

        const short PWM_RESTART = 0x80;
        const short PWM_SLEEP = 0x10;
        const short PWM_ALLCALL = 0x01;
        const short PWM_INVRT = 0x10;
        const short PWM_OUTDRV = 0x04;

        const short PWM_ALL_LED_ON_L = 0xFA;
        const short PWM_ALL_LED_ON_H = 0xFB;
        const short PWM_ALL_LED_OFF_L = 0xFC;
        const short PWM_ALL_LED_OFF_H = 0xFD;

        int i2cIdentifier = 3;

        PWM(unsigned short i2c_address);
        int setAllPWM(unsigned short on, unsigned short off);
        int setPWM(unsigned short pin, unsigned short on, unsigned short off);
        int setPin(unsigned short pin, unsigned short value);
        int getI2cIdentifier();
        
    private:
        
};
