#include "ui/GameBoard.h"
#include "utils/ColorManager.h"
#include "utils/GameConfig.h"
#include <algorithm>
#include <cmath>

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
    if (event.is<sf::Event::MouseButtonPressed>())
    {
        if (gameState != GameState::Idle)
        {
            return;
        }

        if (event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
        {
            float tileSize = getTileSize();
            sf::Vector2f mousePos(event.getIf<sf::Event::MouseButtonPressed>()->position.x,
                                  event.getIf<sf::Event::MouseButtonPressed>()->position.y);
            int col = static_cast<int>(mousePos.x / tileSize);
            int row = static_cast<int>(mousePos.y / tileSize);

            if (row >= 0 && row < gameLogic->getHeight() && col >= 0 && col < gameLogic->getWidth())
            {
                isDragging = true;
                dragStartTile = sf::Vector2i(col, row);
                dragStartPos = mousePos;
                dragCurrentPos = mousePos;
                dragTargetTile = sf::Vector2i(-1, -1);
            }
        }
    }
    else if (event.is<sf::Event::MouseMoved>())
    {
        if (isDragging && gameState == GameState::Idle)
        {
            float tileSize = getTileSize();
            dragCurrentPos = sf::Vector2f(event.getIf<sf::Event::MouseMoved>()->position.x,
                                          event.getIf<sf::Event::MouseMoved>()->position.y);
            
            sf::Vector2f delta = dragCurrentPos - dragStartPos;
            float absDx = std::abs(delta.x);
            float absDy = std::abs(delta.y);
            float threshold = tileSize * 0.3f;
            
            if (absDx > threshold || absDy > threshold)
            {
                sf::Vector2i newTargetTile(-1, -1);
                
                if (absDx > absDy)
                {
                    if (delta.x > threshold)
                    {
                        newTargetTile = sf::Vector2i(dragStartTile.x + 1, dragStartTile.y);
                    }
                    else if (delta.x < -threshold)
                    {
                        newTargetTile = sf::Vector2i(dragStartTile.x - 1, dragStartTile.y);
                    }
                }
                else
                {
                    if (delta.y > threshold)
                    {
                        newTargetTile = sf::Vector2i(dragStartTile.x, dragStartTile.y + 1);
                    }
                    else if (delta.y < -threshold)
                    {
                        newTargetTile = sf::Vector2i(dragStartTile.x, dragStartTile.y - 1);
                    }
                }
                
                if (newTargetTile.x >= 0 && newTargetTile.x < gameLogic->getWidth() &&
                    newTargetTile.y >= 0 && newTargetTile.y < gameLogic->getHeight())
                {
                    dragTargetTile = newTargetTile;
                }
                else
                {
                    dragTargetTile = sf::Vector2i(-1, -1);
                }
            }
            else
            {
                dragTargetTile = sf::Vector2i(-1, -1);
            }
        }
    }
    else if (event.is<sf::Event::MouseButtonReleased>())
    {
        if (event.getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left)
        {
            if (isDragging)
            {
                if (dragTargetTile.x != -1 && dragTargetTile.y != -1)
                {
                    startSwapAnimation(dragStartTile, dragTargetTile);
                }
                else
                {
                    int col = dragStartTile.x;
                    int row = dragStartTile.y;
                    handleTileClick(row, col);
                }
            }
            
            isDragging = false;
            dragStartTile = sf::Vector2i(-1, -1);
            dragTargetTile = sf::Vector2i(-1, -1);
        }
    }
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
    else if (scalingTile.x != -1)
    {
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
            if (isDragging && dragStartTile.x == j && dragStartTile.y == i)
            {
                continue;
            }
            if (isDragging && dragTargetTile.x == j && dragTargetTile.y == i)
            {
                continue;
            }
            window.draw(shapes[i][j]);
        }
    }

    if (isDragging && dragStartTile.x != -1)
    {
        float tileSize = getTileSize();
        float padding = getPadding();
        sf::Vector2f delta = dragCurrentPos - dragStartPos;
        
        sf::Vector2f startTileBasePos(dragStartTile.x * tileSize + padding, 
                                      dragStartTile.y * tileSize + padding);
        
        float absDx = std::abs(delta.x);
        float absDy = std::abs(delta.y);
        sf::Vector2f clampedDelta = delta;
        
        if (absDx > absDy)
        {
            clampedDelta.y = 0;
            clampedDelta.x = std::max(-tileSize, std::min(tileSize, delta.x));
        }
        else
        {
            clampedDelta.x = 0;
            clampedDelta.y = std::max(-tileSize, std::min(tileSize, delta.y));
        }
        
        RoundedRectangle draggedShape = shapes[dragStartTile.y][dragStartTile.x];
        draggedShape.setPosition(startTileBasePos + clampedDelta);
        window.draw(draggedShape);
        
        if (dragTargetTile.x != -1 && dragTargetTile.y != -1)
        {
            sf::Vector2f targetTileBasePos(dragTargetTile.x * tileSize + padding,
                                           dragTargetTile.y * tileSize + padding);
            
            RoundedRectangle targetShape = shapes[dragTargetTile.y][dragTargetTile.x];
            targetShape.setPosition(targetTileBasePos - clampedDelta);
            window.draw(targetShape);
        }
    }

    drawSelectedHighlight(window);
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
    float duration = (gameState == GameState::Swapping) ? 0.3f : 0.8f;
    
    if (elapsed >= duration)
    {
        int height = gameLogic->getHeight();
        int width = gameLogic->getWidth();
        
        if (gameState == GameState::Swapping)
        {
            shapes[swapTile1.y][swapTile1.x].setPosition(targetPositions[swapTile1.y][swapTile1.x]);
            shapes[swapTile2.y][swapTile2.x].setPosition(targetPositions[swapTile2.y][swapTile2.x]);

            auto matches = gameLogic->findMatches();
            if (matches.empty() && !isSwapReversing)
            {
                isSwapReversing = true;
                gameLogic->swapTiles(swapTile1.y, swapTile1.x, swapTile2.y, swapTile2.x);

                float tileSize = getTileSize();
                float padding = getPadding();
                
                startPositions[swapTile1.y][swapTile1.x] = targetPositions[swapTile1.y][swapTile1.x];
                targetPositions[swapTile1.y][swapTile1.x] = sf::Vector2f(swapTile1.x * tileSize + padding, swapTile1.y * tileSize + padding);

                startPositions[swapTile2.y][swapTile2.x] = targetPositions[swapTile2.y][swapTile2.x];
                targetPositions[swapTile2.y][swapTile2.x] = sf::Vector2f(swapTile2.x * tileSize + padding, swapTile2.y * tileSize + padding);

                animationClock.restart();
                return;
            }
            else
            {
                gameState = GameState::CheckingMatches;
                checkAndClearMatches();
            }
        }
        else
        {
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
        }
        
        return;
    }
    
    float t = elapsed / duration;
    
    if (gameState == GameState::Swapping)
    {
        sf::Vector2f startPos1 = startPositions[swapTile1.y][swapTile1.x];
        sf::Vector2f targetPos1 = targetPositions[swapTile1.y][swapTile1.x];
        sf::Vector2f pos1 = startPos1 + (targetPos1 - startPos1) * t;
        shapes[swapTile1.y][swapTile1.x].setPosition(pos1);

        sf::Vector2f startPos2 = startPositions[swapTile2.y][swapTile2.x];
        sf::Vector2f targetPos2 = targetPositions[swapTile2.y][swapTile2.x];
        sf::Vector2f pos2 = startPos2 + (targetPos2 - startPos2) * t;
        shapes[swapTile2.y][swapTile2.x].setPosition(pos2);

        return;
    }
    
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

