#include "Bum.h"

Bum::Bum() :Entity()
{
	spriteData.x=BumNS::X;
	spriteData.y=BumNS::Y;
	spriteData.width=BumNS::WIDTH;
	spriteData.height=BumNS::HEIGHT;
	velocity.x=0;
	velocity.y=0;
	gravity=BumNS::GRVETY;
	frameDelay=BumNS::BUM_ANIMATION_DELAY;
	startFrame= BumNS::BUM_START_FRAME;
	endFrame=BumNS::BUM_END_FRAME;
	currentFrame=startFrame;
	dead=false;
	moving=false;
	movingL=false;
	movingR=false;
	jump=false;
}
bool Bum::initialize(Game *gamePtr,int width,int height,int ncols,
	TextureManager *textureM)
{
	bum.initialize(gamePtr->getGraphics(),width,height,ncols,textureM);
	bum.setFrames(BumNS::BUM_START_FRAME,BumNS::BUM_END_FRAME);
	bum.setCurrentFrame(BumNS::BUM_START_FRAME);
	bum.setFrameDelay(BumNS::BUM_ANIMATION_DELAY);
	return (Entity::initialize(gamePtr,width,height,ncols,textureM));
}

void Bum::draw()
{
	Image::draw();
}

void Bum::update(float frameTime)
{
	if(moving&&movingL)
	{
		velocity.x -= BumNS::SPEED * frameTime;
	}
	if(moving&&movingR)
	{
		velocity.x += BumNS::SPEED * frameTime;
	}
	if(movingL){spriteData.x -= frameTime * velocity.x;}
	if(movingR){spriteData.x += frameTime * velocity.x;}
	if(jump==true)
	{
			spriteData.y=spriteData.y-velocity.y*frameTime;
			if(spriteData.y<250)
			{
				jump=false;
			}
	}
	if(jump==false&&spriteData.y<350)
	{
		spriteData.y=spriteData.y+velocity.y*frameTime;
	}
	
	if (spriteData.x > GAME_WIDTH/2)           
	    spriteData.x = GAME_WIDTH/2-1;       
	else if (spriteData.x < GAME_WIDTH-GAME_WIDTH)  
	    spriteData.x = 0+1;
	}
void Bum::setmoving(bool m)
{
	moving=m;
}

void Bum::setDirectL(bool L)
{
	movingL=L;
}
void Bum::setDirectR(bool R)
{
	movingR=R;
}
void Bum::setPlayerdead(bool d)
{
	dead=d;
}
void Bum::setjump(bool j)
{
	jump=j;
}
	bool Bum::getjump()
	{
		return jump;
	}