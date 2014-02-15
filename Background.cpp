#include "background.h"
	bg::bg()
	{
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
		switch(direction)
		{
		case BgNS::LEFT:

			break;
		case BgNS::RIGHT:
			break;
		}

	}