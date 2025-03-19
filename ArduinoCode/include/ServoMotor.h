#pragma once
#include "Motor.h"
#include "Encoder.h"
#include "velEstimator.h"
#include "tau.h"
#include "config.h"
class ServoMotor
{
private:
    Encoder* enc;
    VelEstimator* est;
    Motor* motor;
    PIreg* motReg;
public:
    const float phi() {return enc->q_Phi;}
    const float vel() {return est->q_omega;}
    const float u() {return motReg->uOut;}
    const float realSpeed() {return est->q_omega;};
    ServoMotor(Encoder* enc_, VelEstimator* est_, Motor* motor_, PIreg* motReg_) //последнее - 1 Вольт
    {
        enc = enc_;
        est = est_;
        motor = motor_;
        motReg = motReg_;
    }
    void init(int DIR, int dirPin, int pwmPin)
    {
        if(DIR == -1) DIR = 0;
        enc->init();
        motor->init(DIR, dirPin, pwmPin);
    }   
    ServoMotor& drive(float omega) // [рад/с]
    {
        enc->tick();
        est->tick(enc->q_Phi);

        motReg->tick(omega - est->q_omega);

        //Serial.println(String(omega) + " " + String(realSpeed()) + " " + String(motReg->uOut));
        motor->drive(motReg->uOut);
        
        //motor.drive(4);
        return *this;
    }
};