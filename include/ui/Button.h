#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
    virtual ~Button() = default;
    
    void setPosition(const sf::Vector2f& position);
    void setSize(const sf::Vector2f& size);
    void setColor(const sf::Color& color);
    void setHoverColor(const sf::Color& color);
    
    bool isMouseOver(const sf::Vector2f& mousePos) const;
    void updateHover(const sf::Vector2f& mousePos);
    
    sf::RectangleShape& getShape();
    const sf::RectangleShape& getShape() const;
    
    virtual void draw(sf::RenderWindow& window);

protected:
    sf::RectangleShape shape;
    sf::Color normalColor;
    sf::Color hoverColor;
};
