#pragma once

#include <SFML/Graphics.hpp>

class RoundedRectangle : public sf::Drawable
{
public:
    RoundedRectangle(const sf::Vector2f &size = sf::Vector2f(0, 0), float cornerRadius = 0.f);

    void setSize(const sf::Vector2f &size);
    void setPosition(const sf::Vector2f &position);
    void setFillColor(const sf::Color &color);
    void setCornerRadius(float radius);

    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;
    sf::Color getFillColor() const;
    float getCornerRadius() const;

    sf::FloatRect getGlobalBounds() const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Color fillColor;
    float cornerRadius;

    sf::RectangleShape centerH;
    sf::RectangleShape centerV;
    sf::CircleShape corners[4];

    void updateShapes();
};
