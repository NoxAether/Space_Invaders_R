#include "laser.hpp"
#include <raylib.h>

Laser::Laser(Vector2 position, int speed)
    : _position(position), _speed(speed), _active(true) {}

Laser::~Laser() {}

void Laser::Draw() {
    if (GetActive())
        DrawRectangle(_position.x, _position.y, 4, 15, {243, 216, 63, 255});
}

Rectangle Laser::GetRect() {
    Rectangle rect;
    rect.x = _position.x;
    rect.y = _position.y;
    rect.width = 4;
    rect.height = 15;

    return rect;
}

void Laser::Update() {
    _position.y += _speed;

    if (GetActive())

        if (_position.y > GetScreenHeight() - 100 || _position.y < 25) {
            ToggleLaserActive();
        }
}
