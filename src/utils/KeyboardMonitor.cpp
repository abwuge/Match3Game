#include "utils/KeyboardMonitor.h"

void KeyboardMonitor::handleEvent(const sf::Event& event)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        for (const auto& [key, callback] : callbacks)
        {
            if (keyPressed->code == toSFMLKey(key))
            {
                callback();
                break;
            }
        }
    }
}

void KeyboardMonitor::setCallback(GlobalKey key, KeyCallback callback)
{
    callbacks[key] = callback;
}

void KeyboardMonitor::clearCallback(GlobalKey key)
{
    callbacks.erase(key);
}

sf::Keyboard::Key KeyboardMonitor::toSFMLKey(GlobalKey key) const
{
    switch (key)
    {
        case GlobalKey::Backspace:
            return sf::Keyboard::Key::Backspace;
        case GlobalKey::Space:
            return sf::Keyboard::Key::Space;
        case GlobalKey::Enter:
            return sf::Keyboard::Key::Enter;
        default:
            return sf::Keyboard::Key::Unknown;
    }
}
