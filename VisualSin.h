//VisualSin.h Objects in the game

#include "Button.h"

class VisualSin : public Button
{
public:
	VisualSin();
	~VisualSin();
	void Move(float frameTime);
};