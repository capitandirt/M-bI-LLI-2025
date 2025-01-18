#pragma once
#include "config.h"
#include "tau.h"
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
    State() : theta(Theta.out), x(X.out), y(Y.out) 
    {

    }
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