#include "tau.h"

void Integrator::tick(float in)
{
    out += in * Ts_s;
}