#include "Dragon.h"
#include"..\Castle\Tower.h"
#include"..\Battle.h"

Dragon::Dragon(int id, EnemyType typ, REGION r_region, double h, double fp, int arr_t, int RP, int sp)
	:Enemy(id, typ, r_region, h, fp, arr_t, RP, sp)
{
}

void Dragon::set_priority_constants(double c1, double c2, double c3)
{
	C1 = c1; C2 = c2; C3 = c3;
}

void Dragon::calcPriority()
{
	priority = (firepower*C1) / Distance + C3*CurrentHealth + C2 / (remaining_time_to_shoot + 1);
}

bool Dragon::Move(int unpaved_meteres)
{
	if(Distance == MinDistance)	//go to the next valid region when reaching min distance from castle at certain region
	{
		Distance = MaxDistance;
		return false;
	}
	if (Distance-speed > MinDistance)
		Distance -= speed;
	else
		Distance = MinDistance;
	return true;
}

void Dragon::Attack(Tower * T, ISoundEngine* pSound)
{
	if (!can_shoot())
	{
		remaining_time_to_shoot--;
		return;
	}
	if(pSound)
		pSound->play2D("Sound/dragon_attack.mp3");
	double dmg = k*firepower / Distance;
	T->receive_damage(dmg);
	set_remaining_time();
}

void Dragon::deploy_sound(ISoundEngine* pSound)
{
	pSound->play2D("Sound\\dragon_deploy.wav");
}

void Dragon::death_sound(ISoundEngine* pSound)
{
	pSound->play2D("Sound/dragon_death.mp3");
}

Dragon::~Dragon()
{
}
double Dragon::C1 = 1;	//intial values for C1, C2, C3
double Dragon::C2 = 1;
double Dragon::C3 = 1;