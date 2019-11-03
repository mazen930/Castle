#pragma once
#include "Enemy.h"
#include "..\Castle\Tower.h"

class paver : public Enemy
{
public:
	static const int k = 1;

	paver(int id, EnemyType typ, REGION r_region, double h, double fp, int arr_t, int RP,int sp);
	virtual bool Move(int unpaved_meteres);
	virtual void Attack(Tower*, ISoundEngine* pSound = NULL);
	virtual void deploy_sound(ISoundEngine* pSound);
	virtual void death_sound(ISoundEngine* pSound);
	~paver();
};

