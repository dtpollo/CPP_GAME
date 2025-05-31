#pragma once
#ifndef BULLET_H
#define BULLET_H

// Incluye las librerías necesarias
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Bullet{
private:

    sf::Sprite shape;

    sf::Vector2f direction;
    float moveSpeed;

public:
    Bullet();
    Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_X, float dir_Y, float movement_speed);
    virtual ~Bullet();

    //Accessor
    const sf::FloatRect getBounds() const;

    void update();
    void render(sf::RenderTarget* target);

};
#endif 