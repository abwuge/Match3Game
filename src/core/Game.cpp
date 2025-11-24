#include "core/Game.h"
#include "core/SceneManager.h"
#include "utils/ColorManager.h"
#include <random>

Game::Game(float windowSize)
    : windowSize(windowSize), grid(GRID_SIZE, std::vector<Tile>(GRID_SIZE))
{
}

void Game::onEnter()
{
    if (!initialized)
    {
        initializeGrid();
        initialized = true;
    }
}

void Game::handleEvent(const sf::Event &event)
{
}

void Game::render(sf::RenderWindow &window)
{
    drawGrid(window);
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            drawTile(window, grid[i][j]);
        }
    }
}

void Game::initializeGrid()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, NUM_COLORS - 1);

    float tileSize = windowSize / GRID_SIZE;
    float padding = tileSize * 0.12f;
    float cornerRadius = tileSize * 0.2f;
    float shapeSize = tileSize - padding * 2;

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            float x = j * tileSize + padding;
            float y = i * tileSize + padding;

            grid[i][j].color = dis(gen);
            grid[i][j].shape.setSize(sf::Vector2f(shapeSize, shapeSize));
            grid[i][j].shape.setPosition(sf::Vector2f(x, y));
            grid[i][j].shape.setCornerRadius(cornerRadius);
            grid[i][j].shape.setFillColor(ColorManager::getColor(grid[i][j].color));
        }
    }
}

void Game::drawGrid(sf::RenderWindow &window)
{
    float tileSize = windowSize / GRID_SIZE;

    sf::RectangleShape line;
    line.setFillColor(sf::Color(180, 180, 180, 200));

    for (int i = 0; i <= GRID_SIZE; i++)
    {
        line.setSize(sf::Vector2f(windowSize, 2.f));
        line.setPosition(sf::Vector2f(0.f, i * tileSize));
        window.draw(line);

        line.setSize(sf::Vector2f(2.f, windowSize));
        line.setPosition(sf::Vector2f(i * tileSize, 0.f));
        window.draw(line);
    }
}

void Game::drawTile(sf::RenderWindow &window, const Tile &tile)
{
    window.draw(tile.shape);
}
