#pragma once
#include "Arduino.h"
#include "config.h"

class Motor
{
private:
    int DIR, dirPin, pwmPin;
    float batteryVolts;
public:
    void init(int DIR_, int dirPin_, int pwmPin_)
    {
        DIR = DIR_;
        dirPin = dirPin_;
        pwmPin = pwmPin_;
    }
    void drive(float u)//[В]
    {   
        int pwm = 255 * (u / batteryVolts);
        pwm = constrain(pwm, -255, 255);
        
        if(pwm >= 0)
        {
            digitalWrite(dirPin, DIR);
            analogWrite(pwmPin, pwm);
        }
        else
        {
            digitalWrite(dirPin, !DIR);
            analogWrite(pwmPin, -pwm);
        }
    }
    void setBatteryVolts(float batteryVolts_) 
    {
        batteryVolts = batteryVolts_;
    }
};