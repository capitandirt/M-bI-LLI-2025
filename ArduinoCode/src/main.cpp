#include <Arduino.h>
#include "motor.h"

#define Ts_us 5000 // Период квантования в [мкс]
#define Ts_s (Ts_us / 1000000.0) // Период квантования в [с]

void setup()
{
  Serial.begin(115200);
  leftEncInit();
  rightEncInit();
}

void loop()
{
  ///////// TIMER /////////
  // Задание постоянной частоты главного цикла прогааммы
  static uint32_t timer = micros();
  while(micros() - timer < Ts_us)
    ;
  timer = micros();
  
  ///////// SENSE /////////
  // Считывание датчиков
  leftEncTick();
  rightEncTick();
  const float leftEncPhi = GleftPhi;
  const float rightEncPhi = GrightPhi;

  ///////// PLAN /////////
  // Расчет управляющих воздействий

  ///////// ACT /////////
  // Приведение управляющих воздействий в действие и логирование данных
  Serial.println(String(leftEncPhi) + " " + String(rightEncPhi));  
}