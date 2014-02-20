#include "Character.h"

Character::Character()
{
	health		= 20;		
	attack		= 24;		
	magic		= 16;		
	special		= 30;		
	evasion		= 60;		
	guard		= 0.75;		
	resistance	= 0.44;	
	speed		= 15;	
}

Character::~Character()
{
	
}

Character::Character(int hP, int atk, int mgc, int spcl, int evsn, double grd, double rst, int spd)
{
	health		= hP; 
	attack		= atk; 
	magic		= mgc; 
	special		= spcl; 
	evasion		= evsn; 
	guard		= grd; 
	resistance	= rst; 
	speed		= spd; 
}

void Character::SetHP	(int H)		{ health		= H; }
void Character::SetAtk	(int A)		{ attack		= A; }
void Character::SetMag	(int M)		{ magic			= M; }
void Character::SetSpcl	(int S)		{ special		= S; }
void Character::SetEvsn	(int E)		{ evasion		= E; }
void Character::SetGrd	(double G)	{ guard			= G; }
void Character::SetRst	(double R)	{ resistance	= R; }
void Character::SetSpd	(int S)		{ speed			= S; }

int		Character::GetHP()		{ return health;		}
int		Character::GetAtk()		{ return attack;		}
int		Character::GetMag()		{ return magic;			}
int		Character::GetSpcl()	{ return special;		}
int		Character::GetEvsn()	{ return evasion;		}
double	Character::GetGrd()		{ return guard;			}
double	Character::GetRst()		{ return resistance;	}
int		Character::GetSpd()		{ return speed;			}
