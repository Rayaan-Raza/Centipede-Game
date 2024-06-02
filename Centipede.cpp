#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;

/* 
Rayaan Raza - 23I0535


Promts used 
    -How to add custom font
    -How to calculate grid position of bullet
    -How to move an object using SF clock
    -How to create a message on the screen and take user input
    -How to add different Textures for different states*/



// Initializing Dimensions.

// resolutionX and resolutionY determine the rendering resolution.

// Don't edit unless required. Use functions on lines 43, 44, 45 for resizing the game window.

const int resolutionX = 960;

const int resolutionY = 960;

const int boxPixelsX = 32;

const int boxPixelsY = 32;

const int gameRows = resolutionX / boxPixelsX; // Total rows on grid

const int gameColumns = resolutionY / boxPixelsY; // Total columns on grid



// Initializing GameGrid.

int gameGrid[gameRows][gameColumns] = {};



// The following exist purely for readability.

const int x = 0;

const int y = 1;

const int exists = 2;



/////////////////////////////////////////////////////////////////////////////

//                                                                         //

// Write your functions declarations here. Some have been written for you. //

//                                                                         //

/////////////////////////////////////////////////////////////////////////////



void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite, sf::Event& event, float bullet[3], int& maxbullet,sf::Clock& bulletClock);

void moveBullet(float bullet[], sf::Clock& bulletClock, float player[]);

void drawBullet(sf::RenderWindow& window, float bullet[], sf::Sprite& bulletSprite);

void initializeCentipede(int centipede[][4], int&centipedeLength, int& direction);

void drawCentipede(sf::RenderWindow& window, int centipede[][4], sf::Sprite& centipedeSprite, int& centipedeLength,sf::Texture& headTexture,sf::Texture& centipedeTexture, int& direction,int& hitIndex);

void moveCentipede(int centipede[][4], int& centipedeLength, int& direction, sf::Clock& centipedeClock, int mushrooms[][4], int& maxMushrooms,float& fact,int& collisionCount);

void splitCentipede(sf::Texture& headTexture, int& centipedeLength, int centipede[][4], float bullet[], int& direction, int& score, sf::Sprite& centipedeSprite,int& hitIndex);

void drawMushrooms(sf::RenderWindow& window, int mushrooms[][4], const int maxMushrooms, sf::Texture mushroomTextures[], sf::Sprite& mushroomSprite, float bullet[3], int & score);

void initializeMushroom(int index, int mushrooms[][4], int gameGrid[][gameColumns], int & health, int & maxMushrooms);

void checkBulletMushroomCollision(float bullet[3], int& maxbullet, int mushrooms[][4], int& maxMushrooms, int poisonMushrooms[][4], int& maxPoisonMushrooms, int gameGrid[][gameColumns], int& score);

bool allSegmentsDestroyed(int centipede[][4], int& centipedeLength, int small[][4]);

void initializePoisonMushrooms(int poisonMushrooms[][4], const int maxPoisonMushrooms,int& health);

void createPoisonMushroom(int poisonMushrooms[][4], int centipede[][4], float bullet[], const int maxPoisonMushrooms,int& centipedeLength);

void drawPoisonMushrooms(sf::RenderWindow& window, int poisonMushrooms[][4], int& maxPoisonMushrooms, sf::Texture poisonMushroomTextures[], sf::Sprite& poisonMushroomSprite);

void checkPlayerCollision(float player[],int centipede[][4], int& centipedeLength, int& lives,int poisonMushrooms[][4],int& maxPoisonMushrooms, sf::RenderWindow& window,sf::Font& font,int small[][4]);

void drawSmall(sf::RenderWindow& window, int small[][4], sf::Sprite& smallSprite, sf::Texture& smallTexture, int&smalldir);

void moveSmall(int small[][4], sf::Clock& smallClock, int& smalldir, int mushrooms[][4], int& maxMushrooms,int poisonMushrooms[][4], int& maxPoisonMushrooms);

void initializesmall(int small[2][4],int& smalldir);

bool isCentipedeInBottomRows(int centipede[][4], int& centipedeLength);

void checkBulletSmallCollision(float bullet[], int& maxBullet, int small[][4],int& score);







int main()

{

	srand(time(0));



	// Declaring RenderWindow.

	sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Centipede", sf::Style::Close | sf::Style::Titlebar);



	// Used to resize your window if it's too big or too small. Use according to your needs.

	window.setSize(sf::Vector2u(640, 640)); // Recommended for 1366x768 (768p) displays.

	// window.setSize(sf::Vector2u(1280, 1280)); // Recommended for 2560x1440 (1440p) displays.

	// window.setSize(sf::Vector2u(1920, 1920)); // Recommended for 3840x2160 (4k) displays.

	

	// Used to position your window on every launch. Use according to your needs.

	window.setPosition(sf::Vector2i(100, 0));



	// Initializing Background Music.

	sf::Music bgMusic;

	bgMusic.openFromFile("Music/music.ogg");

	bgMusic.play();

	bgMusic.setVolume(50);



	// Initializing Background.

	sf::Texture backgroundTexture;

	sf::Sprite backgroundSprite;

	backgroundTexture.loadFromFile("Textures/bg1.jpg");

	backgroundSprite.setTexture(backgroundTexture);

	backgroundSprite.setColor(sf::Color(255, 255, 255, 255 * 0.20)); // Reduces Opacity to 25%



	// Initializing Player and Player Sprites.

	float player[2] = {};

	player[x] = (gameColumns / 2) * boxPixelsX;

	player[y] = (gameColumns * 1) * boxPixelsY;

	sf::Texture playerTexture;

	sf::Sprite playerSprite;

	playerTexture.loadFromFile("Textures/player.png");

	playerSprite.setTexture(playerTexture);

	playerSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));



	// Initializing Bullet and Bullet Sprites.

	float bullet[3] = {};

	bullet[x] = player[x];

	bullet[y] = player[y] - boxPixelsY;

	bullet[exists] = false;

	sf::Clock bulletClock;

	sf::Texture bulletTexture;

	sf::Sprite bulletSprite;

	bulletTexture.loadFromFile("Textures/bullet.png");

	bulletSprite.setTexture(bulletTexture);

	bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	// Initializing Mushrrom and Mushroom Sprites.

