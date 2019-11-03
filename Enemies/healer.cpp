#include "healer.h"


healer::healer(int id, EnemyType typ, REGION r_region, double h, double fp, int arr_t, int RP,int sp)
	:Enemy(id, typ, r_region, h, fp, arr_t, RP, sp)
{
}

void healer::Attack(Tower* T, ISoundEngine* pSound)
{
	if(!can_shoot())
	{
		remaining_time_to_shoot--;
		return;
	}
	if(pSound)
		pSound->play2D("Sound/healer_attack.mp3");
	T->healEnemies(firepower,Distance);
	set_remaining_time();
}

void healer::deploy_sound(ISoundEngine* pSound)
{
	pSound->play2D("Sound/healer_deploy.mp3");
}

void healer::death_sound(ISoundEngine* pSound)
{
	pSound->play2D("Sound/healer_death.mp3");
}

healer::~healer()
{
}
