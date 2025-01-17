#pragma once
#include "Encoder.h"

class VelEstimator
{
private:
    float phiOld, omega = 0;
    Encoder* enc;
    float omegaRawEstimator(float phi);
    float lowPassFilter(float wRaw);
public:
    const float& q_omega = omega; 
    VelEstimator(Encoder* enc_);
    
    void tick();
};