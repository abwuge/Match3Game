#include "core/Game.h"
#include "utils/ColorManager.h"
#include <random>

void initializeGrid(std::vector<std::vector<Tile>>& grid, float windowSize) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, NUM_COLORS - 1);
    
    float tileSize = windowSize / GRID_SIZE;
    float padding = tileSize * 0.12f;
    float cornerRadius = tileSize * 0.2f;
    float shapeSize = tileSize - padding * 2;
    
    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            float x = j * tileSize + padding;
            float y = i * tileSize + padding;
            
            grid[i][j].color = dis(gen);
            grid[i][j].fillColor = ColorManager::getColor(grid[i][j].color);
            
            grid[i][j].centerH.setSize(sf::Vector2f(shapeSize - cornerRadius * 2, shapeSize));
            grid[i][j].centerH.setPosition(sf::Vector2f(x + cornerRadius, y));
            grid[i][j].centerH.setFillColor(grid[i][j].fillColor);
            
            grid[i][j].centerV.setSize(sf::Vector2f(shapeSize, shapeSize - cornerRadius * 2));
            grid[i][j].centerV.setPosition(sf::Vector2f(x, y + cornerRadius));
            grid[i][j].centerV.setFillColor(grid[i][j].fillColor);
            
            for(int k = 0; k < 4; k++) {
                grid[i][j].corners[k].setRadius(cornerRadius);
                grid[i][j].corners[k].setFillColor(grid[i][j].fillColor);
            }
            
            grid[i][j].corners[0].setPosition(sf::Vector2f(x, y));
            grid[i][j].corners[1].setPosition(sf::Vector2f(x + shapeSize - cornerRadius * 2, y));
            grid[i][j].corners[2].setPosition(sf::Vector2f(x, y + shapeSize - cornerRadius * 2));
            grid[i][j].corners[3].setPosition(sf::Vector2f(x + shapeSize - cornerRadius * 2, y + shapeSize - cornerRadius * 2));
        }
    }
}

void drawGrid(sf::RenderWindow& window, float windowSize, int gridSize) {
    float tileSize = windowSize / gridSize;
    
    sf::RectangleShape line;
    line.setFillColor(sf::Color(180, 180, 180, 200));
    
    for(int i = 0; i <= gridSize; i++) {
        line.setSize(sf::Vector2f(windowSize, 2.f));
        line.setPosition(sf::Vector2f(0.f, i * tileSize));
        window.draw(line);
        
        line.setSize(sf::Vector2f(2.f, windowSize));
        line.setPosition(sf::Vector2f(i * tileSize, 0.f));
        window.draw(line);
    }
}

void drawTile(sf::RenderWindow& window, const Tile& tile) {
    window.draw(tile.centerH);
    window.draw(tile.centerV);
    for(int i = 0; i < 4; i++) {
        window.draw(tile.corners[i]);
    }
}
