#pragma once
#include <SFML/Graphics.hpp>

const int sfRed = 0;
const int sfGreen = 1;
const int sfBlue = 2;
const int sfYellow = 3;
const int sfOrange = 4;
const int sfPurple = 5;

class ColorManager {
public:
    static sf::Color getColor(int colorIndex);
};
