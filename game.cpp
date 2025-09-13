#include "game.hpp"
#include "obstacle.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <raylib.h>
#include <stdexcept>

Game::Game() {
    music = LoadMusicStream("Sounds/music.ogg");
    _explosionSound = LoadSound("Sounds/explosion.ogg");
    PlayMusicStream(music);
    _InitGame();
}

Game::~Game() {
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(_explosionSound);
}

void Game::Update() {

    if (!run) {
        if (IsKeyDown(KEY_ENTER)) {
            _Reset();
            _InitGame();
        }
    } else {

        double currentTime = GetTime();
        if (currentTime - _mysteryship.GetTimeLastSpawn() >
            _mysteryship.GetMysteryShipSpawnInterval()) {
            _mysteryship.Spawn();
            _mysteryship.SetTimeLastSpawn(GetTime());
            _mysteryship.SetMysteryShipSpawnInterval(
                static_cast<float>(GetRandomValue(10, 20)));
        }

        for (auto &laser : _spaceship.GetLasers()) {
            laser.Update();
        }

        _MoveAliens();

        _AlienShootLaser();

        for (auto &laser : _alienLasers) {
            laser.Update();
        }

        _DeleteInactiveLasers();

        _mysteryship.Update();

        _CheckForCollisions();
    }
}

void Game::Draw() {
    _spaceship.Draw();

    for (auto &laser : _spaceship.GetLasers()) {
        laser.Draw();
    }

    for (auto &obstacle : _obstacles) {
        obstacle.Draw();
    }

    for (auto &alien : _aliens) {
        alien.Draw();
    }

    for (auto &laser : _alienLasers) {
        laser.Draw();
    }

    _mysteryship.Draw();
}

void Game::HandleInput() {
    if (!run) {

    } else {

        if (IsKeyDown(KEY_LEFT))
            _spaceship.MoveLeft();

        else if (IsKeyDown(KEY_RIGHT))
            _spaceship.MoveRight();

        else if (IsKeyDown(KEY_SPACE))
            _spaceship.FireLaser();
    }
}

void Game::_DeleteInactiveLasers() {
    for (auto it = _spaceship.GetLasers().begin();
         it != _spaceship.GetLasers().end();) {
        if (!it->GetActive())
            it = _spaceship.GetLasers().erase(it);
        else
            ++it;
    }

    for (auto it = _alienLasers.begin(); it != _alienLasers.end();) {
        if (!it->GetActive())
            it = _alienLasers.erase(it);
        else
            ++it;
    }
}

std::vector<Obstacle> Game::_CreateObstacles() {
    std::vector<Obstacle> obstacles;
    int obstacleWidth = Obstacle::_grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5.0f;

    for (int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(
            Obstacle{{offsetX, static_cast<float>(GetScreenHeight() - 200)}});
    }
    return obstacles;
}

std::vector<Alien> Game::_CreateAliens() {
    std::vector<Alien> aliens;
    int aliensInRow = 5;
    int alienColumns = 11;
    int cellSize = 55; // px

    int offsetX = 75;
    int offsetY = 110;

    for (int row = 0; row < aliensInRow; row++)
        for (int col = 0; col < alienColumns; col++) {

            int alienType;
            if (row == 0)
                alienType = 3;
            else if (row == 1 || row == 2)
                alienType = 2;
            else
                alienType = 1;

            float x_pos = offsetX + col * cellSize;
            float y_pos = offsetY + row * cellSize;
            aliens.push_back(Alien{alienType, {x_pos, y_pos}});
        }
    return aliens;
}

void Game::_MoveAliens() {
    float aliensDownBy = 2.0f;

    for (auto &alien : _aliens) {
        if (alien.GetPosition().x +
                alien.alienImages[alien.GetType() - 1].width >
            GetScreenWidth() - 25) {
            _aliensDirection = -0.5;
            _MoveDownAliens(aliensDownBy);
        } else if (alien.GetPosition().x < 25) {
            _aliensDirection = 0.5;
            _MoveDownAliens(aliensDownBy);
        }

        alien.Update(_aliensDirection);
    }
}

void Game::_MoveDownAliens(float distance) {
    for (auto &alien : _aliens) {
        alien.GetPosition().y += distance * 2;
    }
}

void Game::_AlienShootLaser() {
    double currentTime = GetTime();
    if (currentTime - _timeLastAlienFired > _alienLaserShootInterval &&
        !_aliens.empty()) {

        int randomIndex = GetRandomValue(0, _aliens.size() - 1);
        Alien &alien = _aliens[randomIndex];
        float alienPosX = alien.GetPosition().x +
                          alien.alienImages[alien.GetType() - 1].width / 2.0f;
        float alienPosY = alien.GetPosition().y +
                          alien.alienImages[alien.GetType() - 1].height / 2.0f;
        int laserSpeed = 3;
        _alienLasers.push_back(Laser{{alienPosX, alienPosY}, laserSpeed});
        _timeLastAlienFired = GetTime();
    }
}

