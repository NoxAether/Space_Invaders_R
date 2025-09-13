#ifndef GAME_H_
#define GAME_H_

#include "alien.hpp"
#include "mysteryship.hpp"
#include "obstacle.hpp"
#include "spaceship.hpp"

class Game {
private:
  Spaceship _spaceship;
  std::vector<Obstacle> _obstacles;
  std::vector<Alien> _aliens;
  float _aliensDirection;
  std::vector<Laser> _alienLasers;
  constexpr static float _alienLaserShootInterval = 0.70;
  float _timeLastAlienFired;
  MysteryShip _mysteryship;
  int _lives;
  int _score;
  int _level;
  int _highscore;
  Sound _explosionSound;

  // methods
private:
  void _DeleteInactiveLasers();
  std::vector<Obstacle> _CreateObstacles();
  std::vector<Alien> _CreateAliens();
  void _MoveAliens();
  void _MoveDownAliens(float distance);
  void _AlienShootLaser();
  void _CheckForCollisions();
  void _GameOver();
  void _Reset();
  void _InitGame();
  void _CheckHighscore();
  void _SaveHighscoreToFile(int highscore);
  int _LoadHighscoreFromFile();

public:
  bool run;
  Music music;

  // methods
public:
  Game();
  ~Game();
  void Draw();
  void Update();
  void HandleInput();

  // get;set;
  int GetLives() { return this->_lives; }
  int GetScore() { return this->_score; }
  void SetScore(int score) { this->_score = score; }
  int GetLevel() { return this->_level; }
  void SetLevel(int level) { this->_level = level; }
  int GetHighscore() { return this->_highscore; }
};

#endif // GAME_H_
