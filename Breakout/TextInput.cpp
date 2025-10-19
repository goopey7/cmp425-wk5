#include "TextInput.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

TextInput::TextInput(const sf::Font& font)
	: _font(font)
{
}

void TextInput::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::TextEntered)
	{
		// backspace
		if (event.text.unicode == '\b')
		{
			if (!_text.empty())
			{
				_text.pop_back();
			}
		}
		// is text ascii?
		else if (event.text.unicode < 128)
		{
			if (_text.size() < _maxLength)
			{
				_text += static_cast<char>(event.text.unicode);
			}
		}
	}
}

void TextInput::render(sf::RenderWindow* window)
{
	sf::Text displayText;
	displayText.setFont(_font);
	displayText.setString(_text + (_showCursor ? "|" : ""));
	displayText.setPosition(_position);
	window->draw(displayText);
}

const std::string& TextInput::getText() const { return _text; }
void TextInput::setPosition(sf::Vector2f pos){_position = pos;}
void TextInput::clear() { _text.clear();}
