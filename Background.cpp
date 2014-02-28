#include "background.h"
	bg::bg()
	{
	move=false;
	spriteData.x=BgNS::X;
	spriteData.y=BgNS::Y;
	}
	void bg::draw()
	{
		 Image::draw();
	}
	bool bg::initialize(Game *gamePtr,int width,int height,TextureManager *tectureM)
	{
		 BG.initialize(gamePtr->getGraphics(), width, height,0, tectureM);
		  return(Entity::initialize(gamePtr, width, height, 0, tectureM));
	}
	void bg::update(float frameTime)
	{
		if(move==true)
	{
		velocity.x -= BgNS::SPEED * frameTime;
	}
		else 
			velocity.x=0;
	spriteData.x += frameTime * velocity.x;
	if (spriteData.x > GAME_WIDTH)           
	    spriteData.x = -BgNS::WIDTH;       
	else if (spriteData.x < -BgNS::WIDTH)  
	    spriteData.x = GAME_WIDTH;    
	}

void bg::setmoving(bool m)
{
	move=m;
}