sf::Texture mushroomTextures[4]; // 4 different textures
sf::Sprite mushroomSprite;
int health = 3; 
int maxMushrooms = rand() % 11 + 20; // Generates a random value between 20 and 30
int mushrooms[maxMushrooms][4] = {}; 
mushroomTextures[0].loadFromFile("Textures/mushroom1.png");
mushroomTextures[1].loadFromFile("Textures/mushroom2.png");
mushroomTextures[2].loadFromFile("Textures/mushroom3.png");
mushroomTextures[3].loadFromFile("Textures/mushroom4.png");

    for (int i = 0; i < maxMushrooms; ++i) 
{
        initializeMushroom(i, mushrooms, gameGrid, health, maxMushrooms);
}

	// Initializing poison mushrooms and poison mushroom Sprites.

 int maxPoisonMushrooms = 20; // Adjust the maximum number as needed
int poisonMushrooms[maxPoisonMushrooms][4] = {}; // 4 values for X, Y, existence flag, and health
sf::Texture poisonMushroomTextures[2]; // 2 different textures
sf::Sprite poisonMushroomSprite;
poisonMushroomTextures[0].loadFromFile("Textures/poison1.png");
poisonMushroomTextures[1].loadFromFile("Textures/poison2.png");

         initializePoisonMushrooms( poisonMushrooms,maxPoisonMushrooms,health); 



 int centipedeLength = 12;
 int x = 0;
 int y = 1;
 int exists = 2;
 int direction = 3;

 int maxbullet = 2;
int hitIndex=-1;
int eat=0;
bool splt=false;


	// Initializing Centipede and Centipede Sprites.

int centipede[centipedeLength][4] = {}; // Declare centipede array
sf::Texture centipedeTexture;
sf::Texture headTexture; // New texture for the head
 sf::Sprite centipedeSprite;
 sf::Clock centipedeClock;

  initializeCentipede( centipede,centipedeLength,direction); 

    centipedeTexture.loadFromFile("Textures/walkL8.png");
    headTexture.loadFromFile("Textures/headL3.png"); 
    centipedeSprite.setTexture(centipedeTexture);
    centipedeSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));


	// Initializing one segment Head and one segment Head Sprites.

int smallLength=2;
int small[smallLength][4] = {}; // one segment Head centipede array
sf::Texture smallTexture; // texture for one segment Head
 sf::Sprite smallSprite;
 sf::Clock smallClock;
 int smalldir=3;//direction
initializesmall(small,smalldir); 
smallTexture.loadFromFile("Textures/headL4.png");
smallSprite.setTexture(smallTexture);
smallSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));


//Font used in Game
sf::Font font;
if (!font.loadFromFile("ARCADECLASSIC.TTF")) 
{
    std::cerr << "Failed to load font!" << std::endl;
    return 1;  
}

//To display score
sf::Text scoreText;
scoreText.setFont(font);
scoreText.setCharacterSize(24);
scoreText.setPosition(resolutionX - 150, resolutionY - 30);

//To display level counter
sf::Text levelText;
levelText.setFont(font);
levelText.setCharacterSize(24);
levelText.setPosition(5, resolutionY - 30);

//To display Lives counter
sf::Text LivesText;
LivesText.setFont(font);
LivesText.setCharacterSize(24);
LivesText.setPosition(resolutionX/2 -20, resolutionY - 30);

int Lives = 3;

float fact = 1;

int level = 1;

int score = 0;

int collisionCount=0;




//Displaying Welcome text
    sf::Text welcomeText;
    welcomeText.setFont(font);
    welcomeText.setCharacterSize(30);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setStyle(sf::Text::Bold);
    welcomeText.setString("Welcome to Centipede\n \n      Press S to start");

    welcomeText.setPosition(resolutionX / 2 - 150, resolutionY / 2 - 25);

    window.draw(welcomeText);
     window.display();

    bool keyPressed = false;

    // Wait for key press
while (window.isOpen() && !keyPressed)
{
    // Handle events
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed)
        {
            // Check if the pressed key is 'S' or 's'
            if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::S)
                keyPressed = true;
        }
    }
}

