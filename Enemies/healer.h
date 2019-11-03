#pragma once
#include "Enemy.h"
#include "..\Castle\Tower.h"

class healer : public Enemy
{
public:
	static const int k = 1;

	healer(int id, EnemyType typ, REGION r_region, double h, double fp, int arr_t, int RP, int sp);
	virtual void Attack(Tower*, ISoundEngine* pSound = NULL);
	virtual void deploy_sound(ISoundEngine* pSound);
	virtual void death_sound(ISoundEngine* pSound);
	~healer();
};