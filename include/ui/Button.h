#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "utils/RoundedRectangle.h"

class Button
{
public:
    Button(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &color, float cornerRadius = 5.f);
    virtual ~Button() = default;

    void setPosition(const sf::Vector2f &position);
    void setSize(const sf::Vector2f &size);
    void setColor(const sf::Color &color);
    void setHoverColor(const sf::Color &color);
    void setCornerRadius(float radius);

    bool isMouseOver(const sf::Vector2f &mousePos) const;
    void updateHover(const sf::Vector2f &mousePos);

    RoundedRectangle &getShape();
    const RoundedRectangle &getShape() const;

    virtual void draw(sf::RenderWindow &window);

protected:
    RoundedRectangle shape;
    sf::Color normalColor;
    sf::Color hoverColor;
};
