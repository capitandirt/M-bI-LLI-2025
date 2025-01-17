#include "Encoder.h"
#include "velEstimator.h"
#include "Globals.h"
#include "tau.h"


void setup()
{
  leftE.init();
  rightE.init();
  leftMotor.init(LEFT_MOTOR_POLARITY, LEFT_MOTOR_DIR, LEFT_MOTOR_PWM);
  rightMotor.init(RIGHT_MOTOR_POLARITY, RIGHT_MOTOR_DIR, RIGHT_MOTOR_PWM);
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

  leftMotor.tick(battery.volts);
  rightMotor.tick(battery.volts);

  const float omegaL = leftMotor.realSpeed;
  const float omegaR = rightMotor.realSpeed;
  state.update(omegaL, omegaR);

  ///////// PLAN /////////
  // Расчет управляющих воздействий
  const float Vin = 0.3, theta_i_in = 0;
  float W_f_in = Vin / WHEEL_RADIUS, 
        W_delta_in = theta_i_in  * ROBOT_WIDTH / WHEEL_RADIUS;
  //микшер
  float Wl_in = W_f_in - W_delta_in / 2, 
        Wr_in = W_f_in + W_delta_in / 2;
  

  ///////// ACT /////////
  // Приведение управляющих воздействий в действие и логирование данных
  
  leftMotor.drive(1);
  //rightMotor.drive(Wr_in);
}