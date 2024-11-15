#include <Arduino.h>
#include "encISR.h"
#include "Encoder.h"
#include "velEstimator.h"


void setup()
{
  Serial.begin(115200);
  leftE.init(leftISR);
  rightE.init(rightISR);
  // leftEncInit();
  // rightEncInit();
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
  leftE.tick();
  rightE.tick();
  // leftEncTick();
  // rightEncTick();
  const float leftEncPhi = leftE.cPhi;//GleftPhi;
  const float rightEncPhi = rightE.cPhi;//GrightPhi;

  ///////// PLAN /////////
  // Расчет управляющих воздействий

  ///////// ACT /////////
  // Приведение управляющих воздействий в действие и логирование данных
  Serial.println(String(leftEncPhi) + " " + String(rightEncPhi));  
}