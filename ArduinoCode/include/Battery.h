#include <Arduino.h>
#include "config.h"
class Battery
{
private:
    float batteryVolts;
public:
    Battery() : batteryVolts(0) {}
    const float& volts = batteryVolts;
    Battery& tick() 
    {
        const float batteryDividerRatio = 2.0f;
        int adcValue = analogRead(BATTERY_VOLTS);
        float volts = adcValue * (5.0f * batteryDividerRatio / 1023.0f);
        batteryVolts = volts;
        return *this;
    }
};





