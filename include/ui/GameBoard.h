#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "core/Scene.h"
#include "core/GameLogic.h"
#include "utils/RoundedRectangle.h"

enum class GameState
{
    Idle,
    Swapping,
    FallingInitial,
    CheckingMatches,
    ClearingMatches,
    FallingAfterClear
};

class GameBoard : public Scene
{
public:
    GameBoard(float windowSize);

    void onEnter() override;
    void handleEvent(const sf::Event &event) override;
    void render(sf::RenderWindow &window) override;

private:
    float windowSize;
    std::shared_ptr<GameLogic> gameLogic;
    std::vector<std::vector<RoundedRectangle>> shapes;

    std::vector<std::vector<sf::Vector2f>> targetPositions;
    std::vector<std::vector<sf::Vector2f>> startPositions;
    sf::Clock animationClock;
    GameState gameState = GameState::Idle;

    sf::Vector2i selectedTile = sf::Vector2i(-1, -1);
    sf::Vector2i swapTile1 = sf::Vector2i(-1, -1);
    sf::Vector2i swapTile2 = sf::Vector2i(-1, -1);
    bool isSwapReversing = false;
    sf::Clock scaleClock;
    float currentScale = 1.0f;
    float targetScale = 1.0f;
    sf::Vector2i scalingTile = sf::Vector2i(-1, -1);
    sf::Vector2i pendingSwapTile1 = sf::Vector2i(-1, -1);
    sf::Vector2i pendingSwapTile2 = sf::Vector2i(-1, -1);

    bool isDragging = false;
    sf::Vector2i dragStartTile = sf::Vector2i(-1, -1);
    sf::Vector2f dragStartPos;
    sf::Vector2f dragCurrentPos;
    sf::Vector2i dragTargetTile = sf::Vector2i(-1, -1);

    void initializeGame();
    void initializeShapes();
    void drawGrid(sf::RenderWindow &window);
    void updateAnimation();
    void startFallAnimation(const std::vector<sf::Vector2i> &affectedTiles = {});
    void checkAndClearMatches();
    void handleTileClick(int row, int col);
    void startSwapAnimation(const sf::Vector2i &tile1, const sf::Vector2i &tile2);
    bool areAdjacent(const sf::Vector2i &tile1, const sf::Vector2i &tile2) const;
    void drawSelectedHighlight(sf::RenderWindow &window);
    float getTileSize() const;
    float getPadding() const;
};
