#include "paver.h"


paver::paver(int id, EnemyType typ, REGION r_region, double h, double fp, int arr_t, int RP,int sp)
	:Enemy(id, typ, r_region, h, fp, arr_t, RP,sp)
{
}

bool paver::Move(int unpaved_meteres)
{
	if(can_shoot())
	{
		Distance-=firepower;
		if(Distance < MinDistance)
			Distance=MinDistance;
		set_remaining_time();
	}
	else
	{
		Enemy::Move(unpaved_meteres);
		remaining_time_to_shoot--;
	}
	return true;
}

void paver::Attack(Tower* T, ISoundEngine* pSound)
{
	if(remaining_time_to_shoot==Reload_Period && pSound)
		pSound->play2D("Sound/paver_attack.mp3");
	T->pave(min(T->get_unpaved_meters(),Distance));
}

void paver::deploy_sound(ISoundEngine* pSound)
{
	pSound->play2D("Sound/paver_deploy.wav");
}

void paver::death_sound(ISoundEngine* pSound)
{
	pSound->play2D("Sound/paver_death.mp3");
}

paver::~paver()
{
}
