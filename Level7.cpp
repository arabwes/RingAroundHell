#include "Level7.h"

Level7::Level7()
{
	dxFont = new TextDX();  // DirectX font
    messageY = 0;
	initialized = false;
}

Level7::~Level7()
{
	releaseAll();           // call onLostDevice() for every graphics item
    safeDelete(dxFont);
}

void Level7::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // MANAGE POSSIBLE GAME ERRORS

    // LEVEL 7 FIGHTING GAME TEXTURES
    if (!wallpaper.initialize(graphics, "pictures\\HorrorWall.jpg"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Background"));

	if (!protagonist.initialize(graphics, "pictures\\Ghoul.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player"));

	if (!badbitch.initialize(graphics, "pictures\\BadBitch.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Enemy"));

	if (!bborb.initialize(graphics, "pictures\\Orb.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player"));

	if (!proscythe.initialize(graphics, "pictures\\Death Scythe.jpg"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Enemy"));

    // menu image
    if (!wall.initialize(graphics,0,0,0,&wallpaper))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Wall"));

	// menu image
    if (!pro.initialize(graphics,0,0,0, &protagonist))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Character"));

	// menu image
    if (!bitch.initialize(graphics,0,0,0, &badbitch))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing The Bitch"));

	if (!orb.initialize(graphics,0,0,0, &bborb))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Character"));

	// menu image
    if (!scythe.initialize(graphics,0,0,0, &proscythe))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing The Bitch"));

    // initialize DirectX font
    // 18 pixel high Arial
    if(dxFont->initialize(graphics, 18, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

    //menu.setDegrees(300);
    //menu.setScale(0.002861f);

    //message = "\n\n\nUtilizes Object Oriented C++ and DirectX\n\n";
    //message += "Sprites with Transparency\n\n";
    //message += "Xbox 360 Controller Input\n\n";
    //message += "Collision Detection Supported:\n";
    //message += "     - Circular (Distance)\n";
    //message += "     - Axis-aligned bounding box\n";
    //message += "     - Rotated bounding box\n";
    //message += "     - Rotated bounding box and circle\n\n";
    //message += "XACT Audio\n\n";
    //message += "Sprite and DirectX Text\n\n";
    //message += "Tile Based Graphics\n\n";
    //message += "TCP/IP and UDP/IP Network Support\n\n";
    //messageY = GAME_HEIGHT;

    return;
}

void Level7::update()
{
    //if(menu.getDegrees() > 0)
    //{
    //    menu.setDegrees(menu.getDegrees() - frameTime * 120);
    //    menu.setScale(menu.getScale() + frameTime * 0.4f);
    //}
    //else if(messageY > -500)
    //{
    //    menu.setDegrees(0);
    //    menu.setY(menu.getY() - frameTime * 50);
    //    messageY -= frameTime * 50;
    //}
    //else    // start over
    //{
    //    menu.setDegrees(300);
    //    menu.setScale(0.002861f);
    //    menu.setY(0);
    //    messageY = GAME_HEIGHT;
    //}
}

void Level7::ai()
{}

void Level7::collisions()
{}

void Level7::render()
{
    graphics->spriteBegin();                // begin drawing sprites
    
	wall.draw();

	pro.setX(0);
	pro.setY(200);
	pro.draw();

	scythe.setX(100);
	scythe.setY(210);
	scythe.draw();

	bitch.setX(400);
	bitch.setY(0);
	bitch.draw();

	orb.setX(575);
	orb.setY(25);
	orb.draw();

    dxFont->setFontColor(graphicsNS::ORANGE);
    dxFont->print(message,20,(int)messageY);

    graphics->spriteEnd();                  // end drawing sprites
}

void Level7::releaseAll()
{
    dxFont->onLostDevice();
    wallpaper.onLostDevice();
    Game::releaseAll();
    return;
}

void Level7::resetAll()
{
    wallpaper.onResetDevice();
    dxFont->onResetDevice();
    Game::resetAll();
    return;
}
