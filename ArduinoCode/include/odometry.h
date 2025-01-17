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
    void update(float omegaL, float omegaR);
};