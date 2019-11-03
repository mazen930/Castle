#include "Tower.h"
#include "../Defs.h"
#include "../Enemies/shielded_fighter.h"
#include "../Enemies/fighter.h"
#include "../Enemies/paver.h"
#include "../DataStructures/tuple.h"
#include "../Battle.h"
#include "../public_functions.h"
#include "../Enemies/Enemy.h"
#include<irrKlang.h>
using namespace irrklang;

Tower::Tower()
{
	reset();
}

void Tower::reset()
{
	damage=0;
	unPavedMeters = MaxDistance/2;
	ActiveNum = 0;
	KilledNum = 0;
}

void Tower::SetMaxHealth(double h)
{
	if(h > 0)
		MaxHealth = h;
	else
		MaxHealth = 0; 
}

void Tower::set_fp(double f)
{
	firepower=(f>0)?f:1;
}

void Tower::set_Attack_num(int n)
{
	attackNum=(n>0)?n:1;
}

void Tower::set_unpaved_meteres(int m)
{
	unPavedMeters=(m>=0 && m<=MaxDistance-MinDistance)?m:MaxDistance/2;
}

void Tower::set_region(REGION r)
{
	reg=r;
}

void Tower::set_ActiveNum(int num)
{
	if (num < 0)
		ActiveNum = 0;
	ActiveNum = num;
}

double Tower::getCurrentHealth() const
{
	return MaxHealth-damage;
}

double Tower::get_damage()const
{
	return damage;
}

string Tower::get_region()const
{
	if(reg==REGION::A_REG)
		return "A";
	if(reg==REGION::B_REG)
		return "B";
	if(reg==REGION::C_REG)
		return "C";
	if(reg==REGION::D_REG)
		return "D";
}

REGION Tower::getRegion()const
{
	return reg;
}

int Tower::get_unpaved_meters()const
{
	return unPavedMeters;
}

int Tower::getActiveNum()const
{
	return ActiveNum;
}

int Tower::get_killed_enemies_num()const
{
	return KilledNum;
}

bool Tower::isDestroyed()const
{
	return (MaxHealth==damage);
}

List<Enemy*>&Tower::get_shielded()
{
	return shielded;
}

List<Enemy*>&Tower::get_rest()
{
	return Rest;
}

void Tower::pave(int meters)
{
	unPavedMeters = meters;
	if(unPavedMeters < MinDistance)
		unPavedMeters = MinDistance;
}

void Tower::receive_damage(double x)
{
	if(damage+x <= MaxHealth)  damage+=x;
	else   damage=MaxHealth;
}

void Tower::Activate(Enemy*in)
{
	switch (in->getType())
	{

	case SHIELDED_FIGHTER:
		shielded.push_back(in);
		break;
	case DRAGON:
		shielded.push_back(in);
		break;
	default:
		Rest.push_back(in);
		break;
	}
	ActiveNum++;
}

void Tower::move(Tower* nextUnDestroyed)
{
	List<Enemy*>::iterator Rest_it = Rest.begin();
	List<Enemy*>::iterator shielded_it = shielded.begin();
	while (Rest_it != Rest.end())
	{
		(*Rest_it)->Move(unPavedMeters);
		++Rest_it;
	}
	while (shielded_it != shielded.end())
	{
		bool flag = true;
		flag = (*shielded_it)->Move(unPavedMeters);
		if (!flag)
		{
			(*shielded_it)->set_region(nextUnDestroyed->getRegion());
			nextUnDestroyed->Activate(*shielded_it);
			shielded.erase((shielded_it));
			ActiveNum--;
		}
		else
			++shielded_it;
	}
}

