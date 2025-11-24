#pragma once
#include "Button.h"

class SettingsButton : public Button
{
public:
    SettingsButton(const sf::Vector2f &position);

    void draw(sf::RenderWindow &window) override;

private:
    sf::CircleShape icon1;
    sf::CircleShape icon2;
    sf::CircleShape icon3;
};
