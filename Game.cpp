#include "Game.h"
//Private

/*
This function sets up the main window, including dimensions, style,
frame rate limit, and vertical sync.
Limiting the frame rate to 144 FPS helps reduce CPU overhead
and ensures the game runs at a consistent speed.
Vertical sync is disabled to use the defined FPS limit.
*/
void Game::initWindow(){
    this->videoMode.height = 1000; 
    this->videoMode.width = 1200;
    this->window = new sf::RenderWindow(this->videoMode, "Puff Puff Planet", sf::Style::Default | sf::Style::Close);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}


// Load the bullet sound effect and set the volume to 100
void Game::initBulletSound(){
    if(!this->buffer.loadFromFile("Sounds/PIZZA_bullet.wav")){
        std::cout << "Error to load sound - bullet" << std::endl;
    }

    this->sound.setBuffer(buffer);
    this->sound.setVolume(100.f);
}


// Load the main music theme, set the volume to 60,
// enable looping when the music ends, and start when the game begins
void Game::initMusic() {
    if (!this->music.openFromFile("Sounds/main_Theme.ogg")) {
        std::cout << "Error loading music" << std::endl;
    }

    this->music.setLoop(true);
    this->music.setVolume(60.f);
    this->music.play();
}


// Load the gameover music theme, set the volume to 100
void Game::initGameOverSound(){
    if(!this->buffer2.loadFromFile("Sounds/GameOver_sound.wav")){
        std::cout << "Error to load sounds - GameOver" << std::endl;
    }

    this->gameOverSound.setBuffer(buffer2);
    this->gameOverSound.setVolume(100.f);
}


/*
This function loads an image into memory and stores it in the map
with the key "BULLET". Remember that we're using a map to associate
string keys with texture pointers for efficient reuse.
*/
void Game::initTextures(){
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("Textures/finalPIZZA.png");
}


/*
This function initializes the GUI elements such as text, fonts, 
health bars, and assigns properties to each one.
*/
void Game::initGUI(){
    // Load font
    if(!this->font.loadFromFile("Fonts/PixelDigivolve-mOm9.ttf")){
        std::cout << "Error to load fonts" << std::endl;
    }

    // Set the loaded font and configure the score text: size and color
    // We don't set the actual score string here, because it will be updated
    // dynamically during the game in the updateGUI() function
    this->pointText.setFont(this->font);
    this->pointText.setCharacterSize(30); 
    this->pointText.setFillColor(sf::Color::White);

    // Configure the "Game Over" text: font, size, color, and position
    this->gameOver.setFont(this->font);
    this->gameOver.setCharacterSize(80);
    this->gameOver.setFillColor(sf::Color::White);
    this->gameOver.setString("Game Over bro !");
    this->gameOver.setPosition(this->window->getSize().x / 2.f - this->gameOver.getGlobalBounds().width / 2.f, 
                               this->window->getSize().y / 2.f - this->gameOver.getGlobalBounds().height / 2.f);

    // Configure the background of the health bar: size, color, and position
    this->PlayerHpBarBack.setSize(sf::Vector2f(25.f, 300.f));
    this->PlayerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
    this->PlayerHpBarBack.setPosition(sf::Vector2f(2.f, this->window->getSize().y - 310.f));

    // Configure the frontground of the health bar: size, color, and position
    this->PlayerHpBar.setSize(this->PlayerHpBarBack.getSize());
    this->PlayerHpBar.setFillColor(sf::Color::Red);
    this->PlayerHpBar.setPosition(this->PlayerHpBarBack.getPosition()); 
}


// Load the background image and set it as the texture to be used in the game
void Game::initWorld(){
    if(!this->spaceBackgroundTex.loadFromFile("Textures/FINAL_SPACE.png")){
        std::cout << "Error to load the Backgrpound" << "\n";
    }
    this->spaceBackground.setTexture(this->spaceBackgroundTex);
}


// Initialize the points counter to 0
void Game::initSystem(){
    this->points = 0;
}


// Here we create a new object of the Player class.
// It will be the main player with the functionalities defined in the Player class.
void Game::initPlayer() {
    this->player = new Player();
}


// Define the time to wait before spawning a new enemy.
// This value can be modified in the future to increase the game difficulty.
void Game::initEnemies(){
    this->spawnTimerMax = 50.f;
    this->spawnTimer = this->spawnTimerMax;
}


