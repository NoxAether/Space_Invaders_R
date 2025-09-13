#include "spaceship.hpp"
#include <raylib.h>

Spaceship::Spaceship() {
    _image = LoadTexture("Graphics/spaceship.png");
    _position.x = (GetScreenWidth() - _image.width) / 2.0;
    _position.y = GetScreenHeight() - _image.height - 100;
    _lastFireTime = 0.0;
    _laserSound = LoadSound("Sounds/laser.ogg");
}

Spaceship::~Spaceship() {
    UnloadTexture(_image);
    UnloadSound(_laserSound);
}

void Spaceship::Draw() { DrawTextureV(_image, _position, WHITE); }

void Spaceship::MoveLeft() {
    _position.x -= 1.2f;
    if (_position.x < 25)
        _position.x = 25;
}

void Spaceship::MoveRight() {
    _position.x += 1.2f;
    if (_position.x > GetScreenWidth() - _image.width - 25)
        _position.x = GetScreenWidth() - _image.width - 25;
}

void Spaceship::FireLaser() {
    if (GetTime() - _lastFireTime >= 0.35) {
        // laser constructor from the play origin
        lasers.push_back(Laser{
            {(_position.x + _image.width / 2.0f) - 2.0f, _position.y}, -6});
        _lastFireTime = GetTime();
        PlaySound(_laserSound);
    }
}

Rectangle Spaceship::GetRect() {
    return {_position.x, _position.y, float(_image.width),
            float(_image.height)};
}

void Spaceship::Reset() {
    _position.x = (GetScreenWidth() - _image.width) / 2.0f;
    _position.y = GetScreenHeight() - _image.height - 100;
    ;

    lasers.clear();
}
