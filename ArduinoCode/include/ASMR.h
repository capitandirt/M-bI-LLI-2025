#include "config.h"
#pragma once

struct Sensors
{
    float time;
};
struct MotionState
{
    float v_f0;
    float theta_i0;
    float isComplete;
};

typedef void (*Cyclogram)(MotionState*, Sensors);
#define CYCLOGRAM(name) void name(MotionState* ms, Sensors s)

CYCLOGRAM(STOP)
{
    ms->v_f0 = 0;
    ms->theta_i0 = 0;
    ms->isComplete = false;
}

CYCLOGRAM(IDLE)
{
    ms->v_f0 = 0;
    ms->theta_i0 = 0;
    ms->isComplete = true;
}

CYCLOGRAM(FWD)
{
    ms->v_f0 = FORW_SPEED;
    ms->theta_i0 = 0;
    
    if(s.time > CELL_LENGTH / FORW_SPEED)
    {
        ms->isComplete = true;
    }
    else ms->isComplete = false;
}

CYCLOGRAM(SS90EL)
{
    int dir = 1; // 1 - право, -1 - лево

    float R = 0.09; //радиус поворота
    ms->v_f0 = FORW_SPEED;
    float theta_i = FORW_SPEED / R;

    float forwTime = (CELL_LENGTH / 2 - R) / FORW_SPEED;
    float circTime = 2 * PI * R / theta_i;
    if(s.time < forwTime || s.time > forwTime + circTime) ms->theta_i0 = 0;
    else ms->theta_i0 = theta_i;

    if(s.time > 2 * forwTime + circTime) ms->isComplete = true;
}

class ASMR
{
private:
    Cyclogram cycCicle[CYC_BUF_SIZE] = {IDLE};
    int progCounter = 0, progEnd = 0;
    uint32_t lastProgStart = 0;
    int rotMod(int in)
    {
        return in % CYC_BUF_SIZE;
    }
public:
    void addCyc(Cyclogram cyc)
    {
        progEnd = rotMod(progEnd + 1);
        cycCicle[progEnd] = cyc;
    }

    void exec()
    {
        Sensors s = {0};
        MotionState ms = {0};

        s.time = millis() / 1000.0 - lastProgStart;

        cycCicle[progCounter](&ms, s);
        
        //Serial.println(String(ms.v_f0) + " " + String(ms.theta_i0) + " " + String(ms.isComplete));
        if(ms.isComplete)
        {
            progCounter = rotMod(progCounter + 1);
            lastProgStart = millis() / 1000.0;
        }
    }
};