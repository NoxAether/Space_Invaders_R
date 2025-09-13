#ifndef ALIEN_H_
#define ALIEN_H_
#include <raylib.h>

class Alien {
  private:
    int _type;
    Vector2 _position;
    static constexpr int alienImagesCount = 3;

  public:
    static Texture2D alienImages[3];

    // methods
  public:
    Alien(int type, Vector2 position);
    ~Alien();
    void Update(float direction);
    void Draw();
    static void UnloadImages();
    Rectangle GetRect();

    // get;set;
    int GetType() { return this->_type; }

    Vector2 &GetPosition() { return this->_position; }
};

#endif // ALIEN_H_
