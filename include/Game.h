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

sf::Color getColor(int colorIndex);
void initializeGrid(std::vector<std::vector<Tile>>& grid, float windowSize);
void drawGrid(sf::RenderWindow& window, float windowSize, int gridSize);
void drawTile(sf::RenderWindow& window, const Tile& tile);
