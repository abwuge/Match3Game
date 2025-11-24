#include "ui/SettingsScene.h"
#include "core/SceneManager.h"
#include "utils/ColorManager.h"
#include "utils/GameConfig.h"
#include <algorithm>
#include <random>

SettingsScene::SettingsScene(float windowWidth, float windowHeight)
    : windowWidth(windowWidth),
      windowHeight(windowHeight),
      isSelectingGrid(false),
      numColors(6),
      gridSize(8, 8)
{
    availableColors = ColorManager::getAllColors();
    selectedColorIndices = {0, 1, 2, 3, 4, 5};

    colorSelectorStart = sf::Vector2f(50.f, 50.f);
    colorBoxSize = 50.f;

    gridAreaStart = sf::Vector2f(50.f, 200.f);
    gridCellSize = 15.f;

    gridSelectionStart = sf::Vector2i(0, 0);
    gridSelectionEnd = sf::Vector2i(7, 7);

    gridCellColors.resize(maxGridSize, std::vector<sf::Color>(maxGridSize));
    generateGridColors();
}

void SettingsScene::onEnter()
{
    GameConfig &config = GameConfig::getInstance();
    selectedColorIndices = config.getSelectedColorIndices();
    sf::Vector2i currentGridSize = config.getGridSize();
    gridSelectionStart = sf::Vector2i(0, 0);
    gridSelectionEnd = sf::Vector2i(currentGridSize.x - 1, currentGridSize.y - 1);
}

void SettingsScene::handleEvent(const sf::Event &event)
{
    if (event.is<sf::Event::KeyPressed>())
    {
        if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter)
        {
            saveSettings();
            sceneManager->popScene();
        }
        else if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
        {
            sceneManager->popScene();
        }
    }

    if (event.is<sf::Event::MouseButtonPressed>())
    {
        if (event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f mousePos(event.getIf<sf::Event::MouseButtonPressed>()->position.x,
                                  event.getIf<sf::Event::MouseButtonPressed>()->position.y);

            int colorIdx = getColorIndexAtPosition(mousePos);
            if (colorIdx >= 0)
            {
                auto it = std::find(selectedColorIndices.begin(), selectedColorIndices.end(), colorIdx);
                if (it != selectedColorIndices.end())
                {
                    selectedColorIndices.erase(it);
                }
                else
                {
                    selectedColorIndices.push_back(colorIdx);
                }
                generateGridColors();
            }

            sf::Vector2i gridCell = getGridCellAtPosition(mousePos);
            if (gridCell.x >= 0)
            {
                isSelectingGrid = true;
                gridSelectionStart = gridCell;
                gridSelectionEnd = gridCell;
            }
        }
    }

    if (event.is<sf::Event::MouseButtonReleased>())
    {
        if (event.getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left)
        {
            isSelectingGrid = false;
        }
    }

    if (event.is<sf::Event::MouseMoved>())
    {
        if (isSelectingGrid)
        {
            sf::Vector2f mousePos(event.getIf<sf::Event::MouseMoved>()->position.x,
                                  event.getIf<sf::Event::MouseMoved>()->position.y);
            sf::Vector2i gridCell = getGridCellAtPosition(mousePos);
            if (gridCell.x >= 0)
            {
                gridSelectionEnd = gridCell;
            }
        }
    }
}

void SettingsScene::render(sf::RenderWindow &window)
{
    renderColorSelector(window);
    renderGridSelector(window);
}

void SettingsScene::renderColorSelector(sf::RenderWindow &window)
{
    for (size_t i = 0; i < availableColors.size(); i++)
    {
        sf::RectangleShape colorBox(sf::Vector2f(colorBoxSize, colorBoxSize));
        colorBox.setPosition(sf::Vector2f(colorSelectorStart.x + i * (colorBoxSize + 10.f), colorSelectorStart.y));
        colorBox.setFillColor(availableColors[i]);

        bool isSelected = std::find(selectedColorIndices.begin(), selectedColorIndices.end(), i) != selectedColorIndices.end();
        
        if (isSelected)
        {
            colorBox.setOutlineColor(sf::Color::White);
            colorBox.setOutlineThickness(4.f);
        }
        else
        {
            colorBox.setOutlineColor(sf::Color(100, 100, 100));
            colorBox.setOutlineThickness(2.f);
        }

        window.draw(colorBox);
    }
}

