#pragma once
#include "Encoder.h"

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
//из ВелЭст убрать энкодер, 
