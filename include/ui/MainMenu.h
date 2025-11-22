#pragma once

#include <SFML/Graphics.hpp>

enum class MenuState {
    MainMenu,
    Playing,
    Settings
};

class MainMenu {
public:
    MainMenu(float windowWidth, float windowHeight);
    
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    MenuState getState() const { return state; }
    void setState(MenuState newState) { state = newState; }

private:
    MenuState state;
    sf::RectangleShape startButton;
    sf::RectangleShape settingsButton;
    sf::CircleShape startIcon;
    sf::CircleShape settingsIcon1;
    sf::CircleShape settingsIcon2;
    sf::CircleShape settingsIcon3;
    
    bool isMouseOver(const sf::RectangleShape& button, const sf::Vector2f& mousePos) const;
    void setupButton(sf::RectangleShape& button, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
};
