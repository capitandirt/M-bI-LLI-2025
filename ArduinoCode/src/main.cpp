#include "Encoder.h"
#include "velEstimator.h"
#include "Globals.h"
#include "tau.h"
#include "Maze.h"
#include "mazePrint.h" 


void setup()
{
  initEncoders();
  initMotors();
  Serial.begin(115200);

  //asmr.addCyc(SS90EL);
  asmr.addCyc(SD135SR);
  asmr.addCyc(STOP);

  // maze.setWall({0,0}, {PASS, WALL, WALL, PASS});
  // maze.setWall({1,0}, {WALL, PASS, WALL, PASS});
  // maze.setWall({2,0}, {PASS, PASS, WALL, WALL});
  // maze.setWall({0,1}, {PASS, WALL, PASS, WALL});
  // maze.setWall({1,1}, {WALL, WALL, WALL, PASS});
  // maze.setWall({2,1}, {PASS, PASS, PASS, WALL});
  // maze.setWall({0,2}, {WALL, WALL, PASS, PASS});
  // maze.setWall({1,2}, {WALL, PASS, WALL, WALL});
  // maze.setWall({2,2}, {WALL, WALL, PASS, WALL});
  Serial.println("maze created");

  
  solver.solve({1,2}, {3,3}, &maze); 
  Serial.println("maze solved");
  printMaze(&maze, &solver);
  
  //Serial.print("nextCell: " + solver.nextPathCell({1,2}).string());
  solver.writePath({1,2}, {2,0});
  solver.printPath();
  
  Serial.println("\nmaze printed\n");
  while(true);
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
  switch (funcCelect.function)
  {
  case 0: //рабочий режим
  {
    asmr.exec();
  }
  break;
  case 1: //Serial test
  {
    Serial.println("test Serial");
  }
  case 2:
  {
    Serial.println(battery.volts);
  }
  break;
  default:
  Serial.println("idk what to do");
  break;
  }
}