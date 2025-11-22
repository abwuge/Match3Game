#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    auto desktop = sf::VideoMode::getDesktopMode();
    unsigned int windowSize = static_cast<unsigned int>(std::min(desktop.size.x, desktop.size.y) * 0.8f);
    
    auto window = sf::RenderWindow(sf::VideoMode({windowSize, windowSize}), "Match3 Game");
    window.setFramerateLimit(144);

    std::vector<std::vector<Tile>> grid(GRID_SIZE, std::vector<Tile>(GRID_SIZE));
    initializeGrid(grid, static_cast<float>(windowSize));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color(245, 245, 245));
        
        drawGrid(window, static_cast<float>(windowSize), GRID_SIZE);
        
        for(int i = 0; i < GRID_SIZE; i++) {
            for(int j = 0; j < GRID_SIZE; j++) {
                drawTile(window, grid[i][j]);
            }
        }
        
        window.display();
    }
}