/*
Defines the constructor of the Game class. In other words,
it calls all the initialization functions to build and prepare
the game before it runs.
*/
Game::Game(){
    this->initWindow();
    this->initBulletSound();
    this->initGameOverSound();
    this->initMusic();
    this->initTextures();
    this->initGUI();
    this->initWorld();
    this->initSystem();
    this->initPlayer();
    this->initEnemies();
}


/*
This is the destructor of the Game class. It is called automatically
when the game ends, and is responsible for freeing all dynamically allocated memory.
*/
Game::~Game(){
    // Delete objects created with new, such as the window and player
    delete this->window;
    delete this->player;

    // Loop through the texture map and delete each loaded texture
    for (auto &i : this->textures){
        delete i.second;
    }
    this->textures.clear();

    // Loop through the bullets vector and delete each bullet object
    for (auto *i : this->bullets){
        delete i;
    }

    // Loop through the enemies vector and delete each enemy object
    for (auto *i : this->enemies){
        delete i;
    }
}

/*
========================================
---------> Public Functions <-----------
========================================
*/

/*
This is the main function — the game loop.
The game runs as long as the window is open. On each iteration:
- It calls updatePollEvents(), which captures keyboard inputs and window close events.
- Then, it checks if the player still has health.
    If true, it updates the entire game logic.
    If false, it skips updates and only renders the final state.
This allows you to see the "Game Over" screen and hear the ending music,
without continuing the game logic.
*/
void Game::run(){
    while (this->window->isOpen()){
        this->updatePollEvents();

        if(this->player->getHp() > 0){
            this->update();
        }

        this->render();
    }
}


