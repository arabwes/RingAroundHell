#ifndef BG_H
#define BG_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
namespace BgNS
{
	const int X=0,Y=0;
	const int WIDTH=640;//with of each frame 
	const int HEIGHT=480;//height of each frame
	const float	  SPEED = 100;
	
}

class bg : public Entity

{
protected:
	Image BG;	
	bool move;
public:
	bg();
	virtual void draw();
	bool initialize(Game *gamePtr,int width,int height,TextureManager *tectureM);
	void update(float frameTime);
		void setmoving(bool m);
};
#endif