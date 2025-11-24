#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Scene.h"
#include "utils/RoundedRectangle.h"

const int GRID_SIZE = 8;
const int NUM_COLORS = 6;

struct Tile
{
    int color;
    RoundedRectangle shape;
};

class Game : public Scene
{
public:
    Game(float windowSize);

    void onEnter() override;
    void handleEvent(const sf::Event &event) override;
    void render(sf::RenderWindow &window) override;

private:
    float windowSize;
    std::vector<std::vector<Tile>> grid;
    bool initialized = false;

    void initializeGrid();
    void drawGrid(sf::RenderWindow &window);
    void drawTile(sf::RenderWindow &window, const Tile &tile);
};
