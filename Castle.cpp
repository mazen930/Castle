#include "Castle.h"
#include "../Enemies/Enemy.h"

Castle::Castle()
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		switch(i)
		{
		case 0:
			Towers[i].set_region(REGION::A_REG);
			break;
		case 1:
			Towers[i].set_region(REGION::B_REG);
			break;
		case 2:
			Towers[i].set_region(REGION::C_REG);
			break;
		case 3:
			Towers[i].set_region(REGION::D_REG);
			break;
		default:
			return;
		}
	}
}


void Castle::SetTowersMaxHealth(double h)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetMaxHealth(h);
	}
}

void Castle::SetTowersPower(double TP)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].set_fp(TP);
	}
}

void Castle::getUnPvdMtrs(int& a, int& b, int& c, int&d)const
{
	a = Towers[0].get_unpaved_meters();
	b = Towers[1].get_unpaved_meters();
	c = Towers[2].get_unpaved_meters();
	d = Towers[3].get_unpaved_meters();
}

void Castle::towersAreDestroyed(bool& a, bool& b, bool& c, bool& d)const
{
	a = Towers[0].isDestroyed();
	b = Towers[1].isDestroyed();
	c = Towers[2].isDestroyed();
	d = Towers[3].isDestroyed();
}

bool Castle::enemiesAttackTowers(queue<Enemy*>*q, ISoundEngine* pSound)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		if(!Towers[i].isDestroyed())
		{
			Towers[i].enemiesAttackTower(pSound);
			if(Towers[i].isDestroyed())
			{
				if(pSound)
					pSound->play2D("Sound\\tower_destroyed.wav");
				int j = (i+1) % NoOfRegions;
				while(i!=j)
				{
					if(!Towers[j].isDestroyed())
					{
						Towers[j].set_ActiveNum(Towers[j].getActiveNum() + Towers[i].get_rest().size() + Towers[i].get_shielded().size());
						Towers[i].moveEnemies_to((REGION)(j) ,Towers[j].get_rest(), Towers[j].get_shielded(),Towers[j].get_unpaved_meters());
						change_Regions(q,(REGION)(i),(REGION)(j));
						break;
					}
					j = (j+1) % NoOfRegions;
				}
			}
		}
	}
	for(int i = 0; i < NoOfRegions; i++)
		if(!Towers[i].isDestroyed())
			return false;
	return true;
}

void Castle::change_Regions(queue<Enemy*>*inactiveEnemies,REGION from,REGION to)
{
	queue<Enemy*>temp;
	while(!inactiveEnemies->isempty())
	{
		Enemy*e=inactiveEnemies->peekFront();
		if(e->getRegion() == from)
			e->set_region(to);
		temp.enqueue(e);
		inactiveEnemies->dequeue();
	}
	while(!temp.isempty())
	{
		inactiveEnemies->enqueue(temp.peekFront());
		temp.dequeue();
	}
}

bool Castle::towersAttackEnemies(int timeStep, Battle* pBattle, ISoundEngine* pSound)
{
	bool over = true;
	for (int i = 0; i < NoOfRegions; i++)
	{
		if( !Towers[i].towerAttackEnemies(timeStep, pBattle, pSound) )
			over = false;
	}
	return over;
}

void Castle::SetAttackNum(int num)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].set_Attack_num(num);
	}
}

void Castle::reset()
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].reset();
	}
}

void Castle::Activate_Enemy(Enemy*E)
{
	Towers[E->getRegion()].Activate(E);
}

void Castle::move_All()
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		int nextUnDestroyed = i, count = 0;
		do
		{
			nextUnDestroyed = (nextUnDestroyed+1) % NoOfRegions;
			count++;
		} while (Towers[nextUnDestroyed].isDestroyed() && count<=NoOfRegions);

		Towers[i].move(&Towers[nextUnDestroyed]);	//move all enemies
	}
}

const Tower* Castle::get_towers()const
{
	return Towers;
}

void Castle::clearEnemies()
{
	for (int i = 0 ;i < NoOfRegions; i++)
	{
		Towers[i].clearEnemies();
	}
}