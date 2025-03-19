#pragma once
#include "config.h"
#include "tau.h"
#include "MazeCoord.h"
#include "Direction.h"

void polarSpeedToMotorSpeed(float Vin, float theta_i_in, float* omega_l, float* omega_r)
{
    // Расчет управляющих воздействий
    float W_f_in = Vin / WHEEL_RADIUS, 
        W_delta_in = theta_i_in  * ROBOT_WIDTH / WHEEL_RADIUS;
    //микшер
    *omega_l = W_f_in - W_delta_in / 2, 
    *omega_r = W_f_in + W_delta_in / 2;
}

class State
{
private:
    Integrator
    X,
    Y,
    Theta,
    Distance;

    float
    vL = 0,
    vR = 0,
    vX,
    vY,
    v;

    MazeCoord coord = {0, 0};
public:
    // const float &x, &y, &theta, &dist();
    // const MazeCoord &coord_out = coord;
    // : theta(Theta.out), x(X.out), y(Y.out), dist()(Distance.out) {}
    
    const float x() {return X.out;};
    const float y() {return Y.out;};
    const float theta() {return Theta.out;};
    const float dist() {return Distance.out;};
    const MazeCoord coord_out() {return coord;};

    void update(float omegaL, float omegaR)
    {
        vL = omegaL * WHEEL_RADIUS;
        vR = omegaR * WHEEL_RADIUS;

        float theta_i = (vR - vL) / ROBOT_WIDTH; //в этом вычислении опускается тангенс угла, тк tg(x) ~= x на малых углах
        Theta.tick(theta_i);

        v = (vR + vL) / 2;
        vX = v * cos(Theta.out);
        vY = v * sin(Theta.out);

        Distance.tick(v);
        X.tick(vX);
        Y.tick(vY);
    }
    void updateCoord(Direction::Dir dir)
    {
        switch(dir)
        {
            case Direction::Dir::UP:
            {
                coord.y--;
            }
            break;
            case Direction::Dir::DOWN:
            {
                coord.y++;
            }
            break;
            case Direction::Dir::LEFT:
            {
                coord.x--;
            }
            break;
            case Direction::Dir::RIGHT:
            {
                coord.x++;
            }
        }
    }
    void reset()
    {
        vL = 0;
        vR = 0;
        vX = 0;
        vY = 0;
        v = 0;
        X.reset();
        Y.reset();
        Theta.reset();
        Distance.reset();
    }
};