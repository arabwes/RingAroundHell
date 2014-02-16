#include "Bum.h"

Bum::Bum() :Entity()
{
	spriteData.x=BumNS::X;
	spriteData.y=BumNS::Y;
	spriteData.width=BumNS::WIDTH;
	spriteData.height=BumNS::HEIGHT;
	velocity.x=0;
	velocity.y=0;
	frameDelay=BumNS::BUM_ANIMATION_DELAY;
	startFrame= BumNS::BUM_START_FRAME;
	endFrame=BumNS::BUM_END_FRAME;
	currentFrame=startFrame;
	moving=false;
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
	
	if(moving)
	{
		if(movingL){velocity.x -= BumNS::SPEED * frameTime;}
		if(movingR){velocity.x += BumNS::SPEED * frameTime;}
	}
	else
	{
		velocity.x=0;
	}
	spriteData.x += frameTime * velocity.x; 
	//spriteData.y += frameTime * velocity.y;
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