void Tower::healEnemies(double hpow, int hDist)
{
	const int range = 1;	//healer range (Enemies in her range will be healed)
	List<Enemy*>::iterator it = Rest.begin();
	EnemyType typ;
	int dist;
	while(it != Rest.end())
	{
		typ = (*it)->getType();
		dist = (*it)->getDistance();
		if(typ != HEALER)	//the healers cannot heal themselves
		{
			if(dist >= hDist-range && dist <= hDist+range)
				(*it)->heal(hpow);
		}
		++it;
	}

	it = shielded.begin();
	while(it != shielded.end())
	{
		dist = (*it)->getDistance();
		if(dist >= hDist-range && dist <= hDist+range)
			(*it)->heal(hpow);
		++it;
	}
}

void Tower::enemiesAttackTower( ISoundEngine* pSound)
{
	List<Enemy*>::iterator it = Rest.begin();
	while (it != Rest.end())
	{
		(*it)->Attack(this, pSound);
		++it;
	}

	it = shielded.begin();
	while (it != shielded.end())
	{
		(*it)->Attack(this, pSound);
		++it;
	}
}

void Tower::killEnemy(List<Enemy*>::iterator& it, int timeStep, bool shldd, Battle* pBattle, ISoundEngine* pSound)
{
	if(pSound)
		(*it)->death_sound(pSound);
	int FD = (*it)->get_time_first_shot() - (*it)->getArrTime();
	int S = (*it)->getID();
	int KD = timeStep - (*it)->get_time_first_shot();
	int LT = FD + KD;
	Tuple<int, int, Tuple<int, int ,int>> e(timeStep, FD, Tuple<int, int ,int>(S, KD, LT));
	pBattle->addKilledEnemy(e);

	pBattle->killEnemy(*it);

	if(shldd)
		shielded.erase(it);
	else
		Rest.erase(it);
	
	KilledNum++;
	ActiveNum--;
}

bool Tower::towerAttackEnemies(int timeStep, Battle* pBattle, ISoundEngine* pSound)
{
	if(shielded.isempty() && Rest.isempty())
		return true;

	List<Enemy*>::iterator it = shielded.begin();
	for (it; it != shielded.end(); it++)
	{
		(*it)->calcPriority();
	}

	shielded.sort(desc);

	it = shielded.begin();
	int i=0;
	double dmg;
	while (it != shielded.end() && i<attackNum)
	{
		if( !(*it)->wasShot() )
		{
			(*it)->set_time_first_shot(timeStep);
			(*it)->setWasShot();
		}
		dmg = firepower/( (*it)->getDistance()*shielded_fighter::k );
		(*it)->decrement_health(dmg);
		if( (*it)->isKilled() )
		{
			killEnemy(it, timeStep, true, pBattle, pSound);
		}
		else
			++it;
		i++;
	}

	it = Rest.begin();
	while (it != Rest.end() && i<attackNum)
	{
		if( !(*it)->wasShot() )
		{
			(*it)->set_time_first_shot(timeStep);
			(*it)->setWasShot();
		}
		dmg = firepower/( (*it)->getDistance()*fighter::k );
		(*it)->decrement_health(dmg);
		if( (*it)->isKilled() )
		{
			killEnemy(it, timeStep, false, pBattle, pSound);
		}
		else
			++it;
		i++;
	}
	if(shielded.isempty() && Rest.isempty())
		return true;
	return false;
}

void Tower::moveEnemies_to(REGION reg , List<Enemy*>& R , List<Enemy*>& S,int unpaved_meteres)
{
	List<Enemy*>::iterator it = Rest.begin();
	while(it != Rest.end())
	{
		(*it)->set_region(reg);
		if((*it)->getDistance()<unpaved_meteres)
			(*it)->SetDistance(unpaved_meteres);
		R.push_back((*it));
		++it;
	}
	it = shielded.begin();
	while(it != shielded.end())
	{
		(*it)->set_region(reg);
		if((*it)->getDistance()<unpaved_meteres)
			(*it)->SetDistance(unpaved_meteres);
		S.push_back((*it));
		++it;
	}
	R.sort(asc);
	S.sort(desc);
	clearEnemies();
}

void Tower::clearEnemies()
{
	Rest.clear();
	shielded.clear();
	ActiveNum = 0;
}
