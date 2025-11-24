#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct Tile
{
    int colorIndex;
    bool isEmpty = false;
};

struct Match
{
    std::vector<sf::Vector2i> positions;
};

class GameLogic
{
public:
    GameLogic(int width, int height, int numColors);

    void initialize();
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getColorIndex(int row, int col) const;
    bool isEmpty(int row, int col) const;
    const std::vector<int> &getAvailableColors() const { return availableColorIndices; }
    
    std::vector<Match> findMatches();
    void clearMatches(const std::vector<Match> &matches);
    std::vector<sf::Vector2i> applyGravity();
    void fillEmptySpaces();
    void swapTiles(int row1, int col1, int row2, int col2);

private:
    int width;
    int height;
    int numColors;
    std::vector<std::vector<Tile>> grid;
    std::vector<int> availableColorIndices;
    
    void findHorizontalMatches(std::vector<Match> &matches);
    void findVerticalMatches(std::vector<Match> &matches);
};