void SettingsScene::renderGridSelector(sf::RenderWindow &window)
{
    int minX = std::min(gridSelectionStart.x, gridSelectionEnd.x);
    int maxX = std::max(gridSelectionStart.x, gridSelectionEnd.x);
    int minY = std::min(gridSelectionStart.y, gridSelectionEnd.y);
    int maxY = std::max(gridSelectionStart.y, gridSelectionEnd.y);

    for (int i = 0; i < maxGridSize; i++)
    {
        for (int j = 0; j < maxGridSize; j++)
        {
            sf::RectangleShape cell(sf::Vector2f(gridCellSize - 1.f, gridCellSize - 1.f));
            cell.setPosition(sf::Vector2f(gridAreaStart.x + j * gridCellSize, gridAreaStart.y + i * gridCellSize));

            if (j >= minX && j <= maxX && i >= minY && i <= maxY)
            {
                cell.setFillColor(gridCellColors[i][j]);
            }
            else
            {
                cell.setFillColor(sf::Color(120, 120, 120));
            }

            window.draw(cell);
        }
    }

    sf::RectangleShape selectionOutline(
        sf::Vector2f((maxX - minX + 1) * gridCellSize, (maxY - minY + 1) * gridCellSize)
    );
    selectionOutline.setPosition(
        sf::Vector2f(gridAreaStart.x + minX * gridCellSize,
                     gridAreaStart.y + minY * gridCellSize)
    );
    selectionOutline.setFillColor(sf::Color::Transparent);
    selectionOutline.setOutlineColor(sf::Color::White);
    selectionOutline.setOutlineThickness(3.f);
    window.draw(selectionOutline);
}

void SettingsScene::generateGridColors()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 0; i < maxGridSize; i++)
    {
        for (int j = 0; j < maxGridSize; j++)
        {
            if (selectedColorIndices.empty())
            {
                gridCellColors[i][j] = sf::Color(120, 120, 120);
            }
            else
            {
                std::uniform_int_distribution<> dis(0, selectedColorIndices.size() - 1);
                int randomIdx = dis(gen);
                int colorIdx = selectedColorIndices[randomIdx];
                gridCellColors[i][j] = availableColors[colorIdx];
            }
        }
    }
}

int SettingsScene::getColorIndexAtPosition(const sf::Vector2f &pos)
{
    for (size_t i = 0; i < availableColors.size(); i++)
    {
        float x = colorSelectorStart.x + i * (colorBoxSize + 10.f);
        float y = colorSelectorStart.y;
        
        if (pos.x >= x && pos.x <= x + colorBoxSize &&
            pos.y >= y && pos.y <= y + colorBoxSize)
        {
            return i;
        }
    }
    return -1;
}

sf::Vector2i SettingsScene::getGridCellAtPosition(const sf::Vector2f &pos)
{
    float relX = pos.x - gridAreaStart.x;
    float relY = pos.y - gridAreaStart.y;

    if (relX < 0 || relY < 0 || 
        relX >= maxGridSize * gridCellSize || 
        relY >= maxGridSize * gridCellSize)
    {
        return sf::Vector2i(-1, -1);
    }

    int cellX = static_cast<int>(relX / gridCellSize);
    int cellY = static_cast<int>(relY / gridCellSize);

    return sf::Vector2i(cellX, cellY);
}

void SettingsScene::saveSettings()
{
    GameConfig &config = GameConfig::getInstance();
    
    config.setSelectedColorIndices(selectedColorIndices);
    config.setNumColors(selectedColorIndices.size());
    
    int minX = std::min(gridSelectionStart.x, gridSelectionEnd.x);
    int maxX = std::max(gridSelectionStart.x, gridSelectionEnd.x);
    int minY = std::min(gridSelectionStart.y, gridSelectionEnd.y);
    int maxY = std::max(gridSelectionStart.y, gridSelectionEnd.y);

    sf::Vector2i newGridSize(maxX - minX + 1, maxY - minY + 1);
    config.setGridSize(newGridSize);
}
