#include "utils/RoundedRectangle.h"

RoundedRectangle::RoundedRectangle(const sf::Vector2f &size, float cornerRadius)
    : size(size), position(0.f, 0.f), fillColor(sf::Color::White), cornerRadius(cornerRadius)
{
    updateShapes();
}

void RoundedRectangle::setSize(const sf::Vector2f &newSize)
{
    size = newSize;
    updateShapes();
}

void RoundedRectangle::setPosition(const sf::Vector2f &newPosition)
{
    position = newPosition;
    updateShapes();
}

void RoundedRectangle::setFillColor(const sf::Color &color)
{
    fillColor = color;
    centerH.setFillColor(color);
    centerV.setFillColor(color);
    for (int i = 0; i < 4; i++)
    {
        corners[i].setFillColor(color);
    }
}

void RoundedRectangle::setCornerRadius(float radius)
{
    cornerRadius = radius;
    updateShapes();
}

sf::Vector2f RoundedRectangle::getSize() const
{
    return size;
}

sf::Vector2f RoundedRectangle::getPosition() const
{
    return position;
}

sf::Color RoundedRectangle::getFillColor() const
{
    return fillColor;
}

float RoundedRectangle::getCornerRadius() const
{
    return cornerRadius;
}

sf::FloatRect RoundedRectangle::getGlobalBounds() const
{
    return sf::FloatRect(position, size);
}

void RoundedRectangle::updateShapes()
{
    float effectiveRadius = std::min(cornerRadius, std::min(size.x, size.y) / 2.f);

    centerH.setSize(sf::Vector2f(size.x - effectiveRadius * 2, size.y));
    centerH.setPosition(sf::Vector2f(position.x + effectiveRadius, position.y));
    centerH.setFillColor(fillColor);

    centerV.setSize(sf::Vector2f(size.x, size.y - effectiveRadius * 2));
    centerV.setPosition(sf::Vector2f(position.x, position.y + effectiveRadius));
    centerV.setFillColor(fillColor);

    for (int i = 0; i < 4; i++)
    {
        corners[i].setRadius(effectiveRadius);
        corners[i].setFillColor(fillColor);
    }

    corners[0].setPosition(sf::Vector2f(position.x, position.y));
    corners[1].setPosition(sf::Vector2f(position.x + size.x - effectiveRadius * 2, position.y));
    corners[2].setPosition(sf::Vector2f(position.x, position.y + size.y - effectiveRadius * 2));
    corners[3].setPosition(sf::Vector2f(position.x + size.x - effectiveRadius * 2, position.y + size.y - effectiveRadius * 2));
}

void RoundedRectangle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(centerH, states);
    target.draw(centerV, states);
    for (int i = 0; i < 4; i++)
    {
        target.draw(corners[i], states);
    }
}
