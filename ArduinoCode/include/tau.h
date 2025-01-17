#pragma once
#include "config.h"

class Integrator
{
private:
    float private_out = 0;
public:
    const float& out = private_out;
    void tick(float in);
};

class PIreg
{
private:
    float u, K, T, maxI;
    Integrator I;
public:
    float const &uOut = u;
    PIreg(float K_, float T_, float maxI_);
    void tick(float err);
};