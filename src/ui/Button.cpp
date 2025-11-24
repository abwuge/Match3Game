#include "ui/Button.h"

Button::Button(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &color, float cornerRadius)
    : normalColor(color), hoverColor(color)
{
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(color);
    shape.setCornerRadius(cornerRadius);
}

void Button::setPosition(const sf::Vector2f &position)
{
    shape.setPosition(position);
}

void Button::setSize(const sf::Vector2f &size)
{
    shape.setSize(size);
}

void Button::setColor(const sf::Color &color)
{
    normalColor = color;
    shape.setFillColor(color);
}

void Button::setHoverColor(const sf::Color &color)
{
    hoverColor = color;
}

void Button::setCornerRadius(float radius)
{
    shape.setCornerRadius(radius);
}

bool Button::isMouseOver(const sf::Vector2f &mousePos) const
{
    return shape.getGlobalBounds().contains(mousePos);
}

void Button::updateHover(const sf::Vector2f &mousePos)
{
    if (isMouseOver(mousePos))
    {
        shape.setFillColor(hoverColor);
    }
    else
    {
        shape.setFillColor(normalColor);
    }
}

RoundedRectangle &Button::getShape()
{
    return shape;
}

const RoundedRectangle &Button::getShape() const
{
    return shape;
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}