// This function defines an event object to check if a system-level event occurred,
// such as pressing a key to close the game or clicking the close window button.
void Game::updatePollEvents() {
    sf::Event ev;
    while (this->window->pollEvent(ev)) {
        switch (ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

/*
This function defines the player controls used in the game.
It handles real-time input for movement (WASD or arrow keys)
and shooting (spacebar).
*/
void Game::updateInput(){
    // Move player
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->player->move(-1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->player->move(1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->player->move(0.f, -1.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->player->move(0.f, 1.f);

    // Shoot bullet
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && this->player->Attackflag()){
        this->bullets.push_back(new Bullet(this->textures["BULLET"], 
        this->player->getPos().x + this->player->getBounds().width/2.f - this->player->getBounds().width/4.f, 
        this->player->getPos().y, 0.f, -1.f, 4.0f));
        this->sound.play();
    }

    /*
    We should implement a way to stop the music and restart
    game functionality associated with a press key
    */
}


/*
This function updates the score text and adjusts the health bar
according to the player's current health.
*/
void Game::updateGUI(){
    // Points
    std::stringstream ss;
    ss << "Points: " << this->points;
    this->pointText.setString(ss.str());

    // Use static_cast<float> to ensure floating-point division
    float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();


    // Update the size of the health bar based on health percentage
    this->PlayerHpBar.setSize(sf::Vector2f(this->PlayerHpBar.getSize().x, 300.f * hpPercent));

    // Update the position bar
    this->PlayerHpBar.setPosition(
        this->PlayerHpBar.getPosition().x,
        this->PlayerHpBarBack.getPosition().y + (300.f * (1.f - hpPercent))
    );
}



/*
This function helps tp  update the collision of the player with the world boundaries.
It checks if the player is outside the boundaries of the window and adjusts its position accordingly.
*/
void Game::updateCollision()
{
    // Left
    if(this->player->getBounds().left < 0.f){
        this->player->setPosition(0.f, this->player->getBounds().top);
    }

    // Right
    else if(this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x){
        this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
    }

    // Top
    if(this->player->getBounds().top < 0.f){
        this->player->setPosition(this->player->getBounds().left, 0.f);
    }

    // Bottom
    else if(this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y){
        this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
    }
}


/*
This function updates each bullet's state. If a bullet goes outside of screen,
it is deleted from memory and removed from the bullets vector. 
A manual counter is used to keep track of the bullet's position in the vector 
so it can be safely deleted.
*/
void Game::updateBullets(){
    unsigned counter = 0;
    for (auto *bullet : this->bullets){
        bullet->update();
        
        // Just TOP
        if(bullet->getBounds().top + bullet->getBounds().height < 0.f){
            delete this->bullets.at(counter);
            this->bullets.erase(this->bullets.begin() + counter);
        }
        
        ++counter; // For manage the position of the bullet in the vector
    }
}


/*
This function handles the spawning and movement of enemies.
Increases a spawn timer each frame, and when the timer reaches a set value, a new enemy is spawned.
Updates all existing enemies, removes those that go off-screen, 
and handles collisions with the player.
*/
void Game::updateEnemies(){
    // Enemy spawn timer
    this->spawnTimer += 0.5f;
    if(this->spawnTimer >= this->spawnTimerMax){

        // Create a temporary enemy to get its width
        Enemy tempEnemy(0.f, 0.f);
        float enemyWidth = tempEnemy.getBounds().width;

        // Generate a valid X position so the enemy doesn't spawn off-screen
        float maxX = static_cast<float>(this->window->getSize().x) - enemyWidth;
        float posX = static_cast<float>(rand() % static_cast<int>(maxX));

        // Create and add the enemy just above the visible screen
        this->enemies.push_back(new Enemy(posX, -tempEnemy.getBounds().height));

        // Reset the spawn timer
        this->spawnTimer = 0.f;
    }

    // Update all enemies
    unsigned counter = 0;
    for (auto *enemy : this->enemies){
        enemy->update();
        
        // If the enemy has moved off the bottom of the screen
        if(enemy->getBounds().top > this->window->getSize().y){
            // Penalize the player for missing the enemy
            this->player->loseHp(this->enemies.at(counter)->getDamage());

            // Delete and remove the enemy
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
        }
        // If the enemy collides with the player
        else if(enemy->getBounds().intersects(player->getBounds()))
        {
            // Apply damage to the player
            this->player->loseHp(this->enemies.at(counter)->getDamage());

            // Delete and remove the enemy
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
        }
        ++counter;
    }
}

// =====================> Here end the main loop of game



/*
This function handles the combat logic between bullets and enemies.
It checks for collisions between each enemy and all bullets.
If a collision is detected, the enemy and bullet are deleted, the score increases,
and the enemy is removed from the game.
*/
void Game::updateCombat(){
    for (int i = 0; i < this->enemies.size(); ++i){
        bool enemy_deleted = false;

        // Loop through all bullets unless the enemy has already been deleted
        for(size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++){

            // Check if enemy and bullet intersect (collision detected)
            if(this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds())){

                // Increase score
                this->points += 1;

                // Delete enemy and remove it from the vector
                delete this->enemies[i];
                this->enemies.erase(this->enemies.begin() + i);

                // Delete bullet and remove it from the vector
                delete this->bullets[k];
                this->bullets.erase(this->bullets.begin() + k);

                // Flag that the enemy was deleted to avoid invalid access
                enemy_deleted = true;
            }
        }
    }    
}


/*
This is the main update function for the game logic.
It is called every frame and updates all key components of the game.
*/
void Game::update()
{
    // Movement, Shooting
    this->updateInput();

    // Attack cooldowns, animations
    this->player->update();

    // Player screen boundaries
    this->updateCollision();

    // Movement and out-of-screen cleanup
    this->updateBullets();

    // Enemy spawning, movement, and removal
    this->updateEnemies();

    // Bullet-enemy collisions and score
    this->updateCombat();

    // Update GUI elements
    this->updateGUI();

    // Game Over condition
    if(this->player->getHp() <= 0){
        // Stop background music if it's still playing
        if (this->music.getStatus() == sf::Music::Playing) {
            this->music.stop();
        }

        // Play the Game Over sound
        this->gameOverSound.play();
    }
}


/*
This function renders GUI elements
into the game window like:
- Score text
- Background of the health bar
- Current health bar of the player
*/
void Game::renderGUI()
{
    this->window->draw(this->pointText); 
    this->window->draw(this->PlayerHpBarBack);  
    this->window->draw(this->PlayerHpBar);    
}

// This function renders the space background
void Game::renderBackground()
{
    this->window->draw(this->spaceBackground);
}


/*
This function is responsible for rendering all visual elements of the game
in the screen in the correct order.
*/
void Game::render()
{
    // Clear the screen before drawing the next frame
    this->window->clear();

    // Draw the background (space image)
    this->renderBackground();

    /*
    Draw all main game objects in the correct rendering order:
    1. Player
    2. Bullets
    3. Enemies
    4. GUI
    */

    // Draw the player sprite
    this->player->render(*this->window);

    // Draw all bullets
    for (auto *bullet : this->bullets){
        bullet->render(this->window);
    }

    // Draw all enemies
    for (auto *enemy : this->enemies){
        enemy->render(this->window);
    }

    // Draw GUI elements (score, health bar)
    this->renderGUI();

    // If the player is dead, draw the Game Over text
    if(this->player->getHp() <= 0)
        this->window->draw(this->gameOver);

    // Display the frame (swap the buffer to show all drawings)
    this->window->display();
}