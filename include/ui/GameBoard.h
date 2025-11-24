#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "core/Scene.h"
#include "core/GameLogic.h"
#include "utils/RoundedRectangle.h"

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
    bool initialized = false;

    void initializeGame();
    void initializeShapes();
    void drawGrid(sf::RenderWindow &window);
};
