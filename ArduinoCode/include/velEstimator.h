#pragma once
#include "Encoder.h"

class VelEstimator
{
private:
    float phiOld, omega = 0;
    Encoder* enc;
    float omegaRawEstimator(float phi)
    {
        float wRaw = (phi - phiOld) / Ts_s;
        phiOld = phi;
        return wRaw;
    }
    float lowPassFilter(float omegaRaw)
    {
        return (omegaRaw - omega) * K_FILTER;
    }
public:
    const float& q_omega = omega; 
    VelEstimator(Encoder* enc_)
    {
        enc = enc_;
    }
    
    
    VelEstimator& tick()
    {
        const float phi = enc->q_Phi;
        const float omegaRaw = omegaRawEstimator(phi);
        omega += lowPassFilter(omegaRaw);

        return *this;
    }
};