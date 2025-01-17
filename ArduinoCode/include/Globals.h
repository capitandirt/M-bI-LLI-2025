#pragma once
#include <Arduino.h>
#include "Encoder.h"
#include "encISR.h"
#include "velEstimator.h"
#include "odometry.h"
#include "Battery.h"
#include "FunctionalCelector.h"
#include "Motor.h"
#include "ServoMotor.h"

extern Encoder leftE, rightE;
extern State state;
extern Battery battery;
extern FunctionalCelector funcCelect;
extern ServoMotor leftMotor, rightMotor;
extern VelEstimator leftVelEst, rightVelEst;