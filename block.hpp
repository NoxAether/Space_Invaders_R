#ifndef BLOCK_H_
#define BLOCK_H_
#include <raylib.h>

class Block {
private:
  Vector2 _position;

public:
  Block(Vector2 position);
  void Draw();
  Rectangle GetRect();
};

#endif // BLOCK_H_
