#include "core/GameLogic.h"
#include "utils/GameConfig.h"
#include <random>

GameLogic::GameLogic(int width, int height, int numColors)
    : width(width), height(height), numColors(numColors)
{
    grid.resize(height, std::vector<Tile>(width));
    GameConfig &config = GameConfig::getInstance();
    availableColorIndices = config.getSelectedColorIndices();
}

void GameLogic::initialize()
{
    if (availableColorIndices.empty())
    {
        availableColorIndices = {0, 1, 2, 3, 4, 5};
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, availableColorIndices.size() - 1);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int randomIdx = dis(gen);
            grid[i][j].colorIndex = availableColorIndices[randomIdx];
        }
    }
}

int GameLogic::getColorIndex(int row, int col) const
{
    if (row >= 0 && row < height && col >= 0 && col < width)
    {
        return grid[row][col].colorIndex;
    }
    return -1;
}
