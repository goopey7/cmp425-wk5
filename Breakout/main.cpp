#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include <iostream>

int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 800), "Breakout");
	uint8_t currentLevel = 1;
    std::unique_ptr<GameManager> gameManager = std::make_unique<GameManager>(&window, currentLevel);
    gameManager->initialize();

    sf::Clock clock;
    float deltaTime;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        deltaTime = clock.restart().asSeconds();

        gameManager->update(deltaTime);

        window.clear();
        gameManager->render();
        window.display();

        if (gameManager->isLevelComplete() && sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        {
            gameManager = std::make_unique<GameManager>(&window, ++currentLevel);
            gameManager->initialize();
        }
		else if (gameManager->isGameOver() && sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        {
			currentLevel = 1;
            gameManager = std::make_unique<GameManager>(&window, currentLevel);
            gameManager->initialize();
        }
        else if (gameManager->isGameOver() && sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        {
            break;
        }
    }

    return 0;
}
