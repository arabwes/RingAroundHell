#include "VisualSin.h"
#include "constants.h"

VisualSin::VisualSin()
{
	velocity.x = rand() % 30 * 100 * 0.035;
}
VisualSin::~VisualSin()
{

}
void VisualSin::Move(float frameTime)
{
	
	if (spriteData.x < 0 - spriteData.width)
		spriteData.x = GAME_WIDTH;
	spriteData.x -= velocity.x * frameTime;     // move ship along X 
	//spriteData.y++;     // move ship along Y
}