//Start of Game and calling of functions
	while(window.isOpen()) 
    {
		window.draw(backgroundSprite);
        

		sf::Event e;

		while (window.pollEvent(e)) 
        {

			if (e.type == sf::Event::Closed)
             {

				return 0;
			}
             drawPlayer( window,player,playerSprite,e,bullet,maxbullet,bulletClock);

		}	


        drawPoisonMushrooms(window, poisonMushrooms, maxPoisonMushrooms, poisonMushroomTextures, poisonMushroomSprite);
            
        createPoisonMushroom(poisonMushrooms, centipede, bullet, maxPoisonMushrooms, centipedeLength);

        drawMushrooms(window, mushrooms, maxMushrooms, mushroomTextures, mushroomSprite, bullet, score);

        drawPlayer( window,player,playerSprite,e,bullet,maxbullet,bulletClock);


        checkBulletMushroomCollision(bullet,maxbullet,mushrooms, maxMushrooms,poisonMushrooms, maxPoisonMushrooms,gameGrid,score); 


        if(bullet[exists])
         {
            

			moveBullet(bullet, bulletClock,player);

			drawBullet(window, bullet, bulletSprite);

		}
        




        moveCentipede(centipede,centipedeLength,direction,centipedeClock,mushrooms,maxMushrooms, fact, collisionCount);
        drawCentipede(window, centipede, centipedeSprite,centipedeLength,headTexture,centipedeTexture,direction,hitIndex);
        splitCentipede( headTexture,centipedeLength, centipede,bullet,direction,score,centipedeSprite,hitIndex);
        createPoisonMushroom(poisonMushrooms, centipede, bullet, maxPoisonMushrooms, centipedeLength);



        checkPlayerCollision(player,centipede,centipedeLength,Lives,poisonMushrooms,maxPoisonMushrooms,window,font,small);
        isCentipedeInBottomRows(centipede,centipedeLength);

         cout<<collisionCount<<endl;

        bool centipedeInBottomRows = isCentipedeInBottomRows(centipede, centipedeLength);



if(centipedeInBottomRows)
{

         moveSmall(small, smallClock, smalldir,mushrooms,maxMushrooms,poisonMushrooms,maxPoisonMushrooms);
        drawSmall(window, small, smallSprite, smallTexture, smalldir);
        checkBulletSmallCollision(bullet, maxbullet, small,score);
 }
       




scoreText.setString("Score " + std::to_string(score));
window.draw(scoreText);


LivesText.setString("Lives " + std::to_string(Lives));
window.draw(LivesText);

levelText.setString("Level " + std::to_string(level));
window.draw(levelText);
window.draw(scoreText);

 if (allSegmentsDestroyed(centipede, centipedeLength,small)) 
 {
            // if all centipede segments are destroyed then start a new level
            ++level;
            fact*=1.5;
            centipedeLength =12;

                
    // Display "New level, press S to start" message
    sf::Text newLevelText;
    newLevelText.setFont(font);
    newLevelText.setCharacterSize(30);
    newLevelText.setFillColor(sf::Color::White);
    newLevelText.setStyle(sf::Text::Bold);
    newLevelText.setString("Level " + std::to_string(level) + "\n\npress S to start");
    newLevelText.setPosition(resolutionX / 2 - 200, resolutionY / 2 - 25);

    window.clear();
    window.draw(newLevelText);
    window.display();

    // Wait for 'S' key press to start the new level
    bool sPressed = false;
    while (!sPressed && window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                // Check if the pressed key is 'S' or 's'
                if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::S)
                    sPressed = true;
            }
        }
    }
                for (int i = 0; i < maxMushrooms; ++i) 
{
        initializeMushroom(i, mushrooms, gameGrid, health, maxMushrooms);

  
  }

    initializesmall(small,smalldir); 

  if(centipedeInBottomRows)
{
         moveSmall(small, smallClock, smalldir,mushrooms,maxMushrooms,poisonMushrooms,maxPoisonMushrooms);
        drawSmall(window, small, smallSprite, smallTexture, smalldir);
        checkBulletSmallCollision(bullet, maxbullet, small,score);
 }
                 drawPoisonMushrooms(window, poisonMushrooms, maxPoisonMushrooms, poisonMushroomTextures, poisonMushroomSprite);

                                           createPoisonMushroom(poisonMushrooms, centipede, bullet, maxPoisonMushrooms, centipedeLength);
                                 drawMushrooms(window, mushrooms, maxMushrooms, mushroomTextures, mushroomSprite, bullet, score);


            initializeCentipede(centipede, centipedeLength, direction);  // Reset centipede for  new level

        }

    if (Lives <= 0) 
    {
    window.clear();
    
    // Draw "Game Over" message 
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setString("Game Over\n\nYour Score "+ std::to_string(score));
    gameOverText.setPosition(resolutionX / 2 - 150, resolutionY / 2 - 25);
    window.draw(gameOverText);
    }

		window.display();

}

}



////////////////////////////////////////////////////////////////////////////

//                                                                        //

// Write your functions definitions here. Some have been written for you. //

//                                                                        //

////////////////////////////////////////////////////////////////////////////



void checkBulletSmallCollision(float bullet[], int& maxBullet, int small[][4], int& score) //Checking bullet and one segment Head collision
{
    for (int i = 0; i < maxBullet; ++i)
    {
        if (bullet[exists])
        {
            int bulletGridX = static_cast<int>(bullet[i] / boxPixelsX);
            int bulletGridY = static_cast<int>((bullet[i + 1] - boxPixelsY) / boxPixelsY);

            for (int j = 0; j < 2; ++j)
            {
                if (small[j][exists])
                {
                    int smallSegmentGridX = small[j][x] / boxPixelsX;
                    int smallSegmentGridY = small[j][y] / boxPixelsY;

                    // Check if bullet and small segment are in the same grid cell
                    if (bulletGridX == smallSegmentGridX && bulletGridY == smallSegmentGridY)
                    {
                        // Collision detected, destroy the bullet and the small segment
                        bullet[exists] = false;
                        small[j][exists] = false;
                        score += 20;
                    }
                }
            }
        }
    }
}


