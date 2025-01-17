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
    Motor motor;
    PIreg motReg;
public:
    const float& realSpeed;
    ServoMotor(Encoder* enc_, VelEstimator* est_) : realSpeed(est_->q_omega), motReg(1 / (2 * K_MOTOR * T_u), T_u, 1)//последнее - 1 Вольт
    {
        enc = enc_;
        est = est_;
    }
    void init(int DIR, int dirPin, int pwmPin);
    void tick(float batteryVolts);
    void drive(float omega); // [рад/с]
};