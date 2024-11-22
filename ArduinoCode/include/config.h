#pragma once
#include <Arduino.h>

#define Ts_us 20000 // Период квантования в [мкс]
#define Ts_s (Ts_us / 1000000.0) // Период квантования в [с]

#define ENC_PPR 48
#define GEAR_RATIO 30
#define TICK_TO_RAD (2.0 * M_PI / (ENC_PPR * GEAR_RATIO))
#define WHEEL_RADIUS 0.0165
#define ROBOT_WIDTH 0.082

#define LEFT_CLOCK_A_PIN 2
#define LEFT_B_PIN 4
#define LEFT_ENC_DIR 1

#define RIGHT_CLOCK_A_PIN 3
#define RIGHT_B_PIN 5
#define RIGHT_ENC_DIR -1

#define K_FILTER (0.5)