bool isCentipedeInBottomRows(int centipede[][4], int& centipedeLength) //Checking if segments are in player area
{
    for (int i = 0; i < centipedeLength; ++i)
    {
        // check if a segment exists and is not in the last 5 rows
        if (centipede[i][exists] && centipede[i][y] < resolutionY - 5 * boxPixelsY)
        {
            return false;
        }
    }

    // All existing segments are in the last 5 rows
    return true;
}


void drawSmall(sf::RenderWindow& window, int small[][4], sf::Sprite& smallSprite, sf::Texture& smallTexture, int&smalldir) //Draw the one segment Head
{
    for (int i = 0; i < 2; ++i) 
    {
        if (small[i][exists]) 
        {
            smallSprite.setPosition(small[i][x], small[i][y]);
            smallSprite.setTexture(smallTexture);

            // texture  based on direction
            if (small[i][smalldir] == 1) 
            {
                smallSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
            } 
            else 
            {
                smallSprite.setTextureRect(sf::IntRect(boxPixelsX, 0, -boxPixelsX, boxPixelsY));
            }

            window.draw(smallSprite);
        }
    }
}

void moveSmall(int small[][4], sf::Clock& smallClock, int& smalldir, int mushrooms[][4], int& maxMushrooms,int poisonMushrooms[][4], int& maxPoisonMushrooms) //movement of one segment Head
{
    if (smallClock.getElapsedTime().asMilliseconds() < 80)
    {
        return; // Move every 80 milliseconds 
    }

    smallClock.restart();

    for (int i = 0; i < 2; ++i)
    {
        if (small[i][exists])
        {
            // Save the previous x-coordinate before updating
            int prevX = small[i][x];

            small[i][x] += small[i][smalldir] * boxPixelsX;

            // Check boundaries and change direction 
            if (small[i][x] < 0 || small[i][x] >= resolutionX)
            {
                small[i][smalldir] *= -1; // Change direction
                small[i][y] += boxPixelsY;

                // checking if x-coordinate within bounds
                if (small[i][x] < 0)
                {
                    small[i][x] = 0;
                }
                else if (small[i][x] >= resolutionX)
                {
                    small[i][x] = resolutionX - boxPixelsX;
                }

                // Checking if the small sprite collided with the left or right boundary
                if (prevX != small[i][x])
                {
                    // Move down by one block
                    small[i][y] += boxPixelsY;

                }
            }

            if (small[i][y] >= resolutionY - 1 * boxPixelsY)
            {
                small[i][y] = resolutionY - 6 * boxPixelsY;
            }

            // Check for collisions with mushrooms
            int smallGridX = small[i][x] / boxPixelsX;
            int smallGridY = small[i][y] / boxPixelsY;

            for (int j = 0; j < maxMushrooms; ++j)
            {
                if (mushrooms[j][exists])
                {
                    int mushroomGridX = mushrooms[j][x] / boxPixelsX;
                    int mushroomGridY = mushrooms[j][y] / boxPixelsY;

                    // Check if the small entity and mushroom occupy the same grid cell
                    if (smallGridX == mushroomGridX && smallGridY == mushroomGridY)
                    {
                        // Reverse direction and move down one row
                        small[i][smalldir] *= -1;
                        small[i][y] += boxPixelsY;
                    }
                }
            }

            for (int j = 0; j < maxPoisonMushrooms; ++j)
            {
                if (poisonMushrooms[j][exists])
                {
                    int poisonMushroomGridX = poisonMushrooms[j][x] / boxPixelsX;
                    int poisonMushroomGridY = poisonMushrooms[j][y] / boxPixelsY;

                    // Check if the small entity and poisonous mushroom occupy the same grid cell
                    if (smallGridX == poisonMushroomGridX && smallGridY == poisonMushroomGridY)
                    {
                        // Reverse direction and move down one row
                        small[i][smalldir] *= -1;
                        small[i][y] += boxPixelsY;
                    }
                }
            }
        }
    }
}


void initializesmall(int small[][4],int& smalldir) //Initializing one segment Head
{
    for (int i = 0; i < 2; ++i) 
    {
        //  position it slightly out of the screen
        small[i][x] = rand() % (resolutionX) -(2 * boxPixelsX);   //X-coordinates
         small[i][y] = rand() % (boxPixelsY) + (resolutionY - 5 * boxPixelsY);//Y-coordinates
        small[i][exists] = true;//existance
        small[i][smalldir] = -1;//direction
    }
}

