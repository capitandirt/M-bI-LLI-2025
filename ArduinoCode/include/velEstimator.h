#pragma once
#include "Encoder.h"

class VelEstimator
{
private:
    float phiOld = 0, omega = 0;
    float omegaRawEstimator(float phi)
    {
        float wRaw = (phi - phiOld) / Ts_s;
        phiOld = phi;
        return wRaw;
    }
    float lowPassFilter(float omegaRaw)
    {
        return omega + (omegaRaw - omega) * K_FILTER;
    }
public:
    const float& q_omega = omega; //скорость в [единиц / с]
    
    
    VelEstimator& tick(float phi)
    {
        const float omegaRaw = omegaRawEstimator(phi);
        omega = lowPassFilter(omegaRaw);

        return *this;
    }
};