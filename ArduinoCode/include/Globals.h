#pragma once
#include <Arduino.h>
#include "Encoder.h"
#include "encISR.h"
#include "velEstimator.h"

extern Encoder leftE, rightE;
extern VelEstimator leftEst, rightEst;