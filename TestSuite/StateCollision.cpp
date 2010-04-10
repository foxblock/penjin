#include "StateCollision.h"

StateCollision::StateCollision()
{
    //ctor
    text.setPosition(526,32);
    text.setRelativity(true);
    text.loadFont("font/unispace.ttf",10);
    GFX::setClearColour(WHITE);
    cursor.setColour(BLACK);
    cursor.setLineWidth(1);

    // Loading the sprites/images
    // if you need an explanation of this code you probably should not be using
    // CollisionRegions in the first place...
    bg.loadSprite("images/Textures/Border.png");
    bg.setTransparentColour(MAGENTA);
    bg.setPosition(0,0);
    bullet.loadSprite("images/Bullet.png");
    bullet.setTransparentColour(MAGENTA);
    bullet.setPosition(372,100);
    critter.loadFrames("images/critter.png",2,1);
    critter.setFrameRate(DECI_SECONDS);
    critter.setLooping(true);
    critter.setTransparentColour(MAGENTA);
    critter.setPosition(270,190);

    // Sets a collision region without loading an image
    bgCol.setPosition(32,32);
    bgCol.setSize(480,320);
    // Loads a collision image and generates a region of that afterwards
    critterCol.loadImage("images/critter_col.png");
    critterCol.setNoCollisionColour(MAGENTA);
    // Set position to position of sprite (required)
    critterCol.setPosition(270,190);
    // Generates the region by analysing the image (noCollisionColour must be set before)
    critterCol.generateHitRegion();
    bulletCol.loadImage("images/Bullet.png");
    bulletCol.setNoCollisionColour(MAGENTA);
    bulletCol.setPosition(372,100);
    bulletCol.generateHitRegion();

    // Options (defaults)
    options[useCollisionImages] = true;
    options[useRegions] = true;
    options[fullShapeCheck] = true;
    options[movingBullet] = true;
    options[renderCollision] = true;
    updateTime = 0;
}

void StateCollision::init()
{
    text.setBoundaries(Vector2di(0,0),Vector2di(GFX::getXResolution(),GFX::getYResolution()));
}

StateCollision::~StateCollision()
{
    // do fancy stuff here :D
}

void StateCollision::render()
{
    GFX::clearScreen();

    // Render sprites and collision objects
    bg.render();
    bullet.render();
    if (options[renderCollision])
        bulletCol.render();
    critter.render();
    if (options[renderCollision])
    {
        critterCol.render();
        bgCol.render();
    }

    // Render text
    text.setPosition(526,32);
    text.print("Options:\n");
    text.print("Collision Images (A): " + boolToString(options[useCollisionImages]) + "\n");
    text.print("Collision Regions (B): " + boolToString(options[useRegions]) + "\n");
    text.print("Full shape collisions (X): " + boolToString(options[fullShapeCheck]) + "\n");
    text.print("Moving Bullet (Y): " + boolToString(options[movingBullet]) + "\n");
    text.print("Render collisions (R): " + boolToString(options[renderCollision]) + "\n\n\n");
    text.print("Collision: " + boolToString(isCollision) + "\n");
    text.print("With: " + whoCollision + "\n\n\n");
    text.print("Total update time: " + intToString(updateTime) + "ms\n");

    // Render mouse cursor
    cursor.setStartPosition(input->getTouch() - Vector2di(3,0));
    cursor.setEndPosition(input->getTouch() + Vector2di(3,0));
    cursor.render();
    cursor.setStartPosition(input->getTouch() - Vector2di(0,3));
    cursor.setEndPosition(input->getTouch() + Vector2di(0,3));
    cursor.render();
}


