#include "ui/SettingsButton.h"

SettingsButton::SettingsButton(const sf::Vector2f& position)
    : Button(position, sf::Vector2f(120.f, 120.f), sf::Color(180, 130, 70)) {
    setHoverColor(sf::Color(210, 160, 100));
    
    float iconSize = 12.f;
    sf::Vector2f center = position + sf::Vector2f(60.f, 60.f);
    
    icon1.setRadius(iconSize);
    icon1.setFillColor(sf::Color::White);
    icon1.setOrigin(sf::Vector2f(iconSize, iconSize));
    icon1.setPosition(center + sf::Vector2f(0.f, -25.f));
    
    icon2.setRadius(iconSize);
    icon2.setFillColor(sf::Color::White);
    icon2.setOrigin(sf::Vector2f(iconSize, iconSize));
    icon2.setPosition(center);
    
    icon3.setRadius(iconSize);
    icon3.setFillColor(sf::Color::White);
    icon3.setOrigin(sf::Vector2f(iconSize, iconSize));
    icon3.setPosition(center + sf::Vector2f(0.f, 25.f));
}

void SettingsButton::draw(sf::RenderWindow& window) {
    Button::draw(window);
    window.draw(icon1);
    window.draw(icon2);
    window.draw(icon3);
}
