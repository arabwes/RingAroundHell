#include "Character.h"

Character::Character()
{
	Health		= 20;		
	Attack		= 24;		
	Magic		= 16;		
	Special		= 30;		
	Evasion		= 60;		
	Guard		= 0.75;		
	Resistance	= 0.44;	
	Speed		= 15;	
}

Character::~Character()
{
	
}

Character::Character(int HP, int Atk, int Mgc, int Spcl, int Evsn, double Grd, double Rst, int Spd)
{
	Health		= HP; 
	Attack		= Atk; 
	Magic		= Mgc; 
	Special		= Spcl; 
	Evasion		= Evsn; 
	Guard		= Grd; 
	Resistance	= Rst; 
	Speed		= Spd; 
}

void Character::SetHP	(int H)		{ Health		= H; }
void Character::SetAtk	(int A)		{ Attack		= A; }
void Character::SetMag	(int M)		{ Magic			= M; }
void Character::SetSpcl	(int S)		{ Special		= S; }
void Character::SetEvsn	(int E)		{ Evasion		= E; }
void Character::SetGrd	(double G)	{ Guard			= G; }
void Character::SetRst	(double R)	{ Resistance	= R; }
void Character::SetSpd	(int S)		{ Speed			= S; }

int		Character::GetHP()		{ return Health;		}
int		Character::GetAtk()		{ return Attack;		}
int		Character::GetMag()		{ return Magic;			}
int		Character::GetSpcl()	{ return Special;		}
int		Character::GetEvsn()	{ return Evasion;		}
double	Character::GetGrd()		{ return Guard;			}
double	Character::GetRst()		{ return Resistance;	}
int		Character::GetSpd()		{ return Speed;			}
