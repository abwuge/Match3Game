#include "ui/MainMenu.h"
#include "core/SceneManager.h"

MainMenu::MainMenu(float windowWidth, float windowHeight)
    : startButton(sf::Vector2f(windowWidth / 2.f - 150.f, windowHeight / 2.f - 60.f)),
      settingsButton(sf::Vector2f(windowWidth / 2.f + 30.f, windowHeight / 2.f - 60.f)),
      windowWidth(windowWidth),
      windowHeight(windowHeight)
{
}

void MainMenu::handleEvent(const sf::Event &event)
{
    if (event.is<sf::Event::MouseMoved>())
    {
        sf::Vector2f mousePos(event.getIf<sf::Event::MouseMoved>()->position.x,
                              event.getIf<sf::Event::MouseMoved>()->position.y);
        startButton.updateHover(mousePos);
        settingsButton.updateHover(mousePos);
    }

    if (event.is<sf::Event::MouseButtonPressed>())
    {
        if (event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f mousePos(event.getIf<sf::Event::MouseButtonPressed>()->position.x,
                                  event.getIf<sf::Event::MouseButtonPressed>()->position.y);

            if (startButton.isMouseOver(mousePos))
            {
                sceneManager->pushScene("game");
            }
            else if (settingsButton.isMouseOver(mousePos))
            {
                sceneManager->pushScene("settings");
            }
        }
    }
}

void MainMenu::render(sf::RenderWindow &window)
{
    startButton.draw(window);
    settingsButton.draw(window);
}
