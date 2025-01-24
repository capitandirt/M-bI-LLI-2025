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
    
    MotionControl& tick(float Vin, float theta_i_in, float batteryVolts)
    {
        // Расчет управляющих воздействий
        float W_f_in = Vin / WHEEL_RADIUS, 
            W_delta_in = theta_i_in  * ROBOT_WIDTH / WHEEL_RADIUS;
        //микшер
        left->drive(W_f_in - W_delta_in / 2, batteryVolts); 
        right->drive(W_f_in + W_delta_in / 2, batteryVolts);
        return *this;
    }
};