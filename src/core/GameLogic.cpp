#include "core/GameLogic.h"
#include "utils/GameConfig.h"
#include <random>
#include <set>

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
            grid[i][j].isEmpty = false;
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

bool GameLogic::isEmpty(int row, int col) const
{
    if (row >= 0 && row < height && col >= 0 && col < width)
    {
        return grid[row][col].isEmpty;
    }
    return true;
}

std::vector<Match> GameLogic::findMatches()
{
    std::vector<Match> matches;
    findHorizontalMatches(matches);
    findVerticalMatches(matches);
    return matches;
}

void GameLogic::findHorizontalMatches(std::vector<Match> &matches)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (grid[i][j].isEmpty) continue;
            
            int colorIndex = grid[i][j].colorIndex;
            int count = 1;
            
            while (j + count < width && 
                   !grid[i][j + count].isEmpty && 
                   grid[i][j + count].colorIndex == colorIndex)
            {
                count++;
            }
            
            if (count >= 3)
            {
                Match match;
                for (int k = 0; k < count; k++)
                {
                    match.positions.push_back(sf::Vector2i(j + k, i));
                }
                matches.push_back(match);
                j += count - 1;
            }
        }
    }
}

void GameLogic::findVerticalMatches(std::vector<Match> &matches)
{
    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            if (grid[i][j].isEmpty) continue;
            
            int colorIndex = grid[i][j].colorIndex;
            int count = 1;
            
            while (i + count < height && 
                   !grid[i + count][j].isEmpty && 
                   grid[i + count][j].colorIndex == colorIndex)
            {
                count++;
            }
            
            if (count >= 3)
            {
                Match match;
                for (int k = 0; k < count; k++)
                {
                    match.positions.push_back(sf::Vector2i(j, i + k));
                }
                matches.push_back(match);
                i += count - 1;
            }
        }
    }
}

void GameLogic::clearMatches(const std::vector<Match> &matches)
{
    std::set<std::pair<int, int>> toRemove;
    
    for (const auto &match : matches)
    {
        for (const auto &pos : match.positions)
        {
            toRemove.insert({pos.y, pos.x});
        }
    }
    
    for (const auto &pos : toRemove)
    {
        grid[pos.first][pos.second].isEmpty = true;
    }
}

std::vector<sf::Vector2i> GameLogic::applyGravity()
{
    std::vector<sf::Vector2i> affectedColumns;
    
    for (int j = 0; j < width; j++)
    {
        bool columnChanged = false;
        int writePos = height - 1;
        
        for (int i = height - 1; i >= 0; i--)
        {
            if (!grid[i][j].isEmpty)
            {
                if (i != writePos)
                {
                    grid[writePos][j] = grid[i][j];
                    grid[i][j].isEmpty = true;
                    columnChanged = true;
                }
                writePos--;
            }
        }
        
        if (columnChanged)
        {
            affectedColumns.push_back(sf::Vector2i(j, 0));
        }
    }
    
    return affectedColumns;
}

void GameLogic::fillEmptySpaces()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, availableColorIndices.size() - 1);
    
    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            if (grid[i][j].isEmpty)
            {
                int randomIdx = dis(gen);
                grid[i][j].colorIndex = availableColorIndices[randomIdx];
                grid[i][j].isEmpty = false;
            }
        }
    }
}
