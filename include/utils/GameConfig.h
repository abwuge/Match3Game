#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class GameConfig
{
public:
    static GameConfig &getInstance();

    int getNumColors() const { return numColors; }
    void setNumColors(int n) { numColors = n; }

    sf::Vector2i getGridSize() const { return gridSize; }
    void setGridSize(const sf::Vector2i &size) { gridSize = size; }

    const std::vector<int> &getSelectedColorIndices() const { return selectedColorIndices; }
    void setSelectedColorIndices(const std::vector<int> &indices) { selectedColorIndices = indices; }

private:
    GameConfig() : numColors(6), gridSize(8, 8), selectedColorIndices({0, 1, 2, 3, 4, 5}) {}
    GameConfig(const GameConfig &) = delete;
    GameConfig &operator=(const GameConfig &) = delete;

    int numColors;
    sf::Vector2i gridSize;
    std::vector<int> selectedColorIndices;
};
