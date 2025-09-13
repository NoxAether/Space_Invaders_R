#include "block.hpp"
#include "globals.h"
#include <raylib.h>

Block::Block(Vector2 position) : _position(position) {}

void Block::Draw() {
    DrawRectangle(_position.x, _position.y, 3, 3, ColorChange());
}

Rectangle Block::GetRect() {
    Rectangle rect;
    rect.x = _position.x;
    rect.y = _position.y;
    rect.width = 3;
    rect.height = 3;
    return rect;
}
