#include "tau.h"

void Integrator::tick(float in)
{
    private_out += in * Ts_s;
}

void PIreg::tick(float err)
{
    float Kp = K;
    float Ki = K / T;
    if(abs(I.out + err * Ts_s) < maxI / Ki) I.tick(err);
    u = Kp * err + Ki * I.out;
}
PIreg::PIreg(float K_, float T_, float maxI_)
{
    K = K_;
    T = T_;
    maxI = maxI_;
}