#include "core/SceneManager.h"
#include <stdexcept>

SceneManager::SceneManager(sf::RenderWindow &window) : window(window) {}

void SceneManager::registerScene(const std::string &name, std::unique_ptr<Scene> scene)
{
    scene->setSceneManager(this);
    scenes[name] = std::move(scene);
}

void SceneManager::pushScene(const std::string &name)
{
    if (scenes.find(name) == scenes.end())
    {
        throw std::runtime_error("Scene not found: " + name);
    }

    if (!sceneStack.empty())
    {
        getCurrentScene()->onExit();
    }

    sceneStack.push(name);
    getCurrentScene()->onEnter();
}

void SceneManager::popScene()
{
    if (!sceneStack.empty())
    {
        getCurrentScene()->onExit();
        sceneStack.pop();

        if (!sceneStack.empty())
        {
            getCurrentScene()->onEnter();
        }
    }
}

void SceneManager::changeScene(const std::string &name)
{
    if (scenes.find(name) == scenes.end())
    {
        throw std::runtime_error("Scene not found: " + name);
    }

    if (!sceneStack.empty())
    {
        getCurrentScene()->onExit();
        sceneStack.pop();
    }

    sceneStack.push(name);
    getCurrentScene()->onEnter();
}

void SceneManager::handleEvent(const sf::Event &event)
{
    if (hasActiveScene())
    {
        getCurrentScene()->handleEvent(event);
    }
}

void SceneManager::update(float deltaTime)
{
    if (hasActiveScene())
    {
        getCurrentScene()->update(deltaTime);
    }
}

void SceneManager::render()
{
    if (hasActiveScene())
    {
        getCurrentScene()->render(window);
    }
}

bool SceneManager::hasActiveScene() const
{
    return !sceneStack.empty();
}

Scene *SceneManager::getCurrentScene()
{
    if (sceneStack.empty())
    {
        return nullptr;
    }
    return scenes[sceneStack.top()].get();
}
