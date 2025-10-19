#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>

namespace sf
{
    class Event;
    class Font;
    class RenderWindow;
}

class TextInput
{
public:
    TextInput(const sf::Font& font);
    void handleEvent(const sf::Event& event);
    void render(sf::RenderWindow* window);
    const std::string& getText() const;
    void setPosition(sf::Vector2f pos);
    void clear();
private:
    std::string _text;
    const sf::Font& _font;
    size_t _maxLength = 20;
    sf::Vector2f _position;
    bool _showCursor = true;
};
