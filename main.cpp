#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <string>
#include <cstdlib>
#include <ctime>
#include <time.h>

using namespace sf;
using namespace std;

int windowWidth = 1920;  // 400
int windowHeight = 1080; // 300

class platformClass
{
public:
    double xpos;
    double ypos;
    double xvel;
    double yvel;

    platformClass(double xpos, double ypos)
    {
        xpos = xpos;
        ypos = ypos;
        int scale;
    }
};

class playerClass
{
public:
    bool playerFaceRight;
    bool onGround;
    bool playerUp;
    bool canJump;
    double xpos;
    double ypos;
    double xvel;
    double yvel;
    double jumpSpeed;
    double movementSpeed;
    double gravity;
    bool jumping;

    playerClass(double jumpspeed, double movementspeed, double GRAVITY, bool playerup)
    {
        playerFaceRight = true;
        onGround = false;
        xpos = 0;
        ypos = 0;
        xvel = 0;
        yvel = 0;
        jumpSpeed = jumpspeed;
        movementSpeed = jumpSpeed;
        gravity = GRAVITY;
        playerUp = playerup;

        double xvel = 0;
        double yvel = 0;
        cout << "[PLAYER CLASS INITIALIZED]\n";
    }

    void update(bool playerUp, bool playerDown, bool playerRight, bool playerLeft, bool isjumping)
    {
        if (playerRight)
        {
            playerFaceRight = true;
            xvel = movementSpeed;
        }
        if (playerLeft)
        {
            playerFaceRight = false;
            xvel = -movementSpeed;
        }
        if (playerUp && isjumping)
        {
            yvel = -jumpSpeed;
        }
        if (playerDown)
        {
            yvel = jumpSpeed;
        }

        // Reset
        if (!(playerRight || playerLeft))
        {
            xvel = 0;
        }
        if (!(playerUp || playerDown))
        {
            yvel = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::Up) && ypos > 310)
        {
            yvel -= (gravity - 2);
            canJump = false;

            xpos += xvel;

            if (onGround == true /*|| jumping == true*/ && canJump == true)
            {
                yvel = 0;
                yvel *= 2;
                canJump = true;
                ypos += yvel;
            }
        }

        if (onGround == false /*&& jumping == false*/)
        {
            yvel += gravity;
            canJump = false;
            xpos += xvel;
        }

        xpos += xvel;
        ypos += yvel;
    }

    void ground()
    {
        if (ypos > 410)
        {
            onGround = true;
            canJump = true;
        }
        else
        {
            onGround = false;
            canJump = false;
        }
    }
};

// MAIN CODE

