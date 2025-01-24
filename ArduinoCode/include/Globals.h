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

EncoderParameters left_ep = 
{
    .CLOCK_A_PIN = LEFT_CLOCK_A_PIN,
    .B_PIN = LEFT_B_PIN,
    .DIR = LEFT_ENC_DIR,
    .ISRfunc = leftISR
};
EncoderParameters right_ep = 
{
    .CLOCK_A_PIN = RIGHT_CLOCK_A_PIN,
    .B_PIN = RIGHT_B_PIN,
    .DIR = RIGHT_ENC_DIR,
    .ISRfunc = rightISR
};


Encoder leftE(&left_ep);
Encoder rightE(&right_ep);

VelEstimator leftVelEst(&leftE); 
VelEstimator rightVelEst(&rightE);

State state;

Battery battery;

FunctionalCelector funcCelect;

Motor leftMotor, rightMotor;
PIreg leftPIreg(1 / (2 * K_MOTOR * T_u), T_MOTOR, 1), rightPIreg(1 / (2 * K_MOTOR * T_u), T_MOTOR, 1);

ServoMotor leftServo(&leftE, &leftVelEst, &leftMotor, &leftPIreg), rightServo(&rightE, &rightVelEst, &rightMotor, &rightPIreg);

void initEncoders()
{
    leftE.init();
    rightE.init();
}

void initMotors()
{
    leftServo.init(LEFT_MOTOR_POLARITY, LEFT_MOTOR_DIR, LEFT_MOTOR_PWM);
    rightServo.init(RIGHT_MOTOR_POLARITY, RIGHT_MOTOR_DIR, RIGHT_MOTOR_PWM);
}
