#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "core/Scene.h"
#include "core/GameLogic.h"
#include "utils/RoundedRectangle.h"

enum class GameState
{
    Idle,
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

    void initializeGame();
    void initializeShapes();
    void drawGrid(sf::RenderWindow &window);
    void updateAnimation();
    void startFallAnimation(const std::vector<sf::Vector2i> &affectedTiles = {});
    void checkAndClearMatches();
    float getTileSize() const;
    float getPadding() const;
};
