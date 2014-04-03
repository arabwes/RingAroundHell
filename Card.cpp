
#include "Card.h"

Card::Card(string TempFName, string TempName, string TempSuit, int TempVal, int TempNum, string TempFile, string TempFacedown)
{
	fullName = TempFName;
	name = TempName;
	suit = TempSuit;
	value = TempVal;
	number = TempNum;
	Selected = false;
	fileName = TempFile;
	facedownFileName = TempFacedown;
	isFaceDown = true;
	cols = 1;
	spriteData.width = 71;
	spriteData.height = 96;

	texManFront = new TextureManager();
	texManBack = new TextureManager();

	frameDelay = 0;
	startFrame = 0;
	endFrame = 0;
	currentFrame = startFrame;
	visible = true;
}

Card::~Card()
{
	
}

void Card::Initialize(Graphics *graphics, Game* game)
{
	if (!texManFront->initialize(graphics,fileName))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing card textures"));
	if (!texManBack->initialize(graphics,facedownFileName))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing card textures"));

	if(!this->initialize(game, 71, 96, 1, texManFront))
	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing card texture"));


}

void Card::UpdateFace(bool showFace)
{
	if (showFace)
	{
		this->setTextureManager(texManFront);
	}
	else
	{
		this->setTextureManager(texManBack);
	}
}
int Card::GetValue()
{
	return value;
}

void Card::SetValue(int tVal)
{
	value = tVal;
}

string Card::GetSuit()
{
	return suit;
}

string Card::GetFullName()
{
	return fullName;
}
string Card::GetName()
{
	return name;
}
int Card::GetNum()
{
	return number;
}
void Card::Reposition(int X, int Y)
{
	newX = X;
	newY = Y;
}
void Card::CardUpdate()
{
	if(spriteData.x < newX)
	{
		spriteData.x++;
	}
	else if(spriteData.x > newX)
	{
		spriteData.x--;
	}

	if(spriteData.y < newY)
	{
		spriteData.y++;
	}
	else if(spriteData.y > newY)
	{
		spriteData.y--;
	}

}