void checkPlayerCollision(float player[],int centipede[][4], int& centipedeLength, int& lives,int poisonMushrooms[][4],int& maxPoisonMushrooms, sf::RenderWindow& window,sf::Font& font,int small[][4]) //Checking player collision with game entities
{
    for (int i = 0; i < centipedeLength; ++i) 
    {
        if (centipede[i][exists]) 
        {
            int segmentGridX = centipede[i][x] / boxPixelsX;
            int segmentGridY = centipede[i][y] / boxPixelsY;

            int playerGridX = player[x] / boxPixelsX;
            int playerGridY = player[y] / boxPixelsY;

            // Check if player and centipede segment are in the same box in the game grid
            if (playerGridX == segmentGridX && playerGridY == segmentGridY) 
            {
                //If collision detected, set player position to the center at the bottom
                player[x] = (gameColumns / 2) * boxPixelsX; //center of screen
                player[y] = (gameRows - 1) * boxPixelsY; // Set at the bottom of the screen

                lives--;

        //Text displayed on player death
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(30);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setStyle(sf::Text::Bold);
        gameOverText.setString("\tYou died\n\npress R to respawn\n\nLives remaining " + std::to_string(lives));

        gameOverText.setPosition(resolutionX / 2 - 200, resolutionY / 2 - 25);

        window.clear();
        window.draw(gameOverText);
        window.display();

        // Wait for 'R' key press to respawn
        bool rPressed = false;
        while (!rPressed && window.isOpen())
        {
            // Handle events
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyPressed)
                {
                    // Check if the pressed key is 'R' or 'r'
                    if (event.key.code == sf::Keyboard::R || event.key.code == sf::Keyboard::R)
                        rPressed = true;
                }
            }
        }


            }
        }
    }

for (int i = 0; i < maxPoisonMushrooms; ++i)
    {
        if (poisonMushrooms[i][exists])
        {
            int poisonMushroomGridX = poisonMushrooms[i][x] / boxPixelsX;
            int poisonMushroomGridY = poisonMushrooms[i][y] / boxPixelsY;

            int playerGridX = player[x] / boxPixelsX;
            int playerGridY = player[y] / boxPixelsY;

            // Check if player and poison mushroom are in the same box in the game grid
            if (playerGridX == poisonMushroomGridX  && playerGridY == poisonMushroomGridY)
            {
                // Collision with poison mushroom detected
                lives--;
                player[x] = (gameColumns / 2) * boxPixelsX; 
                player[y] = (gameRows - 1) * boxPixelsY;    // Set at the bottom of the screen
                poisonMushrooms[i][exists] = false;

            sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(30);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setStyle(sf::Text::Bold);
        gameOverText.setString("\tYou died\n\npress R to respawn\n\nLives remaining " + std::to_string(lives));

        gameOverText.setPosition(resolutionX / 2 - 200, resolutionY / 2 - 25);

        window.clear();
        window.draw(gameOverText);
        window.display();

        // Wait for 'R' key press to respawn
        bool rPressed = false;
        while (!rPressed && window.isOpen())
        {
            // Handle events
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyPressed)
                {
                    // Check if the pressed key is 'R' or 'r'
                    if (event.key.code == sf::Keyboard::R || event.key.code == sf::Keyboard::R)
                        rPressed = true;
                }
            }
        }
     }
    }
 }


    for (int i = 0; i < 1; ++i) 
    {
        if (small[i][exists])
        {
            int smallSegmentGridX = small[i][x] / boxPixelsX;
            int smallSegmentGridY = small[i][y] / boxPixelsY;

            int playerGridX = player[x] / boxPixelsX;
            int playerGridY = player[y] / boxPixelsY;

            // Check if player and small segment are in the same box in the game grid
            if (playerGridX == smallSegmentGridX && playerGridY == smallSegmentGridY)
            {
                // Collision with small segment detected, handle as needed
                lives--;

                // Optionally, reset the player's position
                player[x] = (gameColumns / 2) * boxPixelsX; // Adjusted initial x position
                player[y] = (gameRows - 1) * boxPixelsY;    // Set at the bottom of the screen

        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(30);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setStyle(sf::Text::Bold);
        gameOverText.setString("\tYou died\n\npress R to respawn\n\nLives remaining " + std::to_string(lives));

        gameOverText.setPosition(resolutionX / 2 - 200, resolutionY / 2 - 25);

        window.clear();
        window.draw(gameOverText);
        window.display();

        // Wait for 'R' key press to respawn
        bool rPressed = false;
        while (!rPressed && window.isOpen())
        {
            // Handle events
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyPressed)
                {
                    // Check if the pressed key is 'R' or 'r'
                    if (event.key.code == sf::Keyboard::R || event.key.code == sf::Keyboard::R)
                        rPressed = true;
                }
            }
        }
            }
        }
    }
}


void initializePoisonMushrooms(int poisonMushrooms[][4], const int maxPoisonMushrooms,int& health) //Initializing Poison mushrooms
{
    for (int i = 0; i < maxPoisonMushrooms; ++i) 
    {
        // Set initial values
        poisonMushrooms[i][exists] = false; // Initialize as not existing
        poisonMushrooms[i][health] = 2; // Set the health to 2
    }
}

void createPoisonMushroom(int poisonMushrooms[][4], int centipede[][4], float bullet[], const int maxPoisonMushrooms, int& centipedeLength)//creating poison mushroom at collision point
{
    // Check for collision between centipede and bullet in the last 5 rows
    for (int i = 0; i < centipedeLength; ++i)
    {
        if (centipede[i][exists] && centipede[i][y] >= resolutionY - 5 * boxPixelsY)
        {
            // Calculate grid positions for the centipede segment
            int centipedeGridX = static_cast<int>(centipede[i][x] / boxPixelsX);
            int centipedeGridY = static_cast<int>(centipede[i][y] / boxPixelsY);

            // Calculate grid positions for the bullet
            int bulletGridX = static_cast<int>(bullet[x] / boxPixelsX);
            int bulletGridY = static_cast<int>(bullet[y] / boxPixelsY);

            // Check if the bullet and centipede are in the same grid cell
            if (bulletGridX == centipedeGridX && bulletGridY == centipedeGridY)
            {
                for (int j = 0; j < maxPoisonMushrooms; ++j)
                {
                    if (!poisonMushrooms[j][exists])
                    {
                        // Collision detected, set the poison mushroom's position at the collision point
                        poisonMushrooms[j][x] = centipede[i][x];
                        poisonMushrooms[j][y] = centipede[i][y];
                        poisonMushrooms[j][exists] = true; // Mark as existing
                        poisonMushrooms[j][3] = 2;    // Set the health to 2
                        break;
                    }
                }
            }
        }
    }
}



