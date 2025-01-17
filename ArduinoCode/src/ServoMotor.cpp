#include "ServoMotor.h"

void ServoMotor::init(int DIR, int dirPin, int pwmPin)
{
    if(DIR == -1) DIR = 0;
    enc->init();
    motor.init(DIR, dirPin, pwmPin);
}   

void ServoMotor::tick(float batteryVolts)
{
    enc->tick();
    motor.tick(batteryVolts);
    est->tick();
}   

void ServoMotor::drive(float omega) // [рад/с]
{
    motReg.tick(omega - realSpeed);
    
    motor.drive(motReg.uOut);
    
    //motor.drive(4);
}