#ifndef LASER_H_
#define LASER_H_
#include <raylib.h>

class Laser {
  private:
    Vector2 _position;
    int _speed;
    bool _active;

  public:
    Laser(Vector2 position, int speed);
    ~Laser();

    //
    void Update();
    void Draw();
    Rectangle GetRect();

    // get;set;
    bool GetActive() { return this->_active; }
    void ToggleLaserActive() { this->_active = !_active; }
};

#endif // LASER_H_
