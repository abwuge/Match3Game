#include "utils/ColorManager.h"

sf::Color ColorManager::getColor(int colorIndex) {
    switch(colorIndex) {
        case 0: return sf::Color(255, 150, 150);
        case 1: return sf::Color(150, 255, 150);
        case 2: return sf::Color(150, 200, 255);
        case 3: return sf::Color(255, 255, 150);
        case 4: return sf::Color(255, 200, 150);
        case 5: return sf::Color(220, 180, 255);
        default: return sf::Color::White;
    }
}
