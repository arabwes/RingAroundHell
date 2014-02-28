#ifndef BUM_H
#define BUM_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace BumNS
{
	const int WIDTH=100;//with of each frame 
	const int HEIGHT=100;//height of each frame
	const int X = 50;//screen location
	const int Y = 50;//screen location
	const int TEXTURE_COLS=6;//number of columns in the sprit sheet
	const int BUM_START_FRAME=0;//ship start frame 
	const int BUM_END_FRAME=21;//ship end frame
	//const float ENEMY_SLOW= 15;//enemy slow 
	const float BUM_ANIMATION_DELAY=0.2f;// time between frames 
	const float	SPEED = 100;// speed of the player movement 
	const float MASS = 200.0f;// the mass of the player 
	const float JUMP_HEIGHT =200;// the jump hight of the player
	const float GRVETY=50;
	enum DIRECTION {NONE, LEFT, RIGHT,JUMPS};//facing derections
}
class Bum : public Entity
{
protected:
	bool jump;
	bool dead;
	bool moving;
	bool movingL;
	bool movingR;
	bool onGround;
	Image bum;
public:
	Bum();
	virtual void draw();
	virtual bool initialize(Game *gamePtr,int width,int height, int ncols,TextureManager *tectureM);

	void update(float frameTime);
	void impared();
	void unimp();

	void setPlayerdead(bool d);
	 void setmoving(bool m);
	void setDirectL(bool L);
	void setDirectR(bool R);
	void setjump(bool j);
	bool getjump();
	void setonground(bool b);
	bool getonground();
};
#endif
	
