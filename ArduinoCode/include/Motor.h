#pragma once
#include "Arduino.h"
#include "config.h"

class Motor
{
private:
    int DIR, dirPin, pwmPin;
    float batteryVolts;
public:
    void init(int DIR_, int dirPin_, int pwmPin_);
    void drive(float u);
    void tick(float batteryVolts_);
};