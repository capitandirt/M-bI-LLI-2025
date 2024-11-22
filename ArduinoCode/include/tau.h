#include "config.h"

class Integrator
{
private:
    float out = 0;
public:
    const float& q_out = out;
    void tick(float in);
};