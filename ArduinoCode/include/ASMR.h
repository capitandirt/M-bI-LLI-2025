#pragma once
#include "config.h"
#include "odometry.h"
#include "MotionControl.h"

struct Sensors
{
    float time;
    State state;
};
struct MotionState
{
    float v_f0;
    float theta_i0;
    float isComplete;
};

/* РАСШИФРОВКА НАЗВАНИЙ ПОВОРОТОВ
SS90EL
S - from straight (0 / 90... градусов поворот) или D - from diagonal
S - to straight или to diagonal
90 - градус поворота
E - explorer или S - smooth
L - левый или R - правый
*/


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
    
    if(s.state.dist() > CELL_LENGTH)
    {
        ms->isComplete = true;
    }
    else ms->isComplete = false;
}
CYCLOGRAM(FWD_HALF)
{
    ms->v_f0 = FORW_SPEED;
    ms->theta_i0 = 0;
    
    if(s.state.dist() > CELL_LENGTH / 2)
    {
        ms->isComplete = true;
    }
    else ms->isComplete = false;
}

//search turns 90
CYCLOGRAM(SS90EL)
{
    const float R = 0.07; //радиус поворота
    ms->v_f0 = FORW_SPEED;
    float theta_i = FORW_SPEED / R;

    float forwDist = CELL_LENGTH / 2 - R;
    float circleDis = (2 * PI * R) / 4; // 90 - четверть окружности #КОСТЫЛЬ
    // float forwTime = (CELL_LENGTH / 2 - R) / FORW_SPEED;
    // float circTime = 2 * PI * R / 4 / FORW_SPEED;

    if(s.state.dist() > forwDist && s.state.dist() < forwDist + circleDis) ms->theta_i0 = theta_i;
    else ms->theta_i0 = 0;
    // if(s.time < forwTime || s.time > forwTime + circTime) ms->theta_i0 = 0;
    // else ms->theta_i0 = theta_i * dir;

    if(s.state.dist() > 2 * forwDist + circleDis) ms->isComplete = true;
    //if(s.time > 2 * forwTime + circTime) ms->isComplete = true;
}
CYCLOGRAM(SS90ER)
{
    const float R = 0.07; //радиус поворота
    ms->v_f0 = FORW_SPEED;
    float theta_i = FORW_SPEED / R;

    const float forwDist = CELL_LENGTH / 2 - R;
    const float circleDis = (2 * PI * R) / 4; // 90 = четверть окружности
    // float forwTime = (CELL_LENGTH / 2 - R) / FORW_SPEED;
    // float circTime = 2 * PI * R / 4 / FORW_SPEED;

    if(s.state.dist() > forwDist && s.state.dist() < forwDist + circleDis) ms->theta_i0 = -theta_i;
    else ms->theta_i0 = 0;
    // if(s.time < forwTime || s.time > forwTime + circTime) ms->theta_i0 = 0;
    // else ms->theta_i0 = theta_i * dir;

    if(s.state.dist() > 2 * forwDist + circleDis) ms->isComplete = true;
    //if(s.time > 2 * forwTime + circTime) ms->isComplete = true;
}

