#include "velEstimator.h"

VelEstimator::VelEstimator(Encoder* enc_)
{
    enc = enc_;
}

float VelEstimator::omegaRawEstimator(float phi)
{
    float wRaw = (phi - phiOld) / Ts_s;
    phiOld = phi;
    return wRaw;
}

float VelEstimator::lowPassFilter(float omegaRaw)
{
    return (omegaRaw - omega) * K_FILTER;
}

void VelEstimator::tick()
{
    const float phi = enc->q_Phi;
    const float omegaRaw = omegaRawEstimator(phi);
    omega += lowPassFilter(omegaRaw);
}