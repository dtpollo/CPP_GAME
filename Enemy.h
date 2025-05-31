#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>


class Enemy{
private:
    sf::Sprite police;
    sf::Texture texture;
    float speed;
    int type;
    int hp;
    int hpMax;
    int damage;
    int points;

    //Private Functions SPRITE
    void initVariables();
    void initTexture();
    void initPolice();



public:
// Constructor/Destructor ======================================================>
    Enemy(float pos_x, float pos_y);
    virtual ~Enemy();

    //Accesors:
    const sf::FloatRect getBounds() const;
    const int& getDamage() const;

/*
============================================
--------------> Funciones <-----------------
============================================
*/


    void update();
    void render(sf::RenderTarget* target);

    
};

#endif