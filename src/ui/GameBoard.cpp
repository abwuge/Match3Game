#include "ui/GameBoard.h"
#include "utils/ColorManager.h"
#include "utils/GameConfig.h"
#include <algorithm>

GameBoard::GameBoard(float windowSize)
    : windowSize(windowSize)
{
}

void GameBoard::onEnter()
{
    GameConfig &config = GameConfig::getInstance();
    sf::Vector2i gridSize = config.getGridSize();
    int numColors = config.getNumColors();
    
    if (!initialized || !gameLogic || 
        gameLogic->getWidth() != gridSize.x || 
        gameLogic->getHeight() != gridSize.y)
    {
        initializeGame();
        initialized = true;
    }
}

void GameBoard::handleEvent(const sf::Event &event)
{
}

void GameBoard::render(sf::RenderWindow &window)
{
    if (!gameLogic || shapes.empty())
    {
        return;
    }

    drawGrid(window);
    
    int height = gameLogic->getHeight();
    int width = gameLogic->getWidth();
    
    if (static_cast<int>(shapes.size()) < height)
    {
        return;
    }
    
    for (int i = 0; i < height; i++)
    {
        if (static_cast<int>(shapes[i].size()) < width)
        {
            continue;
        }
        
        for (int j = 0; j < width; j++)
        {
            window.draw(shapes[i][j]);
        }
    }
}

void GameBoard::initializeGame()
{
    GameConfig &config = GameConfig::getInstance();
    sf::Vector2i gridSize = config.getGridSize();
    int numColors = config.getNumColors();
    
    gameLogic = std::make_shared<GameLogic>(gridSize.x, gridSize.y, numColors);
    gameLogic->initialize();
    
    int height = gameLogic->getHeight();
    int width = gameLogic->getWidth();
    
    shapes.clear();
    shapes.resize(height);
    for (int i = 0; i < height; i++)
    {
        shapes[i].resize(width);
    }
    
    initializeShapes();
}

void GameBoard::initializeShapes()
{
    int width = gameLogic->getWidth();
    int height = gameLogic->getHeight();
    int maxDim = std::max(width, height);
    float tileSize = windowSize / maxDim;
    float padding = tileSize * 0.12f;
    float cornerRadius = tileSize * 0.2f;
    float shapeSize = tileSize - padding * 2;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float x = j * tileSize + padding;
            float y = i * tileSize + padding;

            shapes[i][j].setSize(sf::Vector2f(shapeSize, shapeSize));
            shapes[i][j].setPosition(sf::Vector2f(x, y));
            shapes[i][j].setCornerRadius(cornerRadius);
            
            int colorIndex = gameLogic->getColorIndex(i, j);
            shapes[i][j].setFillColor(ColorManager::getColor(colorIndex));
        }
    }
}

void GameBoard::drawGrid(sf::RenderWindow &window)
{
    if (!gameLogic)
    {
        return;
    }

    int width = gameLogic->getWidth();
    int height = gameLogic->getHeight();
    int maxDim = std::max(width, height);
    float tileSize = windowSize / maxDim;

    sf::RectangleShape line;
    line.setFillColor(sf::Color(180, 180, 180, 200));

    for (int i = 0; i <= height; i++)
    {
        line.setSize(sf::Vector2f(width * tileSize, 2.f));
        line.setPosition(sf::Vector2f(0.f, i * tileSize));
        window.draw(line);
    }

    for (int i = 0; i <= width; i++)
    {
        line.setSize(sf::Vector2f(2.f, height * tileSize));
        line.setPosition(sf::Vector2f(i * tileSize, 0.f));
        window.draw(line);
    }
}
