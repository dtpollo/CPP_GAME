#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_X, float dir_Y, float movement_speed)
{
    this->shape.setTexture(*texture);

    this->shape.setPosition(pos_x,pos_y);
    this->direction.x = dir_X;
    this->direction.y = dir_Y;
    this->moveSpeed = movement_speed;

    //Resize the sprite 
    this->shape.scale(0.08f, 0.08f);
}

Bullet::~Bullet()
{

}

const sf::FloatRect Bullet::getBounds() const
{
    return this->shape.getGlobalBounds();
}

void Bullet::update()
{
    //Movement
    this->shape.move(this->moveSpeed * this->direction);

}

void Bullet::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}
