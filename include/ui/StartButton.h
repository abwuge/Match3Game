#pragma once
#include "Button.h"

class StartButton : public Button {
public:
    StartButton(const sf::Vector2f& position);
    
    void draw(sf::RenderWindow& window) override;

private:
    sf::CircleShape icon;
};
