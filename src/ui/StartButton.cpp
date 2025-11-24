#include "ui/StartButton.h"

StartButton::StartButton(const sf::Vector2f &position)
    : Button(position, sf::Vector2f(120.f, 120.f), sf::Color(70, 180, 70))
{
    setHoverColor(sf::Color(100, 220, 100));

    icon.setRadius(25.f);
    icon.setPointCount(3);
    icon.setFillColor(sf::Color::White);
    icon.setOrigin(sf::Vector2f(25.f, 25.f));
    icon.setPosition(position + sf::Vector2f(60.f, 60.f));
    icon.setRotation(sf::degrees(90.f));
}

void StartButton::draw(sf::RenderWindow &window)
{
    Button::draw(window);
    window.draw(icon);
}
