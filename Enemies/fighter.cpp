#include "fighter.h"


fighter::fighter(int id, EnemyType typ, REGION r_region, double h, double fp, int arr_t, int RP,int sp)
	:Enemy(id, typ, r_region, h, fp, arr_t, RP,sp)
{
}

void fighter::Attack(Tower* T, ISoundEngine* pSound)
{
	if (!can_shoot())
	{
		remaining_time_to_shoot--;
		return;
	}
	if(pSound)
		pSound->play2D("Sound/fighter_attack.wav");
	double dmg = k*firepower/Distance;
	T->receive_damage(dmg);
	set_remaining_time();
}

void fighter::deploy_sound(ISoundEngine* pSound)
{
	pSound->play2D("Sound/fighter_deploy.mp3");
}

void fighter::death_sound(ISoundEngine* pSound)
{
	pSound->play2D("Sound/fighter_death.mp3");
}

fighter::~fighter()
{
}
