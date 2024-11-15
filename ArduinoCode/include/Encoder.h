#pragma once
#include <Arduino.h>
#include "config.h"

class Encoder
{
private:
    int8_t Ett[4][4]; //сначала старое, потом новое
    int8_t B_PIN, CLOCK_A_PIN;
    int8_t DIR;
    float Phi;
    volatile int16_t Counter;
    bool isRight;
    void (*ISRfunc)();
    uint8_t encOld;
    uint8_t B;
    uint8_t ClockA;
    uint8_t A;
public:
    const int &cPhi = Phi;
    Encoder(bool isRight_, int8_t B_PIN_, int8_t CLOCK_A_PIN_, int8_t DIR_);
    void init(void (*ISRfunc_)());
    void addCounter(int16_t counter_);

    void tick();
    void isr();
};
