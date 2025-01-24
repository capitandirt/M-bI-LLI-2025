#pragma once
#include "ServoMotor.h"
class MotionControl
{
private:
    ServoMotor *left, *right;
public:
    MotionControl(ServoMotor* left_, ServoMotor* right_)
    {
        left = left_;
        right = right_;
    }
    
    MotionControl& tick(float Vin, float theta_i_in)
    {
        // Расчет управляющих воздействий
        float W_f_in = Vin / WHEEL_RADIUS;
        float W_delta_in = theta_i_in  * ROBOT_WIDTH / WHEEL_RADIUS;
        //микшер
        left->drive(W_f_in - W_delta_in / 2); 
        right->drive(W_f_in + W_delta_in / 2);
        return *this;
    }
};