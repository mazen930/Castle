#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "Tower.h"
#include "..\DataStructures\queue.h"
#include <irrKlang.h>
using namespace irrklang;

class Battle;	//forward declaration

class Castle
{
	Tower Towers[NoOfRegions];

public:
	Castle();
	void SetTowersMaxHealth(double h);
	void SetTowersPower(double TP);
	void SetAttackNum(int num);
	void getUnPvdMtrs(int& a, int& b, int& c, int&d)const;
	void towersAreDestroyed(bool& a, bool& b, bool& c, bool& d)const;

	bool enemiesAttackTowers(queue<Enemy*>*q, ISoundEngine* pSound = NULL);	//makes each enemy attack the tower in his region
	bool towersAttackEnemies(int timeStep, Battle* pBattle, ISoundEngine* pSound = NULL); //returns true if all active enemies is killed
	void Activate_Enemy(Enemy*);
	void change_Regions(queue<Enemy*>*inactive,REGION from,REGION to);
	void reset();
	void move_All();
	const Tower* get_towers()const;
	void clearEnemies();
};
