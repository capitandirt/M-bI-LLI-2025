#pragma once
#include "Encoder.h"

class VelEstimator
{
private:
    float phiOld, w = 0;
    Encoder* enc;
    float WRawEstimator(float phi);
    void lowPassFilter(float wRaw);
public:
    const float& q_w = w; 
    VelEstimator(Encoder* enc_);
    
    void tick();
};