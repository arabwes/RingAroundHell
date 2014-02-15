#ifndef BG_H
#define BG_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
namespace BgNS
{
	const int WIDTH=650;//with of each frame 
	const int HEIGHT=720;//height of each frame
	const float	  SPEED = 100;
	enum DIRECTION {NONE, LEFT, RIGHT};//facing derections
}

class bg : public Entity

{
protected:
	BgNS::DIRECTION direction;
	Image BG;	
public:
	bg();
	virtual void draw();
	bool initialize(Game *gamePtr,int width,int height,TextureManager *tectureM);
	void update(float frameTime);
	void direc(BgNS::DIRECTION dir) {direction = dir;}

};
#endif