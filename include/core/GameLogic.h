#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct Tile
{
    int colorIndex;
};

class GameLogic
{
public:
    GameLogic(int width, int height, int numColors);

    void initialize();
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getColorIndex(int row, int col) const;
    const std::vector<int> &getAvailableColors() const { return availableColorIndices; }

private:
    int width;
    int height;
    int numColors;
    std::vector<std::vector<Tile>> grid;
    std::vector<int> availableColorIndices;
};
