#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "UI.h"
#include "Leaderboard.h"



class GameManager {
public:
    GameManager(sf::RenderWindow* window, uint8_t levelIdx, Leaderboard& board, const sf::Font& font, uint32_t score, const std::chrono::high_resolution_clock::time_point& startTime);
    void initialize();
    void restart();
    void update(float dt);
    void loseLife();
    void render();
    void levelComplete();
    void powerupEffect(POWERUPS pu, float t);
    bool isGameOver() const;
    bool isLevelComplete() const;
    void incrementScore();
    std::optional<std::chrono::high_resolution_clock::time_point> getTime() const;
    uint32_t getScore() const;
	uint8_t getLevelNumber() const;
    LeaderboardEntry getBoardEntry() const;

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
    std::optional<std::chrono::high_resolution_clock::time_point> _endTime;
    const std::chrono::high_resolution_clock::time_point& _startTime;
    const sf::Font& _font;
    sf::Text _masterText;

    std::pair<POWERUPS, float> _powerupInEffect;
    Leaderboard& _board;
    float _pauseHold;
    float _time;
    float _timeLastPowerupSpawned;
    float _shakeTimeRemaining;
    float _shakeIntensity;
    sf::Vector2f _shakeOffset;
    uint32_t _score;
    int _lives;
    int _lastMouseX;
    uint8_t _levelIdx;
    bool _levelComplete;
    bool _pause;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn
};
