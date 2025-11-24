#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ColorManager
{
public:
    static sf::Color getColor(int colorIndex);
    static const std::vector<sf::Color> &getAllColors();
};
