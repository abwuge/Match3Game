#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class SceneManager;

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void onEnter() {}
    virtual void onExit() {}
    virtual void handleEvent(const sf::Event &event) = 0;
    virtual void update(float deltaTime) {}
    virtual void render(sf::RenderWindow &window) = 0;

    void setSceneManager(SceneManager *manager) { sceneManager = manager; }

protected:
    SceneManager *sceneManager = nullptr;
};
