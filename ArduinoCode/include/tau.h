#pragma once
#include "config.h"

class Integrator
{
private:
    float private_out = 0;
public:
    const float& out = private_out;
    void tick(float in)
    {
        private_out += in * Ts_s;
    }
};

class PIreg
{
private:
    float u, K, T, maxI;
    Integrator I;
public:
    float const &uOut = u;
    PIreg(float K_, float T_, float maxI_)
    {
        K = K_;
        T = T_;
        maxI = maxI_;
    }
    void tick(float err)
    {
        float Kp = K;
        float Ki = K / T;
        if(abs(I.out + err * Ts_s) < maxI / Ki) I.tick(err);
        u = Kp * err + Ki * I.out;
    }
};