#include "motor.h"

void Motor::init(int DIR_, int dirPin_, int pwmPin_)
{
    DIR = DIR_;
    dirPin = dirPin_;
    pwmPin = pwmPin_;
}

void Motor::drive(float u)//[В]
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

void Motor::tick(float batteryVolts_) 
{
    batteryVolts = batteryVolts_;
}