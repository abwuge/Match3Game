#include "ui/MainMenu.h"

MainMenu::MainMenu(float windowWidth, float windowHeight)
    : startButton(sf::Vector2f(windowWidth / 2.f - 150.f, windowHeight / 2.f - 60.f)),
      settingsButton(sf::Vector2f(windowWidth / 2.f + 30.f, windowHeight / 2.f - 60.f)) {
}

ButtonAction MainMenu::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.is<sf::Event::MouseMoved>()) {
        sf::Vector2f mousePos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        startButton.updateHover(mousePos);
        settingsButton.updateHover(mousePos);
    }
    
    if (event.is<sf::Event::MouseButtonPressed>()) {
        if (event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            
            if (startButton.isMouseOver(mousePos)) {
                return ButtonAction::StartGame;
            } else if (settingsButton.isMouseOver(mousePos)) {
                return ButtonAction::OpenSettings;
            }
        }
    }
    
    return ButtonAction::None;
}

void MainMenu::draw(sf::RenderWindow& window) {
    startButton.draw(window);
    settingsButton.draw(window);
}