void GameBoard::handleTileClick(int row, int col)
{
    sf::Vector2i clickedTile(col, row);

    if (selectedTile.x == -1)
    {
        selectedTile = clickedTile;
        scalingTile = clickedTile;
        currentScale = 1.0f;
        targetScale = 1.18f;
        scaleClock.restart();
    }
    else
    {
        if (selectedTile == clickedTile)
        {
            scalingTile = selectedTile;
            currentScale = 1.18f;
            targetScale = 1.0f;
            scaleClock.restart();
            selectedTile = sf::Vector2i(-1, -1);
        }
        else if (areAdjacent(selectedTile, clickedTile))
        {
            scalingTile = selectedTile;
            currentScale = 1.18f;
            targetScale = 1.0f;
            scaleClock.restart();
            pendingSwapTile1 = selectedTile;
            pendingSwapTile2 = clickedTile;
            selectedTile = sf::Vector2i(-1, -1);
        }
        else
        {
            scalingTile = selectedTile;
            currentScale = 1.18f;
            targetScale = 1.0f;
            scaleClock.restart();
            selectedTile = clickedTile;
        }
    }
}

void GameBoard::startSwapAnimation(const sf::Vector2i &tile1, const sf::Vector2i &tile2)
{
    swapTile1 = tile1;
    swapTile2 = tile2;
    isSwapReversing = false;

    float tileSize = getTileSize();
    float padding = getPadding();

    if (isDragging)
    {
        sf::Vector2f delta = dragCurrentPos - dragStartPos;
        float absDx = std::abs(delta.x);
        float absDy = std::abs(delta.y);
        sf::Vector2f clampedDelta = delta;
        
        if (absDx > absDy)
        {
            clampedDelta.y = 0;
            clampedDelta.x = std::max(-tileSize, std::min(tileSize, delta.x));
        }
        else
        {
            clampedDelta.x = 0;
            clampedDelta.y = std::max(-tileSize, std::min(tileSize, delta.y));
        }
        
        sf::Vector2f tile1BasePos(tile1.x * tileSize + padding, tile1.y * tileSize + padding);
        sf::Vector2f tile2BasePos(tile2.x * tileSize + padding, tile2.y * tileSize + padding);
        
        startPositions[tile1.y][tile1.x] = tile1BasePos + clampedDelta;
        startPositions[tile2.y][tile2.x] = tile2BasePos - clampedDelta;
    }
    else
    {
        startPositions[tile1.y][tile1.x] = shapes[tile1.y][tile1.x].getPosition();
        startPositions[tile2.y][tile2.x] = shapes[tile2.y][tile2.x].getPosition();
    }

    targetPositions[tile1.y][tile1.x] = sf::Vector2f(tile2.x * tileSize + padding, tile2.y * tileSize + padding);
    targetPositions[tile2.y][tile2.x] = sf::Vector2f(tile1.x * tileSize + padding, tile1.y * tileSize + padding);

    gameLogic->swapTiles(tile1.y, tile1.x, tile2.y, tile2.x);

    gameState = GameState::Swapping;
    animationClock.restart();
}

