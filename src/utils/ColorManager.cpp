#include "utils/ColorManager.h"

const std::vector<sf::Color> &ColorManager::getAllColors()
{
    static const std::vector<sf::Color> colors = {
        sf::Color(255, 150, 150),
        sf::Color(150, 255, 150),
        sf::Color(150, 200, 255),
        sf::Color(255, 255, 150),
        sf::Color(255, 200, 150),
        sf::Color(220, 180, 255),
        sf::Color(255, 180, 200),
        sf::Color(180, 255, 220),
        sf::Color(200, 180, 255),
        sf::Color(255, 220, 180)
    };
    return colors;
}

sf::Color ColorManager::getColor(int colorIndex)
{
    const auto &colors = getAllColors();
    if (colorIndex >= 0 && colorIndex < static_cast<int>(colors.size()))
    {
        return colors[colorIndex];
    }
    return sf::Color::White;
}