//45 turns
CYCLOGRAM(SD45SL)
{
    const float forwDist = CELL_LENGTH / 4; // путь до начала поворота, максимум - CELL_LENGTH / 2
    const float forwDist2 = M_SQRT2 * CELL_LENGTH / 2 - (CELL_LENGTH / 2 - forwDist); //путь после конца поворота
    const float R = (CELL_LENGTH / 2 - forwDist) * (1 + M_SQRT2); //радиус поворота, максимум - 0.21 (CELL_LENGTH / 2 * (1 + sqrt(2)))

    const float circleDis = (2 * PI * R) / 8; // 45 = 1/8 окружности
    ms->v_f0 = FORW_SPEED;
    float theta_i = FORW_SPEED / R;

    if(s.state.dist() > forwDist && s.state.dist() < forwDist + circleDis) ms->theta_i0 = theta_i;
    else ms->theta_i0 = 0;

    if(s.state.dist() > forwDist + circleDis + forwDist2) ms->isComplete = true;
}
CYCLOGRAM(SD45SR)
{
    const float forwDist = CELL_LENGTH / 4; // путь до начала поворота, максимум - CELL_LENGTH / 2
    const float forwDist2 = M_SQRT2 * CELL_LENGTH / 2 - (CELL_LENGTH / 2 - forwDist); //путь после конца поворота
    const float R = (CELL_LENGTH / 2 - forwDist) * (1 + M_SQRT2); //радиус поворота, максимум - 0.21 (CELL_LENGTH / 2 * (1 + sqrt(2)))

    const float circleDis = (2 * PI * R) / 8; // 45 = 1/8 окружности
    ms->v_f0 = FORW_SPEED;
    float theta_i = FORW_SPEED / R;

    if(s.state.dist() > forwDist && s.state.dist() < forwDist + circleDis) ms->theta_i0 = -theta_i;
    else ms->theta_i0 = 0;

    if(s.state.dist() > forwDist + circleDis + forwDist2) ms->isComplete = true;
}
CYCLOGRAM(DS45SL)
{
    const float forwDist = CELL_LENGTH / 4; // путь до начала поворота, максимум - CELL_LENGTH / 2
    const float forwDist2 = M_SQRT2 * CELL_LENGTH / 2 - (CELL_LENGTH / 2 - forwDist); //путь после конца поворота
    const float R = (CELL_LENGTH / 2 - forwDist) * (1 + M_SQRT2); //радиус поворота, максимум - 0.21 (CELL_LENGTH / 2 * (1 + sqrt(2)))

    const float circleDis = (2 * PI * R) / 8; // 45 = 1/8 окружности
    ms->v_f0 = FORW_SPEED;
    float theta_i = FORW_SPEED / R;

    if(s.state.dist() > forwDist2 && s.state.dist() < forwDist2 + circleDis) ms->theta_i0 = theta_i;
    else ms->theta_i0 = 0;

    if(s.state.dist() > forwDist + circleDis + forwDist2) ms->isComplete = true;
}
CYCLOGRAM(DS45SR)
{
    const float forwDist = CELL_LENGTH / 4; // путь до начала поворота, максимум - CELL_LENGTH / 2
    const float forwDist2 = M_SQRT2 * CELL_LENGTH / 2 - (CELL_LENGTH / 2 - forwDist); //путь после конца поворота
    const float R = (CELL_LENGTH / 2 - forwDist) * (1 + M_SQRT2); //радиус поворота, максимум - 0.21 (CELL_LENGTH / 2 * (1 + sqrt(2)))

    const float circleDis = (2 * PI * R) / 8; // 45 = 1/8 окружности
    ms->v_f0 = FORW_SPEED;
    float theta_i = FORW_SPEED / R;

    if(s.state.dist() > forwDist2 && s.state.dist() < forwDist2 + circleDis) ms->theta_i0 = -theta_i;
    else ms->theta_i0 = 0;

    if(s.state.dist() > forwDist + circleDis + forwDist2) ms->isComplete = true;
}
CYCLOGRAM(SD135SR)
{
    const float R = 0.07; //радиус поворота
    ms->v_f0 = FORW_SPEED;
    float theta_i = FORW_SPEED / R;

    const float forwDist1 = 1.5 * CELL_LENGTH - R * (1 + M_SQRT2);
    const float forwDist2 = R + M_SQRT2 * CELL_LENGTH - R * (M_SQRT2 + 2);
    const float circleDis = (2 * PI * R) * (135.0 / 360); // 90 = четверть окружности

    if(s.state.dist() > forwDist1 && s.state.dist() < forwDist1 + circleDis) ms->theta_i0 = -theta_i;
    else ms->theta_i0 = 0;
    if(s.state.dist() > forwDist1 + circleDis + forwDist2) ms->isComplete = true;
}
CYCLOGRAM(SS180S)
{
    ms->v_f0 = 0;
    float theta_i = FORW_SPEED / ROBOT_WIDTH / 2;

    if(s.state.theta() > PI) ms->isComplete = true;
}


class ASMR
{
private:
    //State* state;
    MotionControl* motionControl;
    Cyclogram cycCicle[CYC_BUF_SIZE] = {IDLE};
    uint8_t progCounter = 0, progEnd = 0;
    uint32_t lastProgStart = 0;
    uint8_t rotMod(uint8_t in)
    {
        return in % CYC_BUF_SIZE;
    }
public:
    ASMR(MotionControl* motionControl_) : motionControl(motionControl_){}
    void addCyc(Cyclogram cyc)
    {
        progEnd = rotMod(progEnd + 1);
        cycCicle[progEnd] = cyc;
    }

    bool exec()
    {
        static Sensors s = {0};
        MotionState ms = {0};

        s.time = millis() / 1000.0 - lastProgStart;

        cycCicle[progCounter](&ms, s);
        float omegaL, omegaR;
        polarSpeedToMotorSpeed(ms.v_f0, ms.theta_i0, &omegaL, &omegaR);
        s.state.update(omegaL, omegaR);
        
        //Serial.println(String(ms.v_f0) + " " + String(ms.theta_i0) + " " + String(ms.isComplete));
        if(ms.isComplete)
        {
            progCounter = rotMod(progCounter + 1);
            lastProgStart = millis() / 1000.0;
            s.state.reset();
        }
        
        if(cycCicle[progCounter] != STOP) 
        {
            //Serial.println(String(omegaL) + " " + String(omegaR) + " " + String(ms.v_f0) + " " + String(ms.theta_i0) + " " + String(s.state.dist()));
        }
        motionControl->tick(ms.v_f0, ms.theta_i0);
        if(ms.isComplete) return true;
        else return false;
    }
};