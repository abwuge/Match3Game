#include <SFML/Graphics.hpp>
#include "core/SceneManager.h"
#include "ui/MainMenu.h"
#include "ui/SettingsScene.h"
#include "ui/GameBoard.h"
#include "utils/KeyboardMonitor.h"

int main()
{
    auto desktop = sf::VideoMode::getDesktopMode();
    unsigned int windowSize = static_cast<unsigned int>(std::min(desktop.size.x, desktop.size.y) * 0.7f);

    auto window = sf::RenderWindow(sf::VideoMode({windowSize, windowSize}), "Match 3 Game", sf::Style::Close);
    window.setFramerateLimit(144);

    SceneManager sceneManager(window);
    KeyboardMonitor keyboardMonitor;

    sceneManager.registerScene("menu", std::make_unique<MainMenu>(static_cast<float>(windowSize), static_cast<float>(windowSize)));
    sceneManager.registerScene("game", std::make_unique<GameBoard>(static_cast<float>(windowSize)));
    sceneManager.registerScene("settings", std::make_unique<SettingsScene>(static_cast<float>(windowSize), static_cast<float>(windowSize)));

    sceneManager.pushScene("menu");

    keyboardMonitor.setCallback(GlobalKey::Backspace, [&sceneManager]()
                                { sceneManager.popScene(); });

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            keyboardMonitor.handleEvent(event.value());
            sceneManager.handleEvent(event.value());
        }

        window.clear(sf::Color(245, 245, 245));
        sceneManager.render();
        window.display();
    }
}