int main()
{
    using namespace std::this_thread;
    using namespace std::chrono;

    Texture windowTex;
    windowTex.loadFromFile("textures/background.png");
    Sprite windowBackground(windowTex);
    windowBackground.scale(10, 10);

    // "TUTORIAL"
    RenderWindow tutorial(VideoMode(windowWidth, windowHeight), "TUTORIAL");
    bool slide1BOOL = true;
    bool slide2BOOL = false;
    bool slide3BOOL = false;
    bool slide4BOOL = false;

    Font marioFont;
    marioFont.loadFromFile("fonts/Mario Font/SuperMario256.ttf");

    Texture marioTexTutorial;
    marioTexTutorial.loadFromFile("spritesheets/mario.png");

    Sprite marioTUTORIAL(marioTexTutorial);
    marioTUTORIAL.scale(50.f, 50.f);

    Texture slide1Tex;
    slide1Tex.loadFromFile("slides/welcome-slide-1.png");
    Sprite slide1(slide1Tex);
    slide1.scale(2.5f, 2.5f);
    slide1.setPosition(-500, -300);

    Texture slide2Tex;
    slide2Tex.loadFromFile("slides/keyboard.png");
    Sprite slide2(slide2Tex);
    slide2.scale(9.f, 9.f);
    slide2.setPosition(650, 100);

    Text slide4Text;
    slide4Text.setString("PLEASE WAIT FOR 5 SECONDS, AND THEN CLOSE THIS WINDOW");

    Text slide2Text__000;
    Text slide2Text__001;
    Text slide2Text__002;
    Text slide2Text__003;
    Text slide2Text__004;
    Text slide2Text__005;
    Text slide2Text__006;
    Text slide2Text__007;

    slide2Text__000.setString("You");
    slide2Text__001.setString("Will");
    slide2Text__002.setString("Be");
    slide2Text__003.setString("Using");
    slide2Text__004.setString("Arrow");
    slide2Text__005.setString("Keys");
    slide2Text__006.setString("To");
    slide2Text__007.setString("Move");

    slide2Text__000.setFont(marioFont);
    slide2Text__000.setFillColor(Color::Yellow);
    slide2Text__000.scale(2.f, 2.f);
    slide2Text__000.setPosition(1200, 250); // x-100,y+150

    slide2Text__001.setFont(marioFont);
    slide2Text__001.setFillColor(Color::Red);
    slide2Text__001.scale(2.f, 2.f);
    slide2Text__001.setPosition(1350, 250);

    slide2Text__002.setFont(marioFont);
    slide2Text__002.setFillColor(Color::Green);
    slide2Text__002.scale(2.f, 2.f);
    slide2Text__002.setPosition(1550, 250);

    slide2Text__003.setFont(marioFont);
    slide2Text__003.setFillColor(Color::Blue);
    slide2Text__003.scale(2.f, 2.f);
    slide2Text__003.setPosition(1150, 350);

    slide2Text__004.setFont(marioFont);
    slide2Text__004.setFillColor(Color::Red);
    slide2Text__004.scale(2.f, 2.f);
    slide2Text__004.setPosition(1370, 350);

    slide2Text__005.setFont(marioFont);
    slide2Text__005.setFillColor(Color::Yellow);
    slide2Text__005.scale(2.f, 2.f);
    slide2Text__005.setPosition(1620, 350);

    slide2Text__006.setFont(marioFont);
    slide2Text__006.setFillColor(Color::Green);
    slide2Text__006.scale(2.f, 2.f);
    slide2Text__006.setPosition(1270, 450);

    slide2Text__007.setFont(marioFont);
    slide2Text__007.setFillColor(Color::Blue);
    slide2Text__007.scale(2.f, 2.f);
    slide2Text__007.setPosition(1400, 450);

    Font tutorialFont;
    tutorialFont.loadFromFile("fonts/Press_Start_2P/PressStart2P-Regular.ttf");

    String playerInput;
    Text playerText;
    playerText.setFont(tutorialFont);
    playerText.setFillColor(Color::White);

    Sprite anotherMarioTUTORIAL(marioTexTutorial);
    anotherMarioTUTORIAL.setScale(15.f, 15.f);
    anotherMarioTUTORIAL.setPosition(Vector2f(-500.f, -1000.f));

    while (tutorial.isOpen())
    {
        Event tutorialEvent;
        while (tutorial.pollEvent(tutorialEvent))
        {
            if (tutorialEvent.type == Event::Closed && slide2BOOL == true)
            {
                std::cout << "The game will start in a few seconds...\n";
                tutorial.close();
            }
            if (tutorialEvent.type == sf::Event::TextEntered)
            {
                playerInput += tutorialEvent.text.unicode;
                playerText.setString(playerInput);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Space) && slide1BOOL == true)
        {
            slide2BOOL = true;
        }
        tutorial.clear();
        if (slide1BOOL == true)
        {
            tutorial.draw(slide1);
        }

        if (slide2BOOL == true)
        {
            tutorial.clear();
            tutorial.draw(windowBackground);
            tutorial.draw(slide2);
            tutorial.draw(anotherMarioTUTORIAL);
            tutorial.draw(marioTUTORIAL);
            tutorial.draw(slide2Text__000);
            tutorial.draw(slide2Text__001);
            tutorial.draw(slide2Text__002);
            tutorial.draw(slide2Text__003);
            tutorial.draw(slide2Text__004);
            tutorial.draw(slide2Text__005);
            tutorial.draw(slide2Text__006);
            tutorial.draw(slide2Text__007);
        }
        tutorial.display();
    }

    //  REAL GAME
    sleep_for(nanoseconds(100000000)); // For the delay so my program doesn't break
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Platformer Game");

    // Gravity
    const double gravity = 5;

    double movementSpeed = 5.0f;
    double jumpSpeed = 5.f;
    bool marioLeft;
    bool jumping;
    bool right_animate;
    int life = 3;
    float time = 300; // Float because it looks more satisfying that way
    bool livesFour = false;
    bool livesFive = false;
    bool livesThree = true;
    bool powerup1_ACTIVE = true; // Meaning, it is waiting to be used
    bool canPress;
    bool onJumpGROUND;
    bool shouldMove = true;
    double placeholderTime = 30; // Because it is easy to predict because time = 300
    int number;
    string whichPipe;
    string developerMode;

    bool playerUp, playerDown, playerLeft, playerRight = false;

    // developerMode

    cout << "Would you like to enter developerMode? " << endl;
    cin >> developerMode;

    // Player Class OBJECT

    playerClass playerObject(jumpSpeed, movementSpeed, gravity, playerUp);

    // Fonts
    Font open_sans;
    open_sans.loadFromFile("fonts/Open_Sans.ttf");

    Text helloText("Hello User!", open_sans, 50);

    // Textures and Sprites

    Texture marioTex;
    marioTex.loadFromFile("spritesheets/mario.png");

    Sprite mario(marioTex);
    mario.setPosition(150, -118); // DON'T CHANGE THIS, IT IS PERFECT (the y axis)
    mario.scale(5.f, 5.f);

    // PowerUp
    Texture powerUpTex;
    Texture powerUpDeInit;
    powerUpDeInit.loadFromFile("spritesheets/powerup-de-init().png");
    powerUpTex.loadFromFile("spritesheets/powerup.png");

    Sprite powerUp1(powerUpTex);
    powerUp1.setPosition(150, 450); // These coords are ok for now
    powerUp1.scale(5.f, 5.f);

    // Enemies

    // Bullet Bill
    Texture bulletBillTex;
    bulletBillTex.loadFromFile("spritesheets/bullet-bill.png");

    Sprite bulletBill__001;
    bulletBill__001.setTexture(bulletBillTex);
    bulletBill__001.setPosition(Vector2f(1725.f, 300.f));
    bulletBill__001.scale(5.f, 5.f);

    Color bulletBill__001_COLOR = bulletBill__001.getColor();

    // Goomba
    Texture goombaTex;
    goombaTex.loadFromFile("spritesheets/goomba.png");

    Sprite goomba__001;
    goomba__001.setTexture(goombaTex);
    goomba__001.setScale(5.f, 5.f);
    // goomba__001.setPosition(Vector2f(300.f,0.f));
    goomba__001.setPosition(mario.getPosition().x, mario.getPosition().y);

    // Platforms
    Texture floorTex;
    floorTex.loadFromFile("spritesheets/mario-floor.png");

    Sprite floor1(floorTex);
    floor1.scale(5.f, 5.f);
    floor1.setPosition(Vector2f(-200.f, 170.f));

    Sprite floor2(floorTex);
    floor2.scale(5.f, 5.f);
    floor2.setPosition(Vector2f(-200.f, 255.f));

    Sprite floor3(floorTex);
    floor3.scale(5.f, 5.f);
    floor3.setPosition(Vector2f(-200.f, 340.f));

    // LIVES

    Font press_start_2p;
    press_start_2p.loadFromFile("fonts/press_start_2p/PressStart2P-Regular.ttf");
    Text lives;
    lives.setString(to_string(life));
    Text strLives("LIVES", press_start_2p);
    lives.setFont(press_start_2p);
    lives.setCharacterSize(40);

    lives.setPosition(Vector2f(1720.f, 30.f)); // Pretty good coords for now
    strLives.setPosition(Vector2f(1650.f, 75.f));
    strLives.setCharacterSize(40);

    // TIMER
    Text timer;
    timer.setFont(press_start_2p);
    timer.setString(to_string(time));
    timer.setCharacterSize(50);
    timer.setPosition(Vector2f(725.f, 50.f));

    Texture leftPipeTex;
    leftPipeTex.loadFromFile("spritesheets/pipe-left.png");
    Sprite leftPipe;
    leftPipe.setTexture(leftPipeTex);
    leftPipe.setPosition(Vector2f(-325.f, 354.f));
    leftPipe.setScale(Vector2f(10.f, 10.f));

    // PIPES

    Texture rightPipeTex;
    rightPipeTex.loadFromFile("spritesheets/pipe-right.png");
    Sprite rightPipe;
    rightPipe.setTexture(rightPipeTex);
    rightPipe.setPosition(mario.getPosition().x, mario.getPosition().y);
    rightPipe.setPosition(Vector2f(1355.f, 405.f));
    rightPipe.setScale(Vector2f(10.f, 10.f));

    // STATS
    Font quantico;
    quantico.loadFromFile("fonts/Quantico/Quantico-Regular.ttf");
    Text marioX;
    Text marioY;
    Text cooldownFOR_pu1;
    Text originMARIO;
    Text originBB1;
    Text marioGlobal;
    Text bb1Global;

    marioX.setFont(quantico);
    marioY.setFont(quantico);
    cooldownFOR_pu1.setFont(quantico);
    originMARIO.setFont(quantico);
    originBB1.setFont(quantico);
    marioGlobal.setFont(quantico);
    bb1Global.setFont(quantico);

    marioX.setFillColor(Color::Green);
    marioY.setFillColor(Color::Blue);
    cooldownFOR_pu1.setFillColor(Color::White);
    originMARIO.setFillColor(Color::Yellow);
    originBB1.setFillColor(Color::Green);
    marioGlobal.setFillColor(Color::Yellow);
    bb1Global.setFillColor(Color::Blue);

    marioX.setPosition(Vector2f(1250.f, 170.f)); // 30
    marioY.setPosition(Vector2f(1250.f, 200.f));
    cooldownFOR_pu1.setPosition(Vector2f(1250.f, 230.f));
    originMARIO.setPosition(Vector2f(1250.f, 260.f));
    originBB1.setPosition(Vector2f(1250.f, 290.f));
    marioGlobal.setPosition(Vector2f(1250.f, 320.f));
    bb1Global.setPosition(Vector2f(1250.f, 350.f));

    marioX.setCharacterSize(25);
    marioY.setCharacterSize(25);
    cooldownFOR_pu1.setCharacterSize(25);
    originMARIO.setCharacterSize(25);
    originBB1.setCharacterSize(25);
    marioGlobal.setCharacterSize(25);
    bb1Global.setCharacterSize(23);

    bool gameEnd = false; // memory management i guess...

    // WINDOW LOOP

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Mario Left and Right
        if (marioLeft == true)
        {
            mario.setPosition(mario.getPosition().x, mario.getPosition().y);
            mario.setTexture(marioTex); // Make it to the left side
        }
        if (marioLeft == false)
        {
            marioTex.loadFromFile("spritesheets/mario.png");
            mario.setTexture(marioTex);
        }

        if (onJumpGROUND == true)
        {
            if (playerObject.ypos > 310)
            {
                playerObject.ground();
            }
        }

        // Keyboard Events
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            right_animate = true;
            playerRight = true;
            marioLeft = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
            playerUp = true;

        jumping = true;
        if (Keyboard::isKeyPressed(Keyboard::Left))
            marioLeft = true;
        playerLeft = true;

        // NOT Keyboard Events
        if (!Keyboard::isKeyPressed(Keyboard::Right))
        {
            playerRight = false;
            mario.setPosition(mario.getPosition().x, mario.getPosition().y);
        }
        if (!Keyboard::isKeyPressed(Keyboard::Up))
        {
            playerUp = false;
            jumping = false;
        }
        if (!Keyboard::isKeyPressed(Keyboard::Left))
        {
            playerLeft = false;
            mario.setPosition(mario.getPosition().x, mario.getPosition().y);
        }

        // Future-Mario
        if (Keyboard::isKeyPressed(Keyboard::K) && Keyboard::isKeyPressed(Keyboard::T))
        {
            marioTex.loadFromFile("spritesheets/future-mario.png");
            mario.setPosition(mario.getPosition().x - 30, mario.getPosition().y);
            mario.setTexture(marioTex);
        }
        if ((Keyboard::isKeyPressed(Keyboard::R) && Keyboard::isKeyPressed(Keyboard::T)))
        {
            marioTex.loadFromFile("spritesheets/mario.png");
            mario.setTexture(marioTex);
        }

        if (life == 1)
        {
            lives.setString("1");
        }
        if (life == 2)
        {
            lives.setString("2");
        }
        if (life == 3)
        {
            lives.setString("3");
        }
        if (life == 4)
        {
            lives.setString("4");
        }
        if (life == 5)
        {
            lives.setString("5");
        }

        if (time >= 0)
        {
            time -= 0.007;
            timer.setString(to_string(time));
        }
        else
        {
            cout << "THE GAME HAS ENDED\n";
            window.close();
        }

        //  Player Events
        playerObject.update(playerUp, playerDown, playerRight, playerLeft, jumping);
        playerObject.ground();

        // x = -35, -160
        // y = -175, -140
        if (placeholderTime >= 0 && powerup1_ACTIVE == false)
        {
            placeholderTime -= 0.005;
        }
        if (placeholderTime <= 0 && powerup1_ACTIVE == false)
        {
            powerup1_ACTIVE = true;
            placeholderTime = 30;
        }

        if (powerup1_ACTIVE == true)
        {
            powerUp1.setTexture(powerUpTex);
        }
        if (powerup1_ACTIVE == false)
        {
            powerUp1.setTexture(powerUpDeInit);
        }

        if (mario.getPosition().x <= -30 && mario.getPosition().x >= -160 && mario.getPosition().y >= 180 && mario.getPosition().y <= 193 && powerup1_ACTIVE == true)
        {
            life++;
            powerup1_ACTIVE = false;
        }

        //  ORIGIN
        double bulletBill__001_ORIGIN = bulletBill__001.getGlobalBounds().height / 2 + bulletBill__001.getGlobalBounds().width / 2;
        double mario_ORIGIN = mario.getGlobalBounds().height / 2 + mario.getGlobalBounds().width / 2;
        double goomba__001_ORIGIN = goomba__001.getGlobalBounds().height / 2 + goomba__001.getGlobalBounds().width / 2;

        // FloatRect
        sf::FloatRect marioBox = mario.getGlobalBounds();
        sf::FloatRect bulletBill__001_BOX = bulletBill__001.getGlobalBounds();

        if (1 + 1 == 2)
        {
            marioX.setString("Mario X: " + to_string(mario.getPosition().x));
            marioY.setString("Mario Y: " + to_string(mario.getPosition().y));
            cooldownFOR_pu1.setString("PowerUp Cooldown: " + to_string(placeholderTime));
            originMARIO.setString("Mario Origin: " + to_string(mario_ORIGIN));
            originBB1.setString("BB1 Origin: " + to_string(bulletBill__001_ORIGIN));
            marioGlobal.setString("Mario Global Height-Width: " + to_string(marioBox.height) + ", " + to_string(marioBox.width));
            bb1Global.setString("BB1 Global Height-Width: " + to_string(bulletBill__001_BOX.height) + ", " + to_string(bulletBill__001_BOX.width));
        }

        // DEVELOPER-MODE
        if (developerMode == "y" || developerMode == "Yes" || developerMode == "Y" || developerMode == "yes")
        {
            cout << "\t\tMARIO POSITION: x = " << mario.getPosition().x << ", y = " << mario.getPosition().y << endl;
            cout << "\t\tGOOMBA_1 POSITION: x = " << goomba__001.getPosition().x << ", y = " << goomba__001.getPosition().y << endl;
            cout << "\t\tBB1 Position: " << bulletBill__001.getPosition().x << ", y = " << bulletBill__001.getPosition().y << endl;
            cout << "\t\tPowerUp One Recharge Time Left = " << placeholderTime << endl;
            cout << "\t\tBB1 ORIGIN: " << bulletBill__001_ORIGIN << endl;
            cout << "\t\tMARIO ORIGIN: " << mario_ORIGIN << endl;
            cout << "\t\tGOOMBA_1 ORIGIN: " << goomba__001_ORIGIN << endl;
            cout << "\t\tMARIO GLOBAL BOUNDS HEIGHT AND WIDTH: " << marioBox.height << ", " << marioBox.width << endl;
            cout << "\t\tBB1 GLOBAL BOUNDS HEIGHT AND WIDTH: " << bulletBill__001_BOX.height << ", " << bulletBill__001_BOX.width << endl
                 << endl
                 << endl
                 << endl;
        }

        if (mario.getPosition().x == bulletBill__001.getPosition().x)
        {
            life--;
        }

        if (life == 0)
        {
            gameEnd = true;
            break;
        }

        if (gameEnd == true)
        {
            cout << "\t\tGAME OVER!\n";
        }

        // Enemy Movement
        if (shouldMove == true)
        {
            bulletBill__001.move(-2.5f, 0.f);
            if (goomba__001.getPosition().y >= 650)
            {
                goomba__001.move(0.f, 0.f);
            }
            else
            {
            }
        }
        // Developers Mode Bool
        bool canDEVELOPERMODE;
        if (developerMode == "y" || developerMode == "Yes" || developerMode == "Y" || developerMode == "yes")
        {
            canDEVELOPERMODE = true;
        }

        // PIPE MOVEMENT
        if (mario.getPosition().x <= -170)
        {
            mario.setPosition(1235, mario.getPosition().y);
        }
        if (mario.getPosition().x >= 1235)
        {
            mario.setPosition(-170, mario.getPosition().y);
        }

        if (mario.getPosition().x >= 1127)
        {
            playerObject.xvel = 0;
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                movementSpeed = 0.f;
            }
            if (mario.getPosition().x != 1235)
            {
                if (Keyboard::isKeyPressed(Keyboard::Right))
                { /*Do nothing*/
                }
                mario.move(0.7f, 0.f);
            }
        }

        if (goomba__001.getPosition().y >= 650)
        {
            goomba__001.move(1.f, 0.f);
        }

        // Goomba Gravity
        if (goomba__001.getPosition().y <= 650)
        {
            goomba__001.move(0.f, 2.f);
        }

        if (goomba__001.getPosition().x >= 1350)
        {
            goomba__001.move(0.f, 0.f); // So when the goomba is falling, it doesn't change the xpos too.

            if (goomba__001.getPosition().x != 1500)
            {
                goomba__001.move(0.1f, 0.f);
            }
        }
        if (goomba__001.getPosition().x >= 1500)
        {
            goomba__001.setPosition(100, goomba__001.getPosition().y);
        }

        //  Rendering

        window.clear();
        window.draw(windowBackground);
        if (canDEVELOPERMODE == true)
        {
            window.draw(marioX);
            window.draw(marioY);
            window.draw(cooldownFOR_pu1);
            window.draw(originMARIO);
            window.draw(originBB1);
            window.draw(marioGlobal);
            window.draw(bb1Global);
        }
        window.draw(goomba__001);
        window.draw(bulletBill__001);
        window.draw(mario);
        window.draw(leftPipe);
        window.draw(rightPipe);
        window.draw(powerUp1);
        window.draw(lives);
        window.draw(strLives);
        window.draw(timer);
        window.draw(floor1);
        window.draw(floor2);
        window.draw(floor3);
        mario.move(Vector2f(playerObject.xvel, playerObject.yvel));
        window.display();
    }
    return 0;
}