void Game::_CheckForCollisions() {
    // Spaceship lasers
    for (auto &laser : _spaceship.GetLasers()) {
        if (!laser.GetActive())
            continue;

        auto alien_it = _aliens.begin();
        while (alien_it != _aliens.end()) {
            if (CheckCollisionRecs(alien_it->GetRect(), laser.GetRect())) {

                PlaySound(_explosionSound);

                if (alien_it->GetType() == 1) {
                    _score += 100;
                }

                else if (alien_it->GetType() == 2) {
                    _score += 200;
                }

                else if (alien_it->GetType() == 3) {
                    _score += 300;
                }

                _CheckHighscore();

                alien_it = _aliens.erase(alien_it);
                if (laser.GetActive())
                    laser.ToggleLaserActive();
            } else {
                ++alien_it;
            }
        }

        if (!laser.GetActive())
            continue;

        for (auto &obstacle : _obstacles) {
            auto block_it = obstacle._blocks.begin();
            while (block_it != obstacle._blocks.end()) {
                if (CheckCollisionRecs(block_it->GetRect(), laser.GetRect())) {
                    block_it = obstacle._blocks.erase(block_it);
                    if (laser.GetActive())
                        laser.ToggleLaserActive();
                } else {
                    ++block_it;
                }
            }
        }

        if (!laser.GetActive())
            continue;

        if (CheckCollisionRecs(_mysteryship.GetRect(), laser.GetRect())) {
            if (_mysteryship.GetAlive())
                _mysteryship.ToggleAlive();
            if (laser.GetActive())
                laser.ToggleLaserActive();
            _score += 500;
            _CheckHighscore();
            PlaySound(_explosionSound);
        }
    }

    // Alien lasers
    for (auto &laser : _alienLasers) {
        if (!laser.GetActive())
            continue;

        if (CheckCollisionRecs(laser.GetRect(), _spaceship.GetRect())) {
            if (laser.GetActive())
                laser.ToggleLaserActive();
            _lives--;
            if (!_lives)
                _GameOver();
        }
        if (!laser.GetActive())
            continue;

        for (auto &obstacle : _obstacles) {
            auto block_it = obstacle._blocks.begin();
            while (block_it != obstacle._blocks.end()) {
                if (CheckCollisionRecs(block_it->GetRect(), laser.GetRect())) {
                    block_it = obstacle._blocks.erase(block_it);
                    if (laser.GetActive())
                        laser.ToggleLaserActive();
                } else {
                    ++block_it;
                }
            }
        }
    }

    // Alien Collision with Obstacle
    for (auto &alien : _aliens) {
        for (auto &obstacle : _obstacles) {
            auto obstacle_it = obstacle._blocks.begin();
            while (obstacle_it != obstacle._blocks.end()) {
                if (CheckCollisionRecs(obstacle_it->GetRect(),
                                       alien.GetRect())) {
                    obstacle_it = obstacle._blocks.erase(obstacle_it);
                } else {
                    obstacle_it++;
                }
            }
        }

        if (CheckCollisionRecs(alien.GetRect(), _spaceship.GetRect())) {
            _GameOver();
        }
    }
}

void Game::_GameOver() { run = false; }

void Game::_InitGame() {
    _obstacles = _CreateObstacles();
    _aliens = _CreateAliens();
    _aliensDirection = 0.5;
    _timeLastAlienFired = 0;
    _lives = 3;
    _score = 0;
    _level = 1;

    // highscore handling
    try {
        _highscore = _LoadHighscoreFromFile();
        TraceLog(LOG_INFO, "Loaded highscore: %d", _highscore);
    } catch (const std::runtime_error &e) {
        TraceLog(LOG_ERROR, "Highscore loading: %s", e.what());
        _highscore = 0;
    } catch (const std::exception &e) {
        TraceLog(LOG_ERROR, "Unexpected error loading highscore: %s", e.what());
        _highscore = 0;
    }

    run = true;
}

void Game::_CheckHighscore() {
    if (_score > _highscore) {
        _highscore = _score;

        try {
            _SaveHighscoreToFile(_highscore);
        } catch (std::runtime_error &e) {
            TraceLog(LOG_ERROR, e.what());
        }
    }
}

int Game::_LoadHighscoreFromFile() {
    std::ifstream in("store.txt");

    if (!in.is_open()) {
        // Use simpler message to avoid potential issues
        throw std::runtime_error("Cannot open highscore file");
    }

    int highscore = 0;

    if (in >> highscore) {
        in.close();
        return highscore;
    } else {
        in.close();
        throw std::runtime_error("Invalid highscore data");
    }
}

void Game::_SaveHighscoreToFile(int highscore) {
    std::ofstream out("store.txt");

    if (!out.is_open()) {
        throw std::runtime_error("Cannot save highscore");
    }

    out << highscore;

    if (out.fail()) {
        out.close();
        throw std::runtime_error("Write failed");
    }

    out.close();
}

void Game::_Reset() {
    _spaceship.Reset();
    _aliens.clear();
    _alienLasers.clear();
    _obstacles.clear();
}
