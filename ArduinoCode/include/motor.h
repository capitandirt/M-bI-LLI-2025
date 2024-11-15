#pragma once
#include <Arduino.h>

#define LEFT_CLOCK_A_PIN 2
#define LEFT_B_PIN 4
#define RIGHT_CLOCK_A_PIN 3
#define RIGHT_B_PIN 5

#define LEFT_ENC_DIR 1
#define RIGHT_ENC_DIR 1

#define ENC_PPR 48
#define GEAR_RATIO 30
#define TICK_TO_RAD (2.0 * M_PI / (ENC_PPR * GEAR_RATIO))

volatile int16_t GleftCounter = 0;
float GleftPhi = 0;
volatile int16_t GrightCounter = 0;
float GrightPhi = 0;
int8_t leftEtt[4][4] = {0}; //сначала старое, потом новое
int8_t rightEtt[4][4] = {0}; //сначала старое, потом новое

void motorSetup()
{

}
void leftISR()
{
    static uint8_t leftEncOld = 0;
    const uint8_t leftB = digitalRead(LEFT_B_PIN);
    const uint8_t leftClockA = digitalRead(LEFT_CLOCK_A_PIN);
    const uint8_t leftA = leftClockA ^ leftB;

    const uint8_t leftEncNow = (leftA << 1) | leftB; // xxxxxxAB = (xxxxxxxA << 1) | xxxxxxxB
    GleftCounter += leftEtt[leftEncOld][leftEncNow];
    leftEncOld = leftEncNow;
}
void rightISR()
{
    static uint8_t rightEncOld = 0;
    const uint8_t rightB = digitalRead(RIGHT_B_PIN);
    const uint8_t rightClockA = digitalRead(RIGHT_CLOCK_A_PIN);
    const uint8_t rightA = rightClockA ^ rightB;

    const uint8_t RightEncNow = (rightA << 1) | rightB; // xxxxxxAB = (xxxxxxxA << 1) | xxxxxxxB
    GrightCounter += rightEtt[rightEncOld][RightEncNow];
    rightEncOld = RightEncNow;
}

void leftEncInit()
{
    // Настройка пинмодов для прерывающихс пинов левого
    pinMode(LEFT_CLOCK_A_PIN, INPUT);
    pinMode(LEFT_B_PIN, INPUT);
    noInterrupts();
    attachInterrupt(
        digitalPinToInterrupt(LEFT_CLOCK_A_PIN), 
        leftISR, 
        CHANGE
        );
    leftEtt[0b00][0b01] = -LEFT_ENC_DIR;
    leftEtt[0b01][0b11] = -LEFT_ENC_DIR;
    leftEtt[0b11][0b10] = -LEFT_ENC_DIR;
    leftEtt[0b10][0b00] = -LEFT_ENC_DIR;

    leftEtt[0b00][0b10] = LEFT_ENC_DIR;
    leftEtt[0b10][0b11] = LEFT_ENC_DIR;
    leftEtt[0b11][0b01] = LEFT_ENC_DIR;
    leftEtt[0b01][0b00] = LEFT_ENC_DIR;

    interrupts();
}

void rightEncInit()
{
    // Настройка пинмодов для прерывающихс пинов левого
    pinMode(RIGHT_CLOCK_A_PIN, INPUT);
    pinMode(RIGHT_B_PIN, INPUT);
    noInterrupts();
    attachInterrupt(
        digitalPinToInterrupt(RIGHT_CLOCK_A_PIN), 
        rightISR, 
        CHANGE
        );
    rightEtt[0b00][0b01] = RIGHT_ENC_DIR;
    rightEtt[0b01][0b11] = RIGHT_ENC_DIR;
    rightEtt[0b11][0b10] = RIGHT_ENC_DIR;
    rightEtt[0b00][0b01] = RIGHT_ENC_DIR;

    rightEtt[0b00][0b10] = -RIGHT_ENC_DIR;
    rightEtt[0b01][0b00] = -RIGHT_ENC_DIR;
    rightEtt[0b11][0b01] = -RIGHT_ENC_DIR;
    rightEtt[0b01][0b11] = -RIGHT_ENC_DIR;

    interrupts();
}

void leftEncTick()
{
    noInterrupts();
    const int deltaLeftEnc = GleftCounter;
    GleftCounter = 0;
    interrupts();
    GleftPhi += deltaLeftEnc * TICK_TO_RAD;
}

void rightEncTick()
{
    noInterrupts();
    const int deltaRightEnc = GrightCounter;
    GrightCounter = 0;
    interrupts();
    GrightPhi += deltaRightEnc * TICK_TO_RAD;
}