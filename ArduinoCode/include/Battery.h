#include <Arduino.h>
#include "config.h"
class Battery
{
private:
    float batteryVolts;
public:
    Battery() : batteryVolts(0) {}
    const float& volts = batteryVolts;
    void tick();
};





