
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

	frameDelay = 0;
	startFrame = 0;
	endFrame = 0;
	currentFrame = startFrame;
	visible = true;
}

Card::~Card()
{
	
}

string Card::UpdateFace(bool ShowFace)
{
	if(ShowFace)
		return fileName;
		//Texture = LoadTexture(FileName, TransColor);
	else
		return facedownFileName;
		//Texture = LoadTexture(FacedownFileName, TransColor);
}
int Card::GetValue()
{
	return value;
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
	spriteData.x = X;
	spriteData.y = Y;
}