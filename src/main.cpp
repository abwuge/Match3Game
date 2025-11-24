#include <SFML/Graphics.hpp>
#include "core/Game.h"
#include "ui/MainMenu.h"
#include "utils/KeyboardMonitor.h"

enum class AppState
{
    MainMenu,
    Playing,
    Settings
};

int main()
{
    auto desktop = sf::VideoMode::getDesktopMode();
    unsigned int windowSize = static_cast<unsigned int>(std::min(desktop.size.x, desktop.size.y) * 0.7f);

    auto window = sf::RenderWindow(sf::VideoMode({windowSize, windowSize}), "Match 3 Game", sf::Style::Close);
    window.setFramerateLimit(144);

    MainMenu menu(static_cast<float>(windowSize), static_cast<float>(windowSize));
    Game game(static_cast<float>(windowSize));
    KeyboardMonitor keyboardMonitor;

    AppState appState = AppState::MainMenu;
    bool gameInitialized = false;

    keyboardMonitor.setCallback(GlobalKey::Backspace, [&appState]() {
        if (appState == AppState::Playing || appState == AppState::Settings)
        {
            appState = AppState::MainMenu;
        }
    });

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            keyboardMonitor.handleEvent(event.value());

            if (appState == AppState::MainMenu)
            {
                ButtonAction action = menu.handleEvent(event.value(), window);
                if (action == ButtonAction::StartGame)
                {
                    appState = AppState::Playing;
                }
                else if (action == ButtonAction::OpenSettings)
                {
                    appState = AppState::Settings;
                }
            }
        }

        window.clear(sf::Color(245, 245, 245));

        if (appState == AppState::MainMenu)
        {
            menu.draw(window);
        }
        else if (appState == AppState::Playing)
        {
            if (!gameInitialized)
            {
                game.initialize();
                gameInitialized = true;
            }

            game.render(window);
        }

        window.display();
    }
}
