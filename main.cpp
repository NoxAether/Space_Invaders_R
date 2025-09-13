#include "game.hpp"
#include "globals.h"
#include <cmath>
#include <raylib.h>
#include <string>

std::string FormatWithLeadingZeros(int number, int width) {
    if (width > 6) {
        width = 6; // Increased to 6 to allow for larger numbers
    } else if (width <= 0) {
        width = 1;
    }

    std::string numberStr = std::to_string(number);
    int leadingZeros = width - numberStr.length();

    // Prevent negative leading zeros
    if (leadingZeros <= 0) {
        return numberStr;
    }

    return std::string(leadingZeros, '0') + numberStr;
}

auto main(int argc, char *argv[]) -> int {
    // background
    Color grey{29, 29, 27, 255};

    int offset = 50; // px

    // setting up `settings`
    constexpr int windowWidth = 750;
    constexpr int windowHeight = 700;
    const char *title = "Space Invaders";
    constexpr int targetFPS = 120;

    InitWindow(windowWidth + offset, windowHeight + 2 * offset, title);
    float GlobalStartTime = GetTime();

    InitAudioDevice();

    Font font = LoadFontEx("Font/monogram.ttf", 64, NULL, 0);
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");
    SetTargetFPS(targetFPS);

    Game game;
    float x;

    while (!WindowShouldClose()) {
        Color color = ColorChange();

        UpdateMusicStream(game.music);

        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, color);
        DrawLineEx({25, 730}, {775, 730}, 3, color);

        // Draw level text
        if (!game.run) {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, color);
        } else {
            std::string levelString =
                "LEVEL " + FormatWithLeadingZeros(game.GetLevel(), 2);
            DrawTextEx(font, levelString.c_str(), {570, 740}, 34, 2, color);
        }

        // Draw lives (spaceships)
        x = 50.0;
        for (int i = 0; i < game.GetLives(); i++) {
            DrawTextureV(spaceshipImage, {x, 745}, WHITE);
            x += 50.0f;
        }

        // Draw SCORE - FIXED POSITION
        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, color);
        std::string scoreText = FormatWithLeadingZeros(game.GetScore(), 6);
        DrawTextEx(font, scoreText.c_str(), {50, 50}, 34, 2,
                   color); // Changed Y to 50

        // Draw HIGH-SCORE - FIXED POSITION
        DrawTextEx(font, "HIGH-SCORE", {500, 15}, 34, 2,
                   color); // Adjusted X position
        std::string highscoreText =
            FormatWithLeadingZeros(game.GetHighscore(), 6);
        DrawTextEx(font, highscoreText.c_str(), {570, 50}, 34, 2,
                   color); // Corrected position

        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
    return 0;
}
