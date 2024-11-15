#pragma once
#include <Arduino.h>
#include "Encoder.h"

volatile int16_t GleftCounter = 0;
float GleftPhi = 0;
volatile int16_t GrightCounter = 0;
float GrightPhi = 0;

Encoder leftE(0, LEFT_B_PIN, LEFT_CLOCK_A_PIN, LEFT_ENC_DIR);
Encoder rightE(1, RIGHT_B_PIN, RIGHT_CLOCK_A_PIN, RIGHT_ENC_DIR);