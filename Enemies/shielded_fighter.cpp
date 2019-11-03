#include "shielded_fighter.h"


shielded_fighter::shielded_fighter(int id, EnemyType typ, REGION r_region, double h, double fp, int arr_t, int RP,int sp)
	:Enemy(id, typ, r_region, h, fp, arr_t, RP,sp)
{
}

void shielded_fighter::set_priority_constants(double c1, double c2, double c3)
{
	C1 = c1; C2 = c2; C3 = c3;
}

void shielded_fighter::calcPriority()
{
	priority=(firepower*C1)/Distance + C3*CurrentHealth + C2/(remaining_time_to_shoot+1);  //we decrement remaining_time_to_shoot with every step and when it reaches 0 we return it back
}

void shielded_fighter::Attack(Tower* T, ISoundEngine* pSound)
{
	if (!can_shoot())
	{
		remaining_time_to_shoot--;
		return;
	}
	if(pSound)
		pSound->play2D("Sound/shielded_attack.mp3");
	double dmg = k*firepower/Distance;
	T->receive_damage(dmg);
	set_remaining_time();
}

void shielded_fighter::deploy_sound(ISoundEngine* pSound)
{
	pSound->play2D("Sound/shielded_deploy.wav");
}

void shielded_fighter::death_sound(ISoundEngine* pSound)
{
	pSound->play2D("Sound/shielded_death.mp3");
}

shielded_fighter::~shielded_fighter()
{
}

double shielded_fighter::C1 = 1;	//intial values for C1, C2, C3
double shielded_fighter::C2 = 1;
double shielded_fighter::C3 = 1;