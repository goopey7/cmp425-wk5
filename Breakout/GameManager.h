#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "UI.h"



class GameManager {
public:
    GameManager(sf::RenderWindow* window, uint8_t levelIdx);
    void initialize();
    void restart();
    void update(float dt);
    void loseLife();
    void render();
    void levelComplete();
    void powerupEffect(POWERUPS pu, float t);
    bool isGameOver() const;
    bool isLevelComplete() const;
	uint8_t getLevelNumber() const;

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;


private:
    sf::RenderWindow* _window;
    std::unique_ptr<Paddle> _paddle;
    std::unique_ptr<Ball> _ball;
    std::unique_ptr<BrickManager> _brickManager;
    std::unique_ptr<PowerupManager> _powerupManager;
    std::unique_ptr<MessagingSystem> _messagingSystem;
    std::unique_ptr<UI> _ui;
    sf::Font _font;
    sf::Text _masterText;

    std::pair<POWERUPS, float> _powerupInEffect;
    float _pauseHold;
    float _time;
    float _timeLastPowerupSpawned;
    float _shakeTimeRemaining;
    float _shakeIntensity;
    sf::Vector2f _shakeOffset;
    int _lives;
    int _lastMouseX;
    uint8_t _levelIdx;
    bool _levelComplete;
    bool _pause;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn
};
