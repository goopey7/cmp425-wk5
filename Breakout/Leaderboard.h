#pragma once
#include <cstdint>
#include <array>
#include <optional>
#include <chrono>
#include <string>
#include "TextInput.h"
#include "CONSTANTS.h"

namespace sf
{
	class RenderWindow;
	class Event;
}

struct LeaderboardEntry
{
	std::chrono::high_resolution_clock::time_point timestamp;
	std::optional<std::string> name;
	uint32_t score;
	float time;
	uint8_t levelReached;

	auto operator<=>(const LeaderboardEntry& other) const
	{
		if (auto cmp = other.levelReached <=> levelReached; cmp != 0)
		{
			return cmp;
		}
		if (auto cmp = other.score <=> score; cmp != 0)
		{
			return cmp;
		}
		return other.timestamp <=> timestamp;
	}
};

class Leaderboard
{
public:
	Leaderboard(const sf::Font& font);
	bool isEntryWorthy(LeaderboardEntry entry) const;
	void addEntry(LeaderboardEntry entry);
	bool handleEvent(const sf::Event& event);
	void render(sf::RenderWindow* window);
	void renderNameEntry(sf::RenderWindow* window);
	std::optional<std::string> getPlayerName() const;
private:
	std::array<std::optional<LeaderboardEntry>, LEADERBOARD_ENTRIES> _entries;
	std::optional<std::string> _playerName;
	const sf::Font& _font;
	TextInput _inputField;
};
