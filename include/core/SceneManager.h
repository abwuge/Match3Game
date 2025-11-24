#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include <unordered_map>
#include <string>
#include "Scene.h"

class SceneManager
{
public:
    SceneManager(sf::RenderWindow &window);

    void registerScene(const std::string &name, std::unique_ptr<Scene> scene);
    void pushScene(const std::string &name);
    void popScene();
    void changeScene(const std::string &name);

    void handleEvent(const sf::Event &event);
    void update(float deltaTime);
    void render();

    bool hasActiveScene() const;

private:
    sf::RenderWindow &window;
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
    std::stack<std::string> sceneStack;

    Scene *getCurrentScene();
};
