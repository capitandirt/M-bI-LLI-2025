#pragma once
#include <Arduino.h>

#define Ts_us 2000.0 // Период квантования в [мкс] [мс * 1000]
#define Ts_s (Ts_us / 1000000.0) // Период квантования в [с]

#define ENC_PPR 48
#define GEAR_RATIO 30
#define TICK_TO_RAD (2.0 * M_PI / (ENC_PPR * GEAR_RATIO))

//=======ROBOT PARAMETERS====
#define WHEEL_RADIUS 0.0163
#define ROBOT_WIDTH 0.077
#define WHEEL_TO_BUMPER 0.038

//=======LEFT MOTOR PINS=======
//------ENCODER-------
#define LEFT_CLOCK_A_PIN 2
#define LEFT_B_PIN 4
#define LEFT_ENC_DIR 1
//------MOTOR
#define LEFT_MOTOR_POLARITY 1
#define LEFT_MOTOR_DIR 7
#define LEFT_MOTOR_PWM 9

//=======RIGHT MOTOR PINS=======
//------ENCODER-------
#define RIGHT_CLOCK_A_PIN 3
#define RIGHT_B_PIN 5
#define RIGHT_ENC_DIR -1
//------MOTOR
#define RIGHT_MOTOR_POLARITY -1
#define RIGHT_MOTOR_DIR 8
#define RIGHT_MOTOR_PWM 10

//======MOTOR REGULATOR=====
#define K_MOTOR (6 / 1.5) //он выдаёт примерно 6.5 рад/с на 1.5 Волта
#define T_MOTOR 0.21 //210 мс - 70% времени от разгона от 0 до некой постоянной скорости при напряжении
#define T_u (32 * Ts_s)

//======BATTERY AND FUNC SELECTOR PINS====
#define BATTERY_VOLTS A7
#define FUNCTION_PIN A6

#define K_FILTER (0.5)


//======MAZE PARAMETERS====
#define FORW_SPEED 0.2 // скорость робота вперёд по-умолчанию [м/с]
#define CELL_LENGTH 0.18 // длинна клетки [м]
#define CYC_BUF_SIZE 64 // длинна буфера циклограмм
#define MAZE_SIZE 11
#define FINISH_CELL {(MAZE_SIZE) / 2, (MAZE_SIZE) / 2} //финишная клетка // не надо делать +1 в рассчётах т.к. корды начинаются с нуля