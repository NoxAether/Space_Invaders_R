#include "alien.hpp"
#include <raylib.h>

Texture2D Alien::alienImages[3] = {};

Alien::Alien(int type, Vector2 position) : _type(type), _position(position) {

    if (alienImages[_type - 1].id == 0) {

        switch (_type) {
        case 1: {
            alienImages[_type - 1] = LoadTexture("Graphics/alien_1.png");
            break;
        }
        case 2: {
            alienImages[_type - 1] = LoadTexture("Graphics/alien_2.png");
            break;
        }
        case 3: {
            alienImages[_type - 1] = LoadTexture("Graphics/alien_3.png");
            break;
        }
        default: {
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            break;
        }
        }
    }
}

Alien::~Alien() {}

void Alien::Update(float direction) { _position.x += direction; }

void Alien::Draw() { DrawTextureV(alienImages[_type - 1], _position, WHITE); }

Rectangle Alien::GetRect() {
    return {_position.x, _position.y, float(alienImages[_type - 1].width),
            float(alienImages[_type - 1].height)};
}

void Alien::UnloadImages() {
    for (int i = 0; i < Alien::alienImagesCount; i++) {
        UnloadTexture(alienImages[i]);
    }
}
