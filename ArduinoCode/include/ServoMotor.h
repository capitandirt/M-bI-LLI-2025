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
    const float& realSpeed;
    const float& phi;
    const float& vel;
    const float& u;
    ServoMotor(Encoder* enc_, VelEstimator* est_, Motor* motor_, PIreg* motReg_) : realSpeed(est_->q_omega), phi(enc->q_Phi), vel(est->q_omega), u(motReg->uOut) //последнее - 1 Вольт
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
    ServoMotor& drive(float omega, float batteryVolts) // [рад/с]
    {
        enc->tick();
        motor->tick(batteryVolts);
        est->tick();

        motReg->tick(omega - realSpeed);
        Serial.println(String(omega) + " " + String(realSpeed));
        motor->drive(motReg->uOut);
        
        //motor.drive(4);
        return *this;
    }
};