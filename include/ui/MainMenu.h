#pragma once

#include <SFML/Graphics.hpp>
#include "core/Scene.h"
#include "StartButton.h"
#include "SettingsButton.h"

class MainMenu : public Scene
{
public:
    MainMenu(float windowWidth, float windowHeight);

    void handleEvent(const sf::Event &event) override;
    void render(sf::RenderWindow &window) override;

private:
    StartButton startButton;
    SettingsButton settingsButton;
    float windowWidth;
    float windowHeight;
};
