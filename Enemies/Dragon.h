#pragma once
#include"Enemy.h"
class Dragon:public Enemy
{
	static double C1, C2, C3;

public:
	static const int k = 2;
	Dragon(int id, EnemyType typ, REGION r_region, double h, double fp, int arr_t, int RP, int sp);
	static void set_priority_constants(double c1, double c2, double c3);
	virtual void calcPriority();
	virtual bool Move(int unpaved_meteres);
	virtual void Attack(Tower* T, ISoundEngine* pSound = NULL);
	virtual void deploy_sound(ISoundEngine* pSound);
	virtual void death_sound(ISoundEngine* pSound);
	~Dragon();
};

