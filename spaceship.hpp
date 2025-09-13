#ifndef SPACESHIP_H_
#define SPACESHIP_H_
#include "laser.hpp"
#include <raylib.h>
#include <vector>

class Spaceship {
  private:
    Texture2D _image;
    Vector2 _position;
    std::vector<Laser> lasers;
    // Time since fired a laser is seconds for delay
    double _lastFireTime;
    Sound _laserSound;

  public:
    Spaceship();
    ~Spaceship();

    // Basic functionality of the spaceship
    void Draw();
    void MoveLeft();
    void MoveRight();
    void FireLaser();
    Rectangle GetRect();
    void Reset();

    // get;set;
    // read only access
    std::vector<Laser> &GetLasers() { return lasers; }
};

#endif // SPACESHIP_H_
