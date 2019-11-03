#pragma once
#include "../DataStructures/List.h"
#include "../Defs.h"
#include <irrKlang.h>
using namespace irrklang;

class Battle;	//forward declaration
class Enemy;	//forward declaration

class Tower
{
	double MaxHealth;	//health of the tower loaded from the file
	REGION reg;
	double firepower;
	int attackNum;			//number of enemies that the tower can attack each time step
	double damage;			
	int unPavedMeters;
	int ActiveNum;
	int KilledNum;
	List<Enemy*>shielded;	//shielded and dragon list
	List<Enemy*>Rest;		//paver, fighter and healer list
	void killEnemy(List<Enemy*>::iterator& it, int timeStep, bool shldd, Battle* pBattle, ISoundEngine* pSound = NULL);

public:
	Tower();
	void reset();

	void SetMaxHealth(double h);
	void set_fp(double);
	void set_Attack_num(int);
	void set_unpaved_meteres(int);
	void set_region(REGION);
	void set_ActiveNum(int num);

	double getCurrentHealth() const;
	double get_damage()const;
	string  get_region()const;
	REGION getRegion()const;
	int get_unpaved_meters()const;
	int getActiveNum()const;
	int get_killed_enemies_num()const;
	bool isDestroyed()const;
	List<Enemy*>&get_shielded();
	List<Enemy*>&get_rest();

	void pave(int meters);
	void receive_damage(double);
	void Activate(Enemy*);
	//move all enemies in this region, nextUnDestroyed is the next undestroyed tower to move dragon to
	void move(Tower* nextUnDestroyed);
	void healEnemies(double hpow, int hDist);
	void enemiesAttackTower(ISoundEngine* pSound = NULL);	//makes enemies in this region attack this tower
	//returns true when all enemies in this region is killed
	bool towerAttackEnemies(int timeStep, Battle* pBattle, ISoundEngine* pSound = NULL);
	void moveEnemies_to(REGION , List<Enemy*>& , List<Enemy*>&,int unpaved_meteres);
	void clearEnemies();
};

