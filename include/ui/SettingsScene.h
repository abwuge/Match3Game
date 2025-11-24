#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "core/Scene.h"
#include "utils/RoundedRectangle.h"

class SettingsScene : public Scene
{
public:
    SettingsScene(float windowWidth, float windowHeight);

    void handleEvent(const sf::Event &event) override;
    void render(sf::RenderWindow &window) override;
    void onEnter() override;

private:
    float windowWidth;
    float windowHeight;

    std::vector<sf::Color> availableColors;
    std::vector<int> selectedColorIndices;
    sf::Vector2f colorSelectorStart;
    float colorBoxSize;
    
    sf::Vector2i gridSelectionStart;
    sf::Vector2i gridSelectionEnd;
    bool isSelectingGrid;
    sf::Vector2f gridAreaStart;
    float gridCellSize;
    const int maxGridSize = 32;
    std::vector<std::vector<sf::Color>> gridCellColors;

    int numColors;
    sf::Vector2i gridSize;

    void renderColorSelector(sf::RenderWindow &window);
    void renderGridSelector(sf::RenderWindow &window);
    int getColorIndexAtPosition(const sf::Vector2f &pos);
    sf::Vector2i getGridCellAtPosition(const sf::Vector2f &pos);
    void saveSettings();
    void generateGridColors();
};
