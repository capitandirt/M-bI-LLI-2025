#pragma once
#include "Encoder.h"

class VelEstimator
{
private:
    float phiOld, w = 0;
    Encoder* enc;
public:
    VelEstimator(Encoder* enc_)
    {
        enc = enc_;
    }
    float WRawEstimator(float phi)
    {
        float wRaw = (phi - phiOld) / Ts_s;
        phiOld = phi;
        return wRaw;
    }
    void lowPassFilter(float wRaw)
    {
        w += (wRaw - w) * K_FILTER;
    }
    void tick()
    {
        const float phi = enc->cPhi;
        const float wRaw = WRawEstimator(phi);
        lowPassFilter(wRaw);
    }
};