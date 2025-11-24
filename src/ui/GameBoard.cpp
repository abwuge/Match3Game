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
    initializeGame();
    startFallAnimation();
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

    if (gameState != GameState::Idle)
    {
        updateAnimation();
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
    float tileSize = getTileSize();
    float padding = getPadding();
    float cornerRadius = tileSize * 0.2f;
    float shapeSize = tileSize - padding * 2;

    targetPositions.clear();
    targetPositions.resize(height);
    startPositions.clear();
    startPositions.resize(height);

    for (int i = 0; i < height; i++)
    {
        targetPositions[i].resize(width);
        startPositions[i].resize(width);
        
        for (int j = 0; j < width; j++)
        {
            float x = j * tileSize + padding;
            float y = i * tileSize + padding;

            targetPositions[i][j] = sf::Vector2f(x, y);
            startPositions[i][j] = sf::Vector2f(x, -windowSize);

            shapes[i][j].setSize(sf::Vector2f(shapeSize, shapeSize));
            shapes[i][j].setPosition(startPositions[i][j]);
            shapes[i][j].setCornerRadius(cornerRadius);
            
            int colorIndex = gameLogic->getColorIndex(i, j);
            shapes[i][j].setFillColor(ColorManager::getColor(colorIndex));
        }
    }
}

void GameBoard::updateAnimation()
{
    float elapsed = animationClock.getElapsedTime().asSeconds();
    float duration = 0.8f;
    
    if (elapsed >= duration)
    {
        int height = gameLogic->getHeight();
        int width = gameLogic->getWidth();
        
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                shapes[i][j].setPosition(targetPositions[i][j]);
            }
        }
        
        if (gameState == GameState::FallingInitial)
        {
            gameState = GameState::CheckingMatches;
            checkAndClearMatches();
        }
        else if (gameState == GameState::FallingAfterClear)
        {
            gameState = GameState::CheckingMatches;
            checkAndClearMatches();
        }
        
        return;
    }
    
    float t = elapsed / duration;
    
    int height = gameLogic->getHeight();
    int width = gameLogic->getWidth();
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sf::Vector2f startPos = startPositions[i][j];
            sf::Vector2f targetPos = targetPositions[i][j];
            
            float distance = targetPos.y - startPos.y;
            float y = startPos.y + distance * t * t;
            
            shapes[i][j].setPosition(sf::Vector2f(targetPos.x, y));
        }
    }
}

void GameBoard::startFallAnimation(const std::vector<sf::Vector2i> &affectedColumns)
{
    int height = gameLogic->getHeight();
    int width = gameLogic->getWidth();
    float tileSize = getTileSize();
    float padding = getPadding();
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float x = j * tileSize + padding;
            float y = i * tileSize + padding;
            targetPositions[i][j] = sf::Vector2f(x, y);
            startPositions[i][j] = sf::Vector2f(x, -windowSize);
            
            int colorIndex = gameLogic->getColorIndex(i, j);
            shapes[i][j].setFillColor(ColorManager::getColor(colorIndex));
        }
    }
    
    gameState = GameState::FallingInitial;
    animationClock.restart();
}

void GameBoard::checkAndClearMatches()
{
    auto matches = gameLogic->findMatches();
    
    if (!matches.empty())
    {
        gameState = GameState::ClearingMatches;
        
        int height = gameLogic->getHeight();
        int width = gameLogic->getWidth();
        float tileSize = getTileSize();
        float padding = getPadding();
        
        std::vector<std::vector<int>> oldColorIndices(height);
        for (int i = 0; i < height; i++)
        {
            oldColorIndices[i].resize(width);
            for (int j = 0; j < width; j++)
            {
                oldColorIndices[i][j] = gameLogic->getColorIndex(i, j);
            }
        }
        
        gameLogic->clearMatches(matches);
        
        std::vector<int> numCleared(width, 0);
        for (int j = 0; j < width; j++)
        {
            for (int i = 0; i < height; i++)
            {
                if (gameLogic->isEmpty(i, j))
                {
                    numCleared[j]++;
                }
            }
        }
        
        auto affectedColumns = gameLogic->applyGravity();
        gameLogic->fillEmptySpaces();
        
        for (int j = 0; j < width; j++)
        {
            int cleared = numCleared[j];
            
            if (cleared > 0)
            {
                for (int i = 0; i < height; i++)
                {
                    float x = j * tileSize + padding;
                    float y = i * tileSize + padding;
                    targetPositions[i][j] = sf::Vector2f(x, y);
                    
                    if (i < cleared)
                    {
                        startPositions[i][j] = sf::Vector2f(x, -(cleared - i) * tileSize);
                    }
                    else
                    {
                        startPositions[i][j] = sf::Vector2f(x, (i - cleared) * tileSize + padding);
                    }
                    
                    int colorIndex = gameLogic->getColorIndex(i, j);
                    shapes[i][j].setFillColor(ColorManager::getColor(colorIndex));
                }
            }
            else
            {
                for (int i = 0; i < height; i++)
                {
                    float x = j * tileSize + padding;
                    float y = i * tileSize + padding;
                    targetPositions[i][j] = sf::Vector2f(x, y);
                    startPositions[i][j] = sf::Vector2f(x, y);
                }
            }
        }
        
        gameState = GameState::FallingAfterClear;
        animationClock.restart();
    }
    else
    {
        gameState = GameState::Idle;
    }
}

float GameBoard::getTileSize() const
{
    if (!gameLogic) return 0.0f;
    int width = gameLogic->getWidth();
    int height = gameLogic->getHeight();
    int maxDim = std::max(width, height);
    return windowSize / maxDim;
}

float GameBoard::getPadding() const
{
    return getTileSize() * 0.12f;
}

void GameBoard::drawGrid(sf::RenderWindow &window)
{
    if (!gameLogic)
    {
        return;
    }

    int width = gameLogic->getWidth();
    int height = gameLogic->getHeight();
    float tileSize = getTileSize();

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
