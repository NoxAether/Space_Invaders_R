#ifndef OBSTACLE_H_
#define OBSTACLE_H_
#include "block.hpp"
#include <vector>

class Obstacle {
  public:
    Vector2 _position;
    std::vector<Block> _blocks;
    static std::vector<std::vector<int>> _grid;

  public:
    Obstacle(Vector2 position);
    void Draw();
};

#endif // OBSTACLE_H_
