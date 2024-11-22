#include "Globals.h"

EncoderParameters left_ep = 
{
    .CLOCK_A_PIN = LEFT_CLOCK_A_PIN,
    .B_PIN = LEFT_B_PIN,
    .DIR = LEFT_ENC_DIR,
    .ISRfunc = leftISR
};
EncoderParameters right_ep = 
{
    .CLOCK_A_PIN = RIGHT_CLOCK_A_PIN,
    .B_PIN = RIGHT_B_PIN,
    .DIR = RIGHT_ENC_DIR,
    .ISRfunc = rightISR
};


Encoder leftE(&left_ep);
Encoder rightE(&right_ep);

VelEstimator leftEst(&leftE), rightEst(&rightE);