void drawPoisonMushrooms(sf::RenderWindow& window, int poisonMushrooms[][4], int& maxPoisonMushrooms, sf::Texture poisonMushroomTextures[], sf::Sprite& poisonMushroomSprite)
{
    for (int i = 0; i < maxPoisonMushrooms; ++i)
    {
        if (poisonMushrooms[i][exists])
        {
            int health = static_cast<int>(poisonMushrooms[i][3]);

            if (health >= 2)
            {
                poisonMushroomSprite.setTexture(poisonMushroomTextures[0]); // Texture for health == 2
            }
            else if(health>=1)
            {
                poisonMushroomSprite.setTexture(poisonMushroomTextures[1]); // Texture for health == 1
            }

            // Set the position and draw the poison mushroom sprite
            poisonMushroomSprite.setPosition(poisonMushrooms[i][0], poisonMushrooms[i][1]);
            window.draw(poisonMushroomSprite);
        }
    }
}


bool allSegmentsDestroyed(int centipede[][4], int& centipedeLength, int small[][4])//Check if all centipede and one headed segments have been destroyed
{
    for (int i = 0; i < centipedeLength; ++i) {
        if (centipede[i][exists]) {
            return false;  // If any centipede segment exists, return false
        }
    }

    for (int i = 0; i < 2; ++i) {
        if (small[i][exists]) {
            return false;  // If any small segment exists, return false
        }
    }

    // All segments are destroyed
    return true;
}

void initializeMushroom(int index, int mushrooms[][4], int gameGrid[][gameColumns], int & health, int & maxMushrooms)//Initialize the mushrooms and set their positions
{   int i=0;
    do 
    {
mushrooms[index][x] = rand() % (resolutionX-30);
mushrooms[index][y] = (rand() % (resolutionY - 1 * boxPixelsY));//random position except last row of the screen
        i++;

    } while (gameGrid[mushrooms[index][x] / boxPixelsX][mushrooms[index][y] / boxPixelsY] != 0 && i<=maxMushrooms);

    mushrooms[index][2] = true;
    mushrooms[index][health] = 2; // Set initial health

    // Mark the  grid cells as occupied by a mushroom
    int gridX = mushrooms[index][x] / boxPixelsX;
    int gridY = mushrooms[index][y] / boxPixelsY;
    gameGrid[gridX][gridY] = 1;
}


void drawMushrooms(sf::RenderWindow& window, int mushrooms[][4], const int maxMushrooms, sf::Texture mushroomTextures[], sf::Sprite& mushroomSprite, float bullet[3], int & score)//drawing the textures of the mushrooms
{
    for (int i = 0; i < maxMushrooms; ++i)
    {
        if (mushrooms[i][2])
        {
            int health = static_cast<int>(mushrooms[i][3]); 

            if (health >= 2)
            {
                mushroomSprite.setTexture(mushroomTextures[0]); // Texture for health >= 15
            }
            else if (health >= 10)
            {
                mushroomSprite.setTexture(mushroomTextures[1]); // Texture for health >= 10
            }
            else if (health >= 5)
            {
                mushroomSprite.setTexture(mushroomTextures[2]); // Texture for health >= 5
            }
            else // health >= 0
            {
                mushroomSprite.setTexture(mushroomTextures[3]); // Texture for health >= 0
            }

            // Set the position and draw the mushroom sprite
            mushroomSprite.setPosition(mushrooms[i][0], mushrooms[i][1]);
            window.draw(mushroomSprite);

        }
    }
}

void checkBulletMushroomCollision(float bullet[3], int& maxbullet, int mushrooms[][4], int& maxMushrooms, int poisonMushrooms[][4], int& maxPoisonMushrooms, int gameGrid[][gameColumns], int& score) //check collision between bullet and mushrooms
{
    for (int i = 0; i < maxbullet; ++i) 
    {
        int bulletIndex = i * 3; // Adjust the index for the 1D array

        if (bullet[bulletIndex + 2]) 
        {
            int bulletGridX = static_cast<int>(bullet[bulletIndex] / boxPixelsX);
            int bulletGridY = static_cast<int>(bullet[bulletIndex + 1] / boxPixelsY);

            // Check for collision with  mushrooms in the bullet's grid cell
            if (gameGrid[bulletGridX][bulletGridY] == 1) 
            {
                for (int j = 0; j < maxMushrooms; ++j) 
                {
                    if (mushrooms[j][2]) {
                        int mushroomGridX = static_cast<int>(mushrooms[j][x] / boxPixelsX);
                        int mushroomGridY = static_cast<int>(mushrooms[j][y] / boxPixelsY);

                        // Check if the bullet and mushroom occupy the same grid cell
                        if (bulletGridX == mushroomGridX && bulletGridY == mushroomGridY) 
                        {
                            mushrooms[j][3] -= 1; // Reduce mushroom's health
                            bullet[bulletIndex + 2] = false; // Mark bullet as not existing

                            if (mushrooms[j][3] <= 0) 
                            {
                                mushrooms[j][2] = false; // Mark mushroom as not existing
                                score += 1;
                                gameGrid[mushroomGridX][mushroomGridY] = 0;
                            }
                        }
                    }
                }
            }

            // Check for collision with poison mushrooms in the bullet's grid cell
            for (int k = 0; k < maxPoisonMushrooms; ++k) 
            {
                if (poisonMushrooms[k][2]) {
                    int poisonMushroomGridX = static_cast<int>(poisonMushrooms[k][x] / boxPixelsX);
                    int poisonMushroomGridY = static_cast<int>(poisonMushrooms[k][y] / boxPixelsY);

                    // Check if the bullet and poison mushroom occupy the same grid cell
                    if (bulletGridX == poisonMushroomGridX && bulletGridY == poisonMushroomGridY) 
                    {
                        poisonMushrooms[k][3] -= 1; // Reduce poison mushroom's health
                        bullet[bulletIndex + 2] = false; // Mark bullet as not existing

                        if (poisonMushrooms[k][3] <= 0) 
                        {
                            poisonMushrooms[k][2] = false; // Mark poison mushroom as not existing
                            score += 2; // Adjust the score for poison mushrooms
                            gameGrid[poisonMushroomGridX][poisonMushroomGridY] = 0;
                        }
                    }
                }
            }
        }
    }
}


