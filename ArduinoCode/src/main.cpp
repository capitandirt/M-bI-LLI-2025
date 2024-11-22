#include "Encoder.h"
#include "velEstimator.h"
#include "Globals.h"
#include "tau.h"


void setup()
{
  leftE.init();
  rightE.init();
  
  Serial.begin(115200);
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
  leftEst.tick();
  rightEst.tick();
  const float leftEncPhi = leftE.q_Phi;
  const float rightEncPhi = rightE.q_Phi;
  const float Wl = leftEst.q_w;
  const float Wr = rightEst.q_w;

  ///////// PLAN /////////
  // Расчет управляющих воздействий
  static Integrator theta;
  const float Vl = Wl * WHEEL_RADIUS, Vr = Wr * WHEEL_RADIUS;
  const float V = (Vl + Vr) / 2;
  const float theta_i = (Vr - Vl) / ROBOT_WIDTH;
  theta.tick(theta_i);
  const float Vx = V * cos(theta.q_out);
  const float Vy = V * sin(theta.q_out);
  static Integrator X, Y;
  X.tick(Vx);
  Y.tick(Vy);


  ///////// ACT /////////
  // Приведение управляющих воздействий в действие и логирование данных
  Serial.println(String(theta.q_out));// + " " + String(Y.q_out));  
}