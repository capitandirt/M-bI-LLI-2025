#include "Encoder.h"
#include "velEstimator.h"
#include "Globals.h"
#include "tau.h"


void setup()
{
  initEncoders();
  initMotors();
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
  battery.tick();
  funcCelect.tick();


  const float omegaL = leftServo.realSpeed;
  const float omegaR = rightServo.realSpeed;
  state.update(omegaL, omegaR);

  ///////// PLAN /////////
  const float Vin = 0.3, theta_i_in = 0;
  float Wl_in, Wr_in;
  polarSpeedToMotorSpeed(Vin, theta_i_in, &Wl_in, &Wr_in);
  

  ///////// ACT /////////
  // Приведение управляющих воздействий в действие и логирование данных
  
  leftServo.drive(0.3, battery.volts);
  //rightMotor.drive(Wr_in);
}