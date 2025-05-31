#pragma once  // Avoid to include the same file multiple times

#include <map>
#include <string>
#include <sstream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game{
    private:
        /*
        Here we define window as the main windows where si draww all,
        and videoMode to put the resolution
        */
        sf::RenderWindow* window;
        sf::VideoMode videoMode;

        /*
        Here we define a map to store textures, where each texture is saved in memory 
        and can be accessed using a string key. This allows us to reuse the same 
        texture without reloading it from disk every time.
        */
        std::map<std::string, sf::Texture*> textures;
        
        /*
        Define a vector to store pointers to Bullet objects,
        which allows us to dynamically manage all active bullets in the game.
        */
        std::vector<Bullet*> bullets;

        /*
        Define the elements to be displayed on the screen,
        such as the font, the points text, and the Game Over message.
        */
        sf::Font font;
        sf::Text pointText;
        sf::Text gameOver;

        /*
        The Texture object is used to load the image into memory,
        and the Sprite object is used to draw the loaded image on the screen.
        */
        sf::Texture spaceBackgroundTex;
        sf::Sprite spaceBackground;

        //Point counter
        unsigned points;

        /*
        Define the player object as a pointer to access
        its functions and properties dynamically.
        */
        Player* player;

        /*
        Define two rectangles: one for the background of the health bar,
        and another for the player's current health.
        */
        sf::RectangleShape PlayerHpBar;
        sf::RectangleShape PlayerHpBarBack;

        /*
        Define a timer for spawning enemies,
        and a vector to store the memory addresses of all active enemies.
        */
        float spawnTimer;
        float spawnTimerMax;
        std::vector<Enemy*> enemies;

        //Bullet_sound
        sf::SoundBuffer buffer;
        sf::Sound sound;

        //GameOver_sound
        sf::SoundBuffer buffer2;
        sf::Sound gameOverSound;

        //Music Background
        sf::Music music;

        /*
        All these methods are used to initialize variables and components,
        ensuring that nothing is left uninitialized or in an invalid state.
        */
        void initWindow();

        void initBulletSound();
        void initMusic();
        void initGameOverSound();

        void initTextures();
        void initGUI();
        void initWorld();
        void initSystem();

        void initPlayer();
        void initEnemies();



    public:
        // Constructor and Destructor of the Game class
        Game();
        virtual ~Game();

        /*
        Calls the main game loop functions:
            -> update: updates the game state and values
            -> render: draws the updated values to the screen
        */
        void run();

        void updatePollEvents();    // Capture window events (close)
        void updateInput();         // Capture pressed keys
        void updateGUI();           // Update the life bar and score display
        void updateCollision();     // Handle collisions
        void updateBullets();       // Move bullets and check their state
        void updateEnemies();       // Move and spawn enemies
        void updateCombat();        // Handle combat logic
        void update();              // MAIN FUNCTION: calls all update functions

        void renderGUI();           // Draw the game interface (life bar, points)
        void renderBackground();    // Draw the background
        void render();              // MAIN FUNCTION: draws all game elements

};