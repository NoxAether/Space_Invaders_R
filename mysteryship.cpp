#include "mysteryship.hpp"
#include <raylib.h>

MysteryShip::MysteryShip() {
    _image = LoadTexture("Graphics/mystery.png");
    _alive = false;
    _timeLastSpawn = 0;
    _mysteryShipSpawnInterval = GetRandomValue(10, 20);
}

MysteryShip::~MysteryShip() { UnloadTexture(_image); }

void MysteryShip::Spawn() {
    _position.y = 90;
    int side = GetRandomValue(0, 1);

    if (!side) {
        _position.x = 25;
        _speed = 1.5;
    } else {
        _position.x = GetScreenWidth() - _image.width - 25;
        _speed = -1;
    }
    if (!_alive)
        ToggleAlive();
}

Rectangle MysteryShip::GetRect() {
    if (_alive) {
        return {_position.x, _position.y, float(_image.width),
                float(_image.height)};
    } else {
        return {_position.x, _position.y, 0, 0};
    }
}

void MysteryShip::Update() {
    if (!_alive)
        return;

    _position.x += _speed;
    if (_position.x > GetScreenWidth() - _image.width - 25 ||
        _position.x < 25) {
        if (_alive)
            ToggleAlive();
    }
}

void MysteryShip::Draw() {
    if (GetAlive()) {
        DrawTextureV(_image, _position, WHITE);
    }
}
