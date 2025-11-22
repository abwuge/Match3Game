#include <SFML/Graphics.hpp>
#include "core/Game.h"
#include "ui/MainMenu.h"

int main()
{
    auto desktop = sf::VideoMode::getDesktopMode();
    unsigned int windowSize = static_cast<unsigned int>(std::min(desktop.size.x, desktop.size.y) * 0.8f);

    auto window = sf::RenderWindow(sf::VideoMode({windowSize, windowSize}), "Match 3 Game", sf::Style::Close);
    window.setFramerateLimit(144);

    MainMenu menu(static_cast<float>(windowSize), static_cast<float>(windowSize));
    
    std::vector<std::vector<Tile>> grid(GRID_SIZE, std::vector<Tile>(GRID_SIZE));
    bool gameInitialized = false;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            
            menu.handleEvent(event.value(), window);
        }

        window.clear(sf::Color(245, 245, 245));

        if (menu.getState() == MenuState::MainMenu) {
            menu.draw(window);
        } else if (menu.getState() == MenuState::Playing) {
            if (!gameInitialized) {
                initializeGrid(grid, static_cast<float>(windowSize));
                gameInitialized = true;
            }
            
            drawGrid(window, static_cast<float>(windowSize), GRID_SIZE);

            for (int i = 0; i < GRID_SIZE; i++)
            {
                for (int j = 0; j < GRID_SIZE; j++)
                {
                    drawTile(window, grid[i][j]);
                }
            }
        }

        window.display();
    }
}
