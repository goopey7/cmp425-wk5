#pragma once
#include <SFML/Graphics.hpp>


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);

private:
    sf::CircleShape _sprite;
    sf::RenderWindow* _window;
    GameManager* _gameManager;  // Reference to the GameManager
    sf::Vector2f _direction;
    float _velocity;
    float _timeWithPowerupEffect;
    bool _isAlive;
    bool _isFireBall;

    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