void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite, sf::Event& event, float bullet[3],  int& maxbullet,sf::Clock& bulletClock)//drawing player position on the screen
{

    //Checking key board inputs for player movement
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    if (event.type == sf::Event::Closed) 
    {
        window.close();
    }

    if (event.type == sf::Event::KeyPressed) 
    {
        if (event.key.code == sf::Keyboard::Left) 
        {
            left = true;
        } 
        else if (event.key.code == sf::Keyboard::Right)
        {
            right = true;
        } 
        else if (event.key.code == sf::Keyboard::Up) 
        {
            up = true;
        } 
        else if (event.key.code == sf::Keyboard::Down) 
        {
            down = true;
        } 
        else if (event.key.code == sf::Keyboard::Space) 
        {
        moveBullet(bullet,bulletClock,player);
        }
    }
    else if (event.type == sf::Event::KeyReleased) 
    {
        if (event.key.code == sf::Keyboard::Left) 
        {
            left = false;
        } 
        else if (event.key.code == sf::Keyboard::Right) 
        {
            right = false;
        } 
        else if (event.key.code == sf::Keyboard::Up)
        {
            up = false;
        } 
        else if (event.key.code == sf::Keyboard::Down) 
        {
            down = false;
        }
    }

    // Update player position based on the key states
    if (left && player[x] > 0) 
    {
        player[x] -= 0.25f;
    }
    if (right && player[x] < resolutionX - boxPixelsX) 
    {
        player[x] += 0.25f;
    }
    if (up && player[y] > resolutionY - (5*boxPixelsY)) 
    {
        player[y] -= 0.25f;
    }
    if (down && player[y] < resolutionY - boxPixelsY) 
    {
        player[y] += 0.25f;
    }


    //Restricting the players movement
    if (player[x] < 0) player[x] = 0;
    if (player[x] > resolutionX - boxPixelsX) player[x] = resolutionX - boxPixelsX;
    if (player[y] < 0) player[y] = 0;
    if (player[y] > resolutionY - boxPixelsY) player[y] = resolutionY - boxPixelsY;

    playerSprite.setPosition(player[x], player[y]);
    window.draw(playerSprite);
}

void splitCentipede(sf::Texture& headTexture, int& centipedeLength, int centipede[][4], float bullet[], int& direction, int& score, sf::Sprite& centipedeSprite,int& hitIndex)//checking bullet and centipede segment collision
{
    // Flag to check if bullet collision has already been processed 
    static bool bulletCollisionChecked = false;


    for (int i = 0; i < centipedeLength; ++i)
    {
        int bulletIndex = i * 3; // Adjust the index for the 1D array

        // Use the bulletCollisionChecked flag to check if the bullet collision has already been processed
        if (!bulletCollisionChecked && centipede[i][exists])
        {
            float segmentLeft = centipede[i][x];
            float segmentRight = centipede[i][x] + boxPixelsX;
            float segmentTop = centipede[i][y];
            float segmentBottom = centipede[i][y] + boxPixelsY;

            float bulletLeft = bullet[x];
            float bulletRight = bullet[x] + boxPixelsX;
            float bulletTop = bullet[y];
            float bulletBottom = bullet[y] + boxPixelsY;

            // Check if the bullet and centipede are in the same grid location
            int bulletGridX = static_cast<int>(bulletLeft / boxPixelsX);
            int bulletGridY = static_cast<int>(bulletTop / boxPixelsY);

            int centipedeGridX = static_cast<int>(segmentLeft / boxPixelsX);
            int centipedeGridY = static_cast<int>(segmentTop / boxPixelsY);

    if (bulletGridX == centipedeGridX && bulletGridY == centipedeGridY) //checking if bullet and centipede are in the same grid location
    {
        centipede[i][exists] = false; // Mark segment as not existing
        bullet[exists] = false;//Mark bullet as not existing

        // Check if the current segment is a head
        if (i == 0)
        {
            score += 20;  // Increment score for destroying head

              centipede[i][exists] = false;
        }
        else
        {
            score += 10;  // Increment score for destroying regular segment
        }

        centipedeLength--; //decrease length

                

                // Store the index of the last segment before reversing direction
                hitIndex = i;

                // Reverse the direction of all remaining segments in the centipede
                for (int j = centipedeLength; j >= i+1; --j)
                {
                    if (centipede[j][exists])
                    {
                        centipede[j][direction] *= -1; // Reverse direction

                    }
                }

                

                // Set the flag to indicate that collision has been checked for the current frame
                bulletCollisionChecked = true;
            }
        }
    }

    // Reset the flag at the end of the frame
    if (!bullet[exists])
    {
        bulletCollisionChecked = false;
    }


}