void StateCollision::update()
{
    critter.update();

    int updateLast = clock();

    // Move the bullet and adjust CollisionRegions position to match sprites
    // This operation is always required or your sprite and your collisionObject will
    // get out of synch. Alternatively you can create a class which takes care of this.
    if (options[movingBullet])
    {
        bullet.setX(bullet.getX() - BULLET_SPEED);
        if (bullet.getX() < 32)
            bullet.setX(372);
    }
    bulletCol.setX(bullet.getX());
    critterCol.setPosition(critter.getPosition());

    // Collision checking
    isCollision = false;
    whoCollision = "";
    // Checking against a CollisionRegion object without an image applied to it
    if (critterCol.hitTest(&bgCol,options[fullShapeCheck]))
    {
        isCollision = true;
        whoCollision += "Background, ";
    }
    // Checking against a variable CollisionRegion (image and/or region)
    if (critterCol.hitTest(&bulletCol,options[fullShapeCheck]))
    {
        isCollision = true;
        whoCollision += "Bullet, ";
    }
    // Checking against a single point (always uses full shape checking when an image is loaded)
    if (critterCol.hitTest(input->getTouch().x,input->getTouch().y,true))
    {
        isCollision = true;
        whoCollision += "Mouse";
    }

    // Measure total time needed for updates (due to timer resolution)
    updateTime += clock() - updateLast;
    // The tests have shown that using a collision image combined with a region is the best deal
    // of performance vs. accuracy when using fullShape checks. The worst alternative is using
    // fullShape checks without having generated a region beforehand as the region optimizes the
    // ranges of the check and without it every pixel of both images might get checked.
    // Usually one does not need fullShape checks anyway, so solely using a region or a generated
    // region from an image (same performance) with rectangular collision checking should suffice.
    // It also has a noticeable performance improvement compared to fullShape checks.
}

void StateCollision::userInput()
{
    input->update();
    #ifdef PLATFORM_PC
        if(input->isQuit())
            nullifyState();
    #endif
    // Return to main menu
    if(input->isStart())
        setNextState(STATE_TITLE);

    // Options
    if (input->isA())
    {
        // Remove or add an collision image to the bullet and critter
        // Removal only fires when a region has been loaded so collision can be checked
        options[useCollisionImages] = not options[useCollisionImages];
        if (options[useCollisionImages])
        {
            critterCol.loadImage("images/critter_col.png");
            bulletCol.loadImage("images/Bullet.png");
        }
        else if (options[useRegions])
        {
            bulletCol.freeImage();
            critterCol.freeImage();
        }
        else
            options[useCollisionImages] = true;
        input->resetA();
    }
    if (input->isB())
    {
        // Remove or add a collision region to the bullet and trigger
        // Removal only fires when an collision image has been loaded
        options[useRegions] = not options[useRegions];
        if (options[useRegions])
        {
            critterCol.generateHitRegion();
            bulletCol.generateHitRegion();
        }
        else if (options[useCollisionImages])
        {
            bulletCol.resetHitRegion();
            critterCol.resetHitRegion();
        }
        else
            options[useRegions] = true;
        input->resetB();
    }
    if (input->isX())
    {
        // Toggle full shape collision checking
        options[fullShapeCheck] = not options[fullShapeCheck];
        input->resetX();
    }
    if (input->isY())
    {
        // Toggle moving of the bullet image
        options[movingBullet] = not options[movingBullet];
        input->resetY();
    }
    if (input->isR())
    {
        // Toggle rendering of the collisionRegions
        options[renderCollision] = not options[renderCollision];
        input->resetR();
    }


    // Critter movement
    if(input->isLeft() && critter.getX() > 0)
    {
        critter.setX(critter.getX() - CRITTER_SPEED);
    }
    else if(input->isRight() && (critter.getX() < 800 - critter.getWidth()))
    {
        critter.setX(critter.getX() + CRITTER_SPEED);
    }

    if(input->isUp() && critter.getY() > 0)
    {
        critter.setY(critter.getY() - CRITTER_SPEED);
    }
    else if(input->isDown() && (critter.getY() < 480 - critter.getHeight()))
    {
        critter.setY(critter.getY() + CRITTER_SPEED);
    }
}