bool GameBoard::areAdjacent(const sf::Vector2i &tile1, const sf::Vector2i &tile2) const
{
    int dx = std::abs(tile1.x - tile2.x);
    int dy = std::abs(tile1.y - tile2.y);
    return (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
}

void GameBoard::drawSelectedHighlight(sf::RenderWindow &window)
{
    if (scalingTile.x != -1 && scalingTile.y != -1)
    {
        float elapsed = scaleClock.getElapsedTime().asSeconds();
        float duration = 0.15f;
        float t = std::min(elapsed / duration, 1.0f);
        
        float scale = currentScale + (targetScale - currentScale) * t;
        
        if (t >= 1.0f && targetScale == 1.0f)
        {
            scalingTile = sf::Vector2i(-1, -1);
            
            if (pendingSwapTile1.x != -1 && pendingSwapTile2.x != -1)
            {
                startSwapAnimation(pendingSwapTile1, pendingSwapTile2);
                pendingSwapTile1 = sf::Vector2i(-1, -1);
                pendingSwapTile2 = sf::Vector2i(-1, -1);
            }
        }
        else if (t >= 1.0f && selectedTile.x != -1)
        {
            scale = targetScale;
        }
        
        if (scalingTile.x != -1)
        {
            float tileSize = getTileSize();
            float padding = getPadding();
            float shapeSize = tileSize - padding * 2;
            float scaledSize = shapeSize * scale;
            float offset = (scaledSize - shapeSize) / 2.0f;
            
            RoundedRectangle scaledShape = shapes[scalingTile.y][scalingTile.x];
            scaledShape.setSize(sf::Vector2f(scaledSize, scaledSize));
            scaledShape.setPosition(sf::Vector2f(scalingTile.x * tileSize + padding - offset, 
                                                  scalingTile.y * tileSize + padding - offset));
            
            window.draw(scaledShape);
        }
    }
    else if (selectedTile.x != -1 && selectedTile.y != -1 && gameState == GameState::Idle)
    {
        float tileSize = getTileSize();
        float padding = getPadding();
        float scale = 1.18f;
        
        float shapeSize = tileSize - padding * 2;
        float scaledSize = shapeSize * scale;
        float offset = (scaledSize - shapeSize) / 2.0f;
        
        RoundedRectangle scaledShape = shapes[selectedTile.y][selectedTile.x];
        scaledShape.setSize(sf::Vector2f(scaledSize, scaledSize));
        scaledShape.setPosition(sf::Vector2f(selectedTile.x * tileSize + padding - offset, 
                                              selectedTile.y * tileSize + padding - offset));
        
        window.draw(scaledShape);
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