void drawCentipede(sf::RenderWindow& window, int centipede[][4], sf::Sprite& centipedeSprite, int& centipedeLength, sf::Texture& headTexture, sf::Texture& centipedeTexture, int& direction, int& hitIndex)
{
    for (int i = 0; i < centipedeLength; ++i)
    {
        if (centipede[i][exists])
        {
            centipedeSprite.setPosition(centipede[i][x], centipede[i][y]);

            // Check if the current segment is the head of a split
            bool splithead = (i == 0) || (hitIndex == i - 1 && hitIndex != 0);

            // Use head texture for the first segment and split heads, and normal texture for the rest
            if (splithead)
            {
                centipedeSprite.setTexture(headTexture);
            }

            else if (i == centipedeLength - 1 && !centipede[i][exists] && (!centipede[i - 1][exists] || !centipede[i + 1][exists]))
             {
                    centipedeSprite.setTexture(headTexture);
            }

            else
            {
                centipedeSprite.setTexture(centipedeTexture);
            }

            // Adjust texture  based on direction
            if (centipede[i][direction] == 1)
            {
                centipedeSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
            }
            else
            {
                centipedeSprite.setTextureRect(sf::IntRect(boxPixelsX, 0, -boxPixelsX, boxPixelsY));
            }

            window.draw(centipedeSprite);
        }
    }
}


void moveCentipede(int centipede[][4], int& centipedeLength, int& direction, sf::Clock& centipedeClock, int mushrooms[][4], int& maxMushrooms,float& fact,int& collisionCount)
{
    if (centipedeClock.getElapsedTime().asMilliseconds() < 120/fact)
    {
        return; // Move every 100 milliseconds 
    }

    centipedeClock.restart();

    for (int i = 0; i < centipedeLength; ++i)
    {
        if (centipede[i][exists])
        {
            centipede[i][x] += centipede[i][direction] * boxPixelsX;

            // Check boundaries and change direction 
            if (centipede[i][x] + centipede[i][direction] * boxPixelsX < 0 ||
    centipede[i][x] + centipede[i][direction] * boxPixelsX >= resolutionX)
            {
                centipede[i][direction] *= -1; // Change direction
                centipede[i][y] += boxPixelsY; // Move down
            }

              if (centipede[i][y] >= resolutionY - 1 * boxPixelsY) 
              {
                    centipede[i][y] = resolutionY - 6 * boxPixelsY;
                }

            // Check for collisions with mushrooms
            int centipedeGridX = centipede[i][x] / boxPixelsX;
            int centipedeGridY = centipede[i][y] / boxPixelsY;

            for (int j = 0; j < maxMushrooms; ++j)
            {
                if (mushrooms[j][exists])
                {
                    int mushroomGridX = mushrooms[j][x] / boxPixelsX;
                    int mushroomGridY = mushrooms[j][y] / boxPixelsY;

                    // Check if the centipede and mushroom occupy the same grid cell
                    if (centipedeGridX == mushroomGridX && centipedeGridY == mushroomGridY)
                    {
                        centipede[i][direction] *= -1; // Change direction
                        centipede[i][y] += boxPixelsY; // Move down one row
                        collisionCount++;
                        break;                          // Break out of the loop after handling the collision
                    }
                }
            }
        }
    }
}


void initializeCentipede(int centipede[][4], int& centipedeLength, int& direction) 
{
      int headX = rand() % (gameColumns * boxPixelsX - centipedeLength * boxPixelsX); // Random X within the game area with enough space for all segments
    int headY = rand() % (resolutionY - 5 * boxPixelsY) + boxPixelsY; // Random Y excluding the last 5 rows


    for (int i = 0; i < centipedeLength; ++i)
    {
        centipede[i][x] = headX + i * boxPixelsX; // Adjusted initial x position
        centipede[i][y] = headY;                   // Initial y position same as the head
        centipede[i][exists] = true;
        centipede[i][direction] = -1;
    }
}


void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite) 
{

	playerSprite.setPosition(player[x], player[y]);

	window.draw(playerSprite);

}

void moveBullet(float bullet[], sf::Clock& bulletClock, float player[])
{
    if (bulletClock.getElapsedTime().asMilliseconds() < 10)
        return;

    bulletClock.restart();

    // Only move the bullet if it's active
    if (bullet[exists]) 
    {
        bullet[y] -= 10;

        if (bullet[y] < -32) 
        {
            bullet[exists] = false;
        }
    }
    else 
    {
        // Set the bullet's position to the player position when it is fired
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
        {
            bullet[x] = player[x];
            bullet[y] = player[y] - boxPixelsY;
            bullet[exists] = true;
        }
    }
}


void drawBullet(sf::RenderWindow& window, float bullet[], sf::Sprite& bulletSprite) 
{

	bulletSprite.setPosition(bullet[x], bullet[y]);

	window.draw(bulletSprite);

}

