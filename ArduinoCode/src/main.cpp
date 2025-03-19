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

  maze.setWall({0,0}, {PASS, WALL, WALL, PASS});
  maze.setWall({1,0}, {WALL, PASS, WALL, PASS});
  maze.setWall({2,0}, {PASS, PASS, WALL, WALL});
  maze.setWall({0,1}, {PASS, WALL, PASS, WALL});
  maze.setWall({1,1}, {WALL, WALL, WALL, PASS});
  maze.setWall({2,1}, {PASS, PASS, PASS, WALL});
  maze.setWall({0,2}, {WALL, WALL, PASS, PASS});
  maze.setWall({1,2}, {WALL, PASS, WALL, WALL});
  maze.setWall({2,2}, {WALL, WALL, PASS, PASS});

  
  solver.solve({1,2}, {7,9}, &maze);
  
  solver.writePath({1,2}, {7,9});
  solver.printPath();
  printMaze(&maze, &solver);
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

  const float omegaL = leftServo.realSpeed();
  const float omegaR = rightServo.realSpeed();
  state.update(omegaL, omegaR);


  ///////// PLAN /////////
  

  ///////// ACT /////////
  // Приведение управляющих воздействий в действие и логирование данных
  
  //leftServo.drive(6.28, battery.volts());
  //rightMotor.drive(Wr_in);
  switch (funcCelect.function)
  {
    case 0: //рабочий режим
    {
      if(asmr.exec())
      {
        double correctRadAngle = (fmod(state.theta(), 2*PI));
        Direction::Dir correctDir;
        
        solver.solve(state.coord_out(), FINISH_CELL, &maze);
        Direction::Dir next = solver.nextPathCell();
        state.updateCoord(next);
        Direction::Dir releativeDirection = Direction::Dir(int(next) - int(correctDir));
        switch(releativeDirection)
        {
          case Direction::Dir::UP:
          {
            asmr.addCyc(FWD);
          }break;
          case Direction::Dir::RIGHT:
          {
            asmr.addCyc(SS90ER);
          };
          case Direction::Dir::DOWN:
          {
            asmr.addCyc(SS180S);
            asmr.addCyc(FWD);
          };
          case Direction::Dir::LEFT:
          {
            asmr.addCyc(SS90EL);
          };
        }
      }
    }
    break;
    case 1: //Serial test
    {
      Serial.println("test Serial");
    }
    case 2: // проверка заряда батареи
    {
      Serial.println(battery.volts());
    }
    break;
    default:
    Serial.println("idk what to do");
    delay(2000);
    break;
  }
}