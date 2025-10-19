#include "Leaderboard.h"
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <algorithm>
#include <ranges>

Leaderboard::Leaderboard(const sf::Font& font)
    : _inputField(font), _font(font)
{
}

bool Leaderboard::handleEvent(const sf::Event& event)
{
    if (event.text.unicode == '\r' || event.text.unicode == '\n')
    {
        _playerName = _inputField.getText();
        return true;
    }
    _inputField.handleEvent(event);
    return false;
}

bool Leaderboard::isEntryWorthy(LeaderboardEntry entry) const
{
    return std::ranges::any_of(_entries, [&entry](const auto& opt)
        { return !opt.has_value() || entry < opt.value(); });
}

void Leaderboard::addEntry(LeaderboardEntry entry)
{
    auto insertIt =
        std::ranges::find_if(_entries, [&entry](const auto& existingOpt)
		{
			return !existingOpt.has_value() || entry < existingOpt.value();
		}
	);

    if (insertIt != _entries.end())
    {
        std::ranges::rotate(insertIt, _entries.end() - 1, _entries.end());
        *insertIt = entry;
    }
}

void Leaderboard::render(sf::RenderWindow* window)
{
	sf::RectangleShape overlay(sf::Vector2f(window->getSize()));
	overlay.setFillColor(sf::Color(0, 0, 0, 200));
	window->draw(overlay);
	
	sf::Vector2u windowSize = window->getSize();
	float centerX = windowSize.x / 2.f;
	
	sf::Text title;
	title.setFont(_font);
	title.setString("LEADERBOARD");
	title.setCharacterSize(50);
	title.setFillColor(sf::Color::Yellow);
	sf::FloatRect titleBounds = title.getLocalBounds();
	title.setPosition(centerX - titleBounds.width / 2.f, 50);
	window->draw(title);
	
	sf::Text headers;
	headers.setFont(_font);
	headers.setString("RANK  NAME      LEVEL  SCORE   TIME");
	headers.setCharacterSize(25);
	headers.setFillColor(sf::Color::Cyan);
	sf::FloatRect headerBounds = headers.getLocalBounds();
	headers.setPosition(centerX - headerBounds.width / 2.f, 130);
	window->draw(headers);
	
	float entryStartX = centerX - 250;
	
	for (uint8_t i = 0; i < _entries.size(); ++i)
	{
		if (!_entries[i].has_value())
		{
			break;
		}
		
		const LeaderboardEntry& entry = _entries[i].value();
		
		sf::Text entryText;
		entryText.setFont(_font);
		
		std::ostringstream oss;
		oss << std::setw(4) << (i + 1) << ".   "
			<< std::setw(8) << std::left << entry.name.value_or("<NONE>") << "  "
			<< std::setw(5) << std::right << static_cast<int>(entry.levelReached) << "  "
			<< std::setw(8) << entry.score << "   "
			<< std::setw(7) << std::fixed << std::setprecision(1) << entry.time << "s";
		
		entryText.setString(oss.str());
		entryText.setCharacterSize(30);
		entryText.setFillColor(i < 3 ? sf::Color::Yellow : sf::Color::White);
		
		sf::FloatRect entryBounds = entryText.getLocalBounds();
		entryText.setPosition(centerX - entryBounds.width / 2.f, 180.f + i * 40);
		window->draw(entryText);
	}
	
	sf::Text instructions;
	instructions.setFont(_font);
	instructions.setString("Press ESC to quit or SPACE to replay");
	instructions.setCharacterSize(20);
	instructions.setFillColor(sf::Color::Magenta);
	sf::FloatRect instrBounds = instructions.getLocalBounds();
	instructions.setPosition(centerX - instrBounds.width / 2.f, 550);
	window->draw(instructions);
}

void Leaderboard::renderNameEntry(sf::RenderWindow* window)
{
	sf::RectangleShape overlay(sf::Vector2f(window->getSize()));
	overlay.setFillColor(sf::Color(0, 0, 0, 200));
	window->draw(overlay);
	
	sf::Vector2u windowSize = window->getSize();
	float centerX = windowSize.x / 2.f;
	float centerY = windowSize.y / 2.f;
	
	sf::Text title;
	title.setFont(_font);
	title.setString("CONGRATS");
	title.setCharacterSize(50);
	title.setFillColor(sf::Color::Yellow);
	sf::FloatRect titleBounds = title.getLocalBounds();
	title.setPosition(centerX - titleBounds.width / 2.f, centerY - 150);
	window->draw(title);
	
	sf::Text prompt;
	prompt.setFont(_font);
	prompt.setString("Enter your name:");
	prompt.setCharacterSize(30);
	prompt.setFillColor(sf::Color::White);
	sf::FloatRect promptBounds = prompt.getLocalBounds();
	prompt.setPosition(centerX - promptBounds.width / 2.f, centerY - 50);
	window->draw(prompt);
	
	sf::RectangleShape inputBox(sf::Vector2f(400, 60));
	inputBox.setPosition(centerX - 200, centerY + 10);
	inputBox.setFillColor(sf::Color(40, 40, 40));
	inputBox.setOutlineColor(sf::Color::Cyan);
	inputBox.setOutlineThickness(3);
	window->draw(inputBox);
	
	_inputField.setPosition({centerX - 180, centerY + 25});
	_inputField.render(window);
	
	sf::Text instructions;
	instructions.setFont(_font);
	instructions.setString("Press ENTER to submit");
	instructions.setCharacterSize(20);
	instructions.setFillColor(sf::Color::Magenta);
	sf::FloatRect instrBounds = instructions.getLocalBounds();
	instructions.setPosition(centerX - instrBounds.width / 2.f, centerY + 100);
	window->draw(instructions);
}

std::optional<std::string> Leaderboard::getPlayerName() const
{
    return _playerName;
}
