#include "encISR.h"
#include "Globals.h"

void leftISR()
{
    leftE.isr();
}

void rightISR()
{
    rightE.isr();
}