#include "ui/MainMenu.h"

MainMenu::MainMenu(float windowWidth, float windowHeight) : state(MenuState::MainMenu) {
    float buttonWidth = 120.f;
    float buttonHeight = 120.f;
    float centerX = windowWidth / 2.f;
    float startY = windowHeight / 2.f;
    
    setupButton(startButton, sf::Vector2f(centerX - buttonWidth - 30.f, startY - buttonHeight / 2.f), 
                sf::Vector2f(buttonWidth, buttonHeight), sf::Color(70, 180, 70));
    setupButton(settingsButton, sf::Vector2f(centerX + 30.f, startY - buttonHeight / 2.f), 
                sf::Vector2f(buttonWidth, buttonHeight), sf::Color(180, 130, 70));
    
    startIcon.setRadius(25.f);
    startIcon.setPointCount(3);
    startIcon.setFillColor(sf::Color::White);
    startIcon.setOrigin(sf::Vector2f(25.f, 25.f));
    startIcon.setPosition(sf::Vector2f(centerX - buttonWidth / 2.f - 30.f, startY));
    startIcon.setRotation(sf::degrees(90.f));
    
    float iconSize = 12.f;
    settingsIcon1.setRadius(iconSize);
    settingsIcon1.setFillColor(sf::Color::White);
    settingsIcon1.setOrigin(sf::Vector2f(iconSize, iconSize));
    settingsIcon1.setPosition(sf::Vector2f(centerX + buttonWidth / 2.f + 30.f, startY - 25.f));
    
    settingsIcon2.setRadius(iconSize);
    settingsIcon2.setFillColor(sf::Color::White);
    settingsIcon2.setOrigin(sf::Vector2f(iconSize, iconSize));
    settingsIcon2.setPosition(sf::Vector2f(centerX + buttonWidth / 2.f + 30.f, startY));
    
    settingsIcon3.setRadius(iconSize);
    settingsIcon3.setFillColor(sf::Color::White);
    settingsIcon3.setOrigin(sf::Vector2f(iconSize, iconSize));
    settingsIcon3.setPosition(sf::Vector2f(centerX + buttonWidth / 2.f + 30.f, startY + 25.f));
}

void MainMenu::setupButton(sf::RectangleShape& button, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color) {
    button.setSize(size);
    button.setPosition(position);
    button.setFillColor(color);
}

bool MainMenu::isMouseOver(const sf::RectangleShape& button, const sf::Vector2f& mousePos) const {
    return button.getGlobalBounds().contains(mousePos);
}

void MainMenu::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (state != MenuState::MainMenu) return;
    
    if (event.is<sf::Event::MouseMoved>()) {
        sf::Vector2f mousePos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        
        if (isMouseOver(startButton, mousePos)) {
            startButton.setFillColor(sf::Color(100, 220, 100));
        } else {
            startButton.setFillColor(sf::Color(70, 180, 70));
        }
        
        if (isMouseOver(settingsButton, mousePos)) {
            settingsButton.setFillColor(sf::Color(210, 160, 100));
        } else {
            settingsButton.setFillColor(sf::Color(180, 130, 70));
        }
    }
    
    if (event.is<sf::Event::MouseButtonPressed>()) {
        if (event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            
            if (isMouseOver(startButton, mousePos)) {
                state = MenuState::Playing;
            } else if (isMouseOver(settingsButton, mousePos)) {
                // Settings functionality to be implemented
            }
        }
    }
}

void MainMenu::draw(sf::RenderWindow& window) {
    if (state != MenuState::MainMenu) return;
    
    window.draw(startButton);
    window.draw(settingsButton);
    window.draw(startIcon);
    window.draw(settingsIcon1);
    window.draw(settingsIcon2);
    window.draw(settingsIcon3);
}
