#pragma once
#include "Globals.h"

extern Encoder leftE;

void leftISR()
{
    leftE.isr();
}

extern Encoder rightE;

void rightISR()
{
    rightE.isr();
}
