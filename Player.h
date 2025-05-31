#pragma once
#include "Bullet.h"

class Player{
private:

    sf::Sprite sprite;
    sf::Texture texture;
    float moveSpeed;
    float attackCooldown;
    float attackCooldownMax;
    int hp;
    int hpMax;

    //Private Functions SPRITE
    void initVariables();
    void initTexture();
    void initSprite();

public:
// Constructor/Destructor ====================================================>
    Player();
    virtual ~Player();

//Acessor
const sf::Vector2f& getPos() const;
const sf::FloatRect getBounds() const;
const int& getHp() const;
const int& getHpMax() const;

//Modifiers
void setPosition(const sf::Vector2f pos);
void setPosition(const float x, const float y);
void setHp(const int hp);
void loseHp(const int value);

/*
============================================
--------------> Funciones <-----------------
============================================
*/
    void move(const float driX, const float driY);
    const bool Attackflag();

    void updateAttack();
    void update();
    void render(sf::RenderTarget& target);

};