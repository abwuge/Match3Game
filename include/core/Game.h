#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

const int GRID_SIZE = 8;
const int NUM_COLORS = 6;

struct Tile {
    int color;
    sf::RectangleShape centerH;
    sf::RectangleShape centerV;
    sf::CircleShape corners[4];
    sf::Color fillColor;
};

class Game {
public:
    Game(float windowSize);
    
    void initialize();
    void render(sf::RenderWindow& window);
    
private:
    float windowSize;
    std::vector<std::vector<Tile>> grid;
    
    void initializeGrid();
    void drawGrid(sf::RenderWindow& window);
    void drawTile(sf::RenderWindow& window, const Tile& tile);
};
