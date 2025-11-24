#pragma once

#include <SFML/Graphics.hpp>
#include "StartButton.h"
#include "SettingsButton.h"

enum class ButtonAction {
    None,
    StartGame,
    OpenSettings
};

class MainMenu {
public:
    MainMenu(float windowWidth, float windowHeight);
    
    ButtonAction handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    StartButton startButton;
    SettingsButton settingsButton;
};
