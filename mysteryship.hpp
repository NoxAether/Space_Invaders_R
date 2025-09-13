#ifndef MYSTERYSHIP_H_
#define MYSTERYSHIP_H_
#include <raylib.h>

class MysteryShip {
  private:
    Vector2 _position;
    Texture2D _image;
    float _speed;
    bool _alive;
    float _mysteryShipSpawnInterval;
    float _timeLastSpawn;

  public:
    MysteryShip();
    ~MysteryShip();
    void Update();
    void Draw();
    void Spawn();
    Rectangle GetRect();

    // get;set;
    const bool GetAlive() const { return this->_alive; }
    void ToggleAlive() { this->_alive = !this->_alive; }

    void SetTimeLastSpawn(float timeLastSpawn) {
        this->_timeLastSpawn = timeLastSpawn;
    }
    float GetTimeLastSpawn() { return this->_timeLastSpawn; }

    void SetMysteryShipSpawnInterval(float time) {
        this->_mysteryShipSpawnInterval = time;
    }
    float GetMysteryShipSpawnInterval() {
        return this->_mysteryShipSpawnInterval;
    }
};

#endif // MYSTERYSHIP_H_
