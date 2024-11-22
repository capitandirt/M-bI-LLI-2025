#include "velEstimator.h"

VelEstimator::VelEstimator(Encoder* enc_)
{
    enc = enc_;
}

float VelEstimator::WRawEstimator(float phi)
{
    float wRaw = (phi - phiOld) / Ts_s;
    phiOld = phi;
    return wRaw;
}

void VelEstimator::lowPassFilter(float wRaw)
{
    w += (wRaw - w) * K_FILTER;
}

void VelEstimator::tick()
{
    const float phi = enc->q_Phi;
    const float wRaw = WRawEstimator(phi);
    lowPassFilter(wRaw);
}