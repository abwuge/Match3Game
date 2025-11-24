#pragma once

#include <SFML/Window/Event.hpp>
#include <functional>
#include <unordered_map>

enum class GlobalKey
{
    Backspace,
    Space,
    Enter
};

class KeyboardMonitor
{
public:
    using KeyCallback = std::function<void()>;

    void handleEvent(const sf::Event &event);
    void setCallback(GlobalKey key, KeyCallback callback);
    void clearCallback(GlobalKey key);

private:
    std::unordered_map<GlobalKey, KeyCallback> callbacks;
    sf::Keyboard::Key toSFMLKey(GlobalKey key) const;
};
