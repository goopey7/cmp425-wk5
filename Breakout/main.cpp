#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include <iostream>
#include "Leaderboard.h"

int main()
{
    sf::Font font;
    font.loadFromFile("font/montS.ttf");
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Breakout");
	uint8_t currentLevel = 1;
    Leaderboard board(font);
    auto startTime = std::chrono::high_resolution_clock::now();
    std::unique_ptr<GameManager> gameManager = std::make_unique<GameManager>(&window, currentLevel, board, font, 0, startTime);
    gameManager->initialize();

    sf::Clock clock;
    float deltaTime;
    bool nameAddedToLeaderboard = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
			if (gameManager->isGameOver())
			{
				board.handleEvent(event);
			}
        }

        deltaTime = clock.restart().asSeconds();

        gameManager->update(deltaTime);

        window.clear();
        gameManager->render();
        if (gameManager->isGameOver())
        {
			board.render(&window);
            if (!nameAddedToLeaderboard)
            {
                LeaderboardEntry entry = gameManager->getBoardEntry();
                if (board.isEntryWorthy(entry) && !board.getPlayerName().has_value())
                {
                    board.renderNameEntry(&window);
                }
                else if (board.isEntryWorthy(entry) && !nameAddedToLeaderboard)
                {
                    entry.name = board.getPlayerName().value();
                    board.addEntry(entry);
                    nameAddedToLeaderboard = true;
                }
            }
        }
        window.display();

        if (gameManager->isLevelComplete() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            uint32_t score = gameManager->getScore();
            gameManager = std::make_unique<GameManager>(&window, ++currentLevel, board, font, score, startTime);
            gameManager->initialize();
        }
		else if (gameManager->isGameOver() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
			currentLevel = 1;
            startTime = std::chrono::high_resolution_clock::now();
            gameManager = std::make_unique<GameManager>(&window, currentLevel, board, font, 0, startTime);
            gameManager->initialize();
            nameAddedToLeaderboard = false;
        }
        else if (gameManager->isGameOver() && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            break;
        }
    }

    return 0;
}
