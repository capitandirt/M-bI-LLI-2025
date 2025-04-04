#include "Encoder.h"
#include "velEstimator.h"
#include "Globals.h"
#include "tau.h"
#include "Maze.h"
#include "mazePrint.h" 

void work()
{
  static Direction::Dir correctDir = Direction::Dir::RIGHT; // изначально это стартовое направдение робота по лабиринту (направо / вниз)
        
  solver.solve(state.coord_out(), FINISH_CELL, &maze);
  Direction::Dir next = solver.nextPathCell();
  state.updateCoord(next);

  enum moveSet : uint8_t
  {
    FORWARD = 0,
    LEFT_TURN = 1,
    STOP_PROGRAMM = 2,
    RIGHT_TURN = 3
  };
  moveSet releativeDirection = (moveSet)((int(next) - int(correctDir) + 4) % 4); // остальное - СТОП  
  switch(releativeDirection)
  {
    case FORWARD:
    {
      asmr.addCyc(FWD);
    }break;
    case RIGHT_TURN:
    {
      asmr.addCyc(SS90ER);
    };
    case LEFT_TURN:
    {
      asmr.addCyc(SS90EL);
    };
    case STOP_PROGRAMM:
    {
      asmr.addCyc(STOP);
    };
  }
  correctDir = next;
}


void setup()
{
  initEncoders();
  initMotors();
  Serial.begin(115200);

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


  // asmr.addCyc(FWD);
  // asmr.addCyc(SS90ER);
  // asmr.addCyc(FWD);
  // asmr.addCyc(SS90EL);
  // asmr.addCyc(STOP);
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
  // PRINTLN(virtualEstimator.q_omega);
  
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
        work();
      }
      PRINT("IMALIVE");
      asmr.printCyc();
    }
    break;
    case 1: //Serial test
    {
      PRINTLN("test Serial");
    }
    case 2: // проверка заряда батареи
    {
      PRINTLN(battery.volts());
    }
    break;
    default:
    PRINTLN("idk what to do");
    delay(2000);
    break;
  }
}