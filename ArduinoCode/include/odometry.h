#pragma once
#include "config.h"
#include "tau.h"

void polarSpeedToMotorSpeed(float Vin, float theta_i_in, float* omega_l, float* omega_r)
{
    // Расчет управляющих воздействий
    float W_f_in = Vin / WHEEL_RADIUS, 
        W_delta_in = theta_i_in  * ROBOT_WIDTH / WHEEL_RADIUS;
    //микшер
    *omega_l = W_f_in - W_delta_in / 2, 
    *omega_r = W_f_in + W_delta_in / 2;
}

class State
{
private:
    Integrator
    X,
    Y,
    Theta;

    float
    vL = 0,
    vR = 0,
    vX,
    vY,
    v;
public:
    const float &x, &y, &theta;
    State() : theta(Theta.out), x(X.out), y(Y.out) {}
    
    void update(float omegaL, float omegaR)
    {
        vL = omegaL * WHEEL_RADIUS;
        vR = omegaR * WHEEL_RADIUS;

        float theta_i = (vR - vL) / ROBOT_WIDTH; //в этом вычислении опускается тангенс угла, тк tg(x) ~= x на малых углах
        Theta.tick(theta_i);

        v = (vR + vL) / 2;
        vX = v * cos(theta);
        vY = v * sin(theta);

        X.tick(vX);
        Y.tick(vY);
    }
};