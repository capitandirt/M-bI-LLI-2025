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
    void init()
    {
        // Настройка пинмодов для прерывающихс пинов левого

        pinMode(CLOCK_A_PIN, INPUT);
        pinMode(B_PIN, INPUT);
        
        noInterrupts();

        attachInterrupt(
            digitalPinToInterrupt(CLOCK_A_PIN), 
            ISRfunc, 
            CHANGE
        );

        Ett[0b00][0b01] = -DIR;
        Ett[0b01][0b11] = -DIR;
        Ett[0b11][0b10] = -DIR;
        Ett[0b10][0b00] = -DIR;

        Ett[0b00][0b10] = DIR;
        Ett[0b10][0b11] = DIR;
        Ett[0b11][0b01] = DIR;
        Ett[0b01][0b00] = DIR;

        interrupts();
    }

    void tick()
    {
        noInterrupts();
        const int deltaEnc = Counter;
        Counter = 0;
        interrupts();

        Phi += deltaEnc * TICK_TO_RAD;
    }
    void isr()
    {
        const uint8_t B = digitalRead(B_PIN);

        const uint8_t ClockA = digitalRead(CLOCK_A_PIN);
        const uint8_t A = ClockA ^ B;

        const uint8_t encNow = (A << 1) | B; // xxxxxxAB = (xxxxxxxA << 1) | xxxxxxxB

        Counter += Ett[encOld][encNow];
        encOld = encNow;
    }
};
