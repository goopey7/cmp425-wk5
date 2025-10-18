#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f),
    _shakeTimeRemaining(0.f),_shakeIntensity(0.f),_shakeOffset({0.f, 0.f}),
    _lastMouseX(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);
}

void GameManager::initialize()
{
    srand(time(0));
    _paddle = std::make_unique<Paddle>(_window);
    _brickManager = std::make_unique<BrickManager>(_window, this);
    _messagingSystem = std::make_unique<MessagingSystem>(_window);
    _ball = std::make_unique<Ball>(_window, 400.0f, this); 
    _powerupManager = std::make_unique<PowerupManager>(_window, _paddle.get(), _ball.get());
    _ui = std::make_unique<UI>(_window, _lives, this);

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    

    if (_lives <= 0)
    {
        _masterText.setString("Game over.\nPlay again? y/n");
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.\nPlay again? y/n");
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;

    if (_shakeTimeRemaining > 0.f)
    {
        _shakeTimeRemaining -= dt;
        float currentIntensity = _shakeIntensity * (_shakeTimeRemaining / SHAKE_DURATION_SECONDS);
        _shakeOffset.x = ((rand() % 200 - 100) / 100.f) * currentIntensity;
        _shakeOffset.y = ((rand() % 200 - 100) / 100.f) * currentIntensity;
    }
    else
    {
        _shakeOffset = { 0.f, 0.f };
    }

    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand() % POWERUP_SPAWN_CHANCE == 0)
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    if (sf::Mouse::getPosition(*_window).x != _lastMouseX)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
        _paddle->setPosition(mousePos.x);
        _lastMouseX = mousePos.x;
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);
    }

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    _shakeTimeRemaining = SHAKE_DURATION_SECONDS;
    _shakeIntensity = SHAKE_INTENSITY_NUM_PIXELS;
}

void GameManager::render()
{
    sf::View view = _window->getDefaultView();
    view.setCenter(view.getCenter() + _shakeOffset);
    _window->setView(view);

    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();

    _window->setView(_window->getDefaultView());
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

bool GameManager::is_game_over() const
{
    return _lives <= 0 || _levelComplete;
}

Paddle* GameManager::getPaddle() const { return _paddle.get(); }
BrickManager* GameManager::getBrickManager() const { return _brickManager.get(); }
