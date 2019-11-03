#include "Enemy.h"
#include "..\Castle\Tower.h"

Enemy::Enemy(int id, EnemyType typ, REGION r_region, double h, double fp, int arr_t, int RP,int sp)
	:ID(id), type(typ), firepower(fp), arrival_time(arr_t), Reload_Period(RP), speed(sp), MaxHealth(h)
{
	Region = r_region;
	Distance = MaxDistance;
	CurrentHealth = MaxHealth;
	remaining_time_to_shoot=0;
	was_shot = false;
	priority = arrival_time;

	switch (typ)
	{
	case PAVER:
		Clr = DARKBLUE;
		break;
	case FIGHTER:
		Clr = DARKOLIVEGREEN;
		break;
	case SHIELDED_FIGHTER:
		Clr = ORANGERED;
		break;
	case HEALER:
		Clr = HOTPINK;
		break;
	case DRAGON:
		Clr = BLACK;
		break;
	default:
		break;
	}
}

void Enemy::decrement_health(double x)
{
	if(CurrentHealth-x>0) CurrentHealth-=x;
	else  CurrentHealth=0;
}

void Enemy::set_time_first_shot(int tfs)
{
	time_first_shot=(tfs>0)?tfs:1;
}
void Enemy::set_region(REGION r)
{
	Region=r;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

void Enemy::heal(double h)
{
	if(CurrentHealth+h > MaxHealth)
		CurrentHealth = MaxHealth;
	else
		CurrentHealth += h;
}

void Enemy::set_remaining_time()
{
	remaining_time_to_shoot = Reload_Period;
}

EnemyType Enemy::getType()const
{
	return type;
}

color Enemy::getColor() const
{
	return Clr;
}

REGION Enemy::getRegion() const
{
	return Region;
}

int Enemy::getDistance() const
{
	return Distance;
}

bool Enemy::isKilled()const
{
	return (CurrentHealth == 0);
}

bool Enemy::wasShot()const
{
	return was_shot;
}

void Enemy::setWasShot()
{
	was_shot = true;
}

int Enemy::getArrTime()const
{
	return arrival_time;
}

int Enemy::getID()const
{
	return ID;
}

int Enemy::get_time_first_shot()const
{
	return time_first_shot;
}

bool Enemy::can_shoot()const
{
	return (remaining_time_to_shoot==0);
}

bool Enemy::operator<(const Enemy& E)
{
	return (priority<=E.priority);
}

bool Enemy::Move(int unpaved_meteres)
{
	if (Distance-speed > unpaved_meteres)
		Distance-=speed;
	else
		Distance=unpaved_meteres;
	return true;
}

void Enemy::calcPriority()
{
	priority = arrival_time;
}

Enemy::~Enemy()
{
}