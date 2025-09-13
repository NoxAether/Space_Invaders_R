#include "globals.h"
#include <algorithm>
#include <cmath>

float GlobalStartTime; // Definition of the global variable

Color ColorChange() {
    const float speed = 0.5f;
    float t = GetTime() - GlobalStartTime;

    int red = 255;
    int green = static_cast<int>(220 + 35 * sin(t * speed * 1.5f));
    int blue = static_cast<int>(50 + 30 * sin(t * speed * 0.7f));

    red = std::clamp(red, 0, 255);
    green = std::clamp(green, 0, 255);
    blue = std::clamp(blue, 0, 255);

    return Color{static_cast<unsigned char>(red),
                 static_cast<unsigned char>(green),
                 static_cast<unsigned char>(blue), 255};
}
