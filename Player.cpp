#include "Player.h"

void Player::initVariables()
{   
    this->moveSpeed = 7.5f;
    this->attackCooldownMax = 70.f;
    this->attackCooldown = this->attackCooldownMax;
    this->hpMax = 100;
    this->hp = this->hpMax;
}

void Player::initTexture()
{
    //Load a texture from file
    if(!this->texture.loadFromFile("/home/chickenux/Documents/JUEGO_2/Textures/finalAstronaut.png")){
        std::cout << "ERROR::PLAYER::INITEXTURE::Could not load texture file";
    }
}

void Player::initSprite()
{
    //Set testure to the sprite
    this->sprite.setTexture(this->texture);

    //Resize the sprite 
    //this->sprite.scale(0.16f, 0.16f);
    this->sprite.scale(0.11f, 0.11f);


}

Player::Player()
{
    this->initVariables();
    this->initTexture();
    this->initSprite();
}

Player::~Player(){

}

const sf::Vector2f &Player::getPos() const
{
    return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const int &Player::getHp() const
{
    return this->hp;
}

const int &Player::getHpMax() const
{
    return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x,y);
}

void Player::setHp(const int hp)
{
    this->hp = hp;
}

void Player::loseHp(const int value)
{
    this->hp -= value;
    if(this->hp < 0)
        this->hp = 0;
}

/*
============================================
--------------> Funciones <-----------------
============================================
*/

void Player::move(const float driX, const float driY)
{
    this->sprite.move(this->moveSpeed * driX, this->moveSpeed * driY);
}

const bool Player::Attackflag()
{
    if(this->attackCooldown >= this->attackCooldownMax){
        this->attackCooldown = 0.5f;
        return true;
    }
    return false;
}

void Player::updateAttack()
{
    if(this->attackCooldown < this->attackCooldownMax)
    this->attackCooldown += 1.f;
}

void Player::update()
{
    this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}