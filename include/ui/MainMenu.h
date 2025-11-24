#pragma once

#include <SFML/Graphics.hpp>

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
    sf::RectangleShape startButton;
    sf::RectangleShape settingsButton;
    sf::CircleShape startIcon;
    sf::CircleShape settingsIcon1;
    sf::CircleShape settingsIcon2;
    sf::CircleShape settingsIcon3;
    
    bool isMouseOver(const sf::RectangleShape& button, const sf::Vector2f& mousePos) const;
    void setupButton(sf::RectangleShape& button, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
};
