#include "Encoder.h"
#include "velEstimator.h"
#include "Globals.h"
#include "tau.h"


void setup()
{
  initEncoders();
  initMotors();
  Serial.begin(115200);


  asmr.addCyc(SS90EL);
  asmr.addCyc(STOP);
}

void loop()
{
  ///////// TIMER /////////
  // Задание постоянной частоты главного цикла прогааммы
  static uint32_t timer = micros();
  while(micros() - timer < Ts_us)
    ;
  uint32_t dtime = micros() - timer;
  timer = micros();

  // static int checker = 0;
  // checker += 10;

  // static VelEstimator virtualEstimator;
  // virtualEstimator.tick(checker);
  // Serial.println(virtualEstimator.q_omega);
  
  ///////// SENSE /////////
  // Считывание датчиков
  BatteryTick();
  funcCelect.tick();

  const float omegaL = leftServo.realSpeed;
  const float omegaR = rightServo.realSpeed;
  state.update(omegaL, omegaR);


  ///////// PLAN /////////
  

  ///////// ACT /////////
  // Приведение управляющих воздействий в действие и логирование данных
  
  //leftServo.drive(6.28, battery.volts);
  //rightMotor.drive(Wr_in);
  asmr.exec();
}