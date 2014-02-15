#ifndef Button_H           // Prevent multiple definitions if this 
#define Button_H           // file is included in more than one place

#include"entity.h"

class Button : public Entity
{
	bool clicked;
	int lvl;
public:
	Button();
	Button(int level);
	int GetBtnLevel();
	~Button();
	bool Update();
};



#endif