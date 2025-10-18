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
    GameManager(sf::RenderWindow* window);
    void initialize();
    void restart();
    void update(float dt);
    void loseLife();
    void render();
    void levelComplete();
    void powerupEffect(POWERUPS pu, float t);
    bool is_game_over() const;

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;


private:
    bool _pause;
    float _pauseHold;
    float _time;
    float _timeLastPowerupSpawned;
    int _lives;
    bool _levelComplete;
    std::pair<POWERUPS, float> _powerupInEffect;

    sf::Font _font;
    sf::Text _masterText;

    sf::RenderWindow* _window;
    std::unique_ptr<Paddle> _paddle;
    std::unique_ptr<Ball> _ball;
    std::unique_ptr<BrickManager> _brickManager;
    std::unique_ptr<PowerupManager> _powerupManager;
    std::unique_ptr<MessagingSystem> _messagingSystem;
    std::unique_ptr<UI> _ui;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn
};
