#pragma once
#include "Enemy.h"
#include "..\Castle\Tower.h"

class shielded_fighter : public Enemy
{
	static double C1, C2, C3;
public:
	static const int k = 2;

	shielded_fighter(int id, EnemyType typ, REGION r_region, double h, double fp, int arr_t, int RP,int sp);
	virtual void calcPriority();
	static void set_priority_constants(double c1, double c2, double c3);
	virtual void Attack(Tower*, ISoundEngine* pSound = NULL);
	virtual void deploy_sound(ISoundEngine* pSound);
	virtual void death_sound(ISoundEngine* pSound);
	~shielded_fighter(void);
};
