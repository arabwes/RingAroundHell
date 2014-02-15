#include"Button.h"


Button::Button()
{
}

Button::~Button()
{
}

Button::Button(int level) : Entity()
{
	lvl = level;
	clicked = false;
	spriteData.width = spriteData.height = 100;
	spriteData.rect.bottom = spriteData.rect.right = 100;
	cols = 1;
	frameDelay = 0;
	startFrame = 0;
	endFrame = 0;
	currentFrame = startFrame;
	radius = 29;
	visible = true;
}

bool Button::Update()
{
	if(input->getMouseLButton())
	{ 
		if(input->getMouseX() > spriteData.x &&		//If Button was clicked then
			input->getMouseX() < spriteData.x + spriteData.rect.right &&	//clicked flag is changed and 
			input->getMouseY() < spriteData.y + spriteData.rect.bottom &&		//click event is called
			input->getMouseY() > spriteData.y)
		{
			input->setMouseLButton(false);
			clicked = true;
			return true;
		}
	}
	return false;
}

int Button::GetBtnLevel()
{
	return lvl;
}