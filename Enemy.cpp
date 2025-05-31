#include "Enemy.h"
#include <iostream>

void Enemy::initVariables()
{
    this->type = 0;
    this->speed = 1.5f;
    this->hpMax = 10;
    this->hp = 0;
    this->damage = 20;
    this->points = 5;
}

void Enemy::initTexture()
{
    //Load a texture from file
    if(!this->texture.loadFromFile("/home/chickenux/Documents/JUEGO_2/Textures/finalPOLICE.png")){
        std::cout << "ERROR::PLAYER::INITEXTURE::Could not load texture file";
    }
}

void Enemy::initPolice()
{
    //Set testure to the sprite
    this->police.setTexture(this->texture);

    //this->police.setPointCount(rand() % 20 + 3);

    //Resize the sprite 
    //this->police.scale(0.15f, 0.15f);
    this->police.scale(0.12f, 0.12f);
}

//Enemy::Enemy(float pos_x, float pos_y)
Enemy::Enemy(float pos_x, float pos_y)
{
    this->initVariables();
    this->initTexture();
    this->initPolice();
    this->police.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

const sf::FloatRect Enemy::getBounds() const{

    return this->police.getGlobalBounds();

}

const int &Enemy::getDamage() const
{
    return this->damage;
}

void Enemy::update()
{
    this->police.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
    target->draw(this->police);
}
