#include "Encoder.h"

void Encoder::init(void (*ISRfunc_)())
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

    ISRfunc = ISRfunc_;
}

Encoder::Encoder(bool isRight_, int8_t B_PIN_, int8_t CLOCK_A_PIN_, int8_t DIR_)
{
    isRight = isRight_;
    B_PIN = B_PIN_;
    CLOCK_A_PIN = CLOCK_A_PIN_;
}

void Encoder::isr()
{
    B = digitalRead(B_PIN);
    ClockA = digitalRead(CLOCK_A_PIN);
    A = ClockA ^ B;
    const uint8_t encNow = (A << 1) | B; // xxxxxxAB = (xxxxxxxA << 1) | xxxxxxxB
    Counter += Ett[encOld][encNow];
    encOld = encNow;
}

void Encoder::tick()
{
    noInterrupts();
    const int deltaEnc = Counter;
    Counter = 0;
    interrupts();
    Phi += deltaEnc * TICK_TO_RAD;
}

void Encoder::addCounter(int16_t counter_)
{
    Counter += counter_;
}