#pragma once
#include <Arduino.h>
#include "config.h"

struct EncoderParameters
{
    int CLOCK_A_PIN;
    int B_PIN;
    int DIR;
    void (*ISRfunc)();
};

class Encoder : public EncoderParameters
{
private:
    int8_t Ett[4][4] = {0}; //сначала старое, потом новое
    volatile int16_t Counter = 0;
    volatile uint8_t encOld = 0;

    float Phi = 0;
public:
    const float &q_Phi = Phi;
    
    Encoder(EncoderParameters *ecp) : EncoderParameters(*ecp){}
    void init();

    void tick();
    void isr();
};
