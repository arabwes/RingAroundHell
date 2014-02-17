#ifndef _CHARACTER_H           // Prevent multiple definitions if this 
#define _CHARACTER_H           // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <sstream>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "textDX.h"
#include "entity.h"

class Character : public Entity
{
private:
	int		Health;
	int		Attack;
	int		Magic;
	int		Special;
	int		Evasion;
	double	Guard;
	double	Resistance;
	int		Speed;

public:
	Character();
	virtual ~Character();
	Character(int,int,int,int,int,double,double,int);

	void SetHP		(int);
	void SetAtk		(int);
	void SetMag		(int);
	void SetSpcl	(int);
	void SetEvsn	(int);
	void SetGrd		(double);
	void SetRst		(double);
	void SetSpd		(int);
	
	int		GetHP();
	int		GetAtk();
	int		GetMag();
	int		GetSpcl();
	int		GetEvsn();
	double	GetGrd();
	double	GetRst();
	int		GetSpd();
};

#endif