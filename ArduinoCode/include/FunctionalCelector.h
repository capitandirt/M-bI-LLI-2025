#include <Arduino.h>
#include "config.h"

class FunctionalCelector
{
private:
    uint8_t functionOut = 0;
    int decodeFunctionSwitch(int functionValue);
public:
    uint8_t& function = functionOut;
    void tick();
};