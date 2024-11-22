#include "encISR.h"
#include "Globals.h"

void leftISR()
{
    leftE.isr();
    // static uint8_t leftEncOld = 0;
    // const uint8_t leftB = digitalRead(LEFT_B_PIN);
    // const uint8_t leftClockA = digitalRead(LEFT_CLOCK_A_PIN);
    // const uint8_t leftA = leftClockA ^ leftB;

    // const uint8_t leftEncNow = (leftA << 1) | leftB; // xxxxxxAB = (xxxxxxxA << 1) | xxxxxxxB
    // leftE.addCounter(Ett[leftEncOld][leftEncNow]);
    // leftEncOld = leftEncNow;
}

void rightISR()
{
    rightE.isr();
    // static uint8_t rightEncOld = 0;
    // const uint8_t rightB = digitalRead(RIGHT_B_PIN);
    // const uint8_t rightClockA = digitalRead(RIGHT_CLOCK_A_PIN);
    // const uint8_t rightA = rightClockA ^ rightB;

    // const uint8_t RightEncNow = (rightA << 1) | rightB; // xxxxxxAB = (xxxxxxxA << 1) | xxxxxxxB
    // rightE.addCounter(Ett[rightEncOld][RightEncNow]);
    // rightEncOld = RightEncNow;
}