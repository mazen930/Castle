#pragma once

#include "Castle\Castle.h"
#include "DataStructures\queue.h"
#include "DataStructures\tuple.h"
#include "DataStructures\List.h"
#include "GUI\GUI.h"
#include <irrKlang.h>
using namespace irrklang;

// it is the controller of the project
class Battle
{
private:
	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function
	queue<Enemy*>inactiveEnemies;
	List<Tuple<int, int, Tuple<int, int, int>>> killedInfo;
public:
	Battle();
	bool simulate(int timeStep, ISoundEngine* pSound = NULL);
	void AddEnemy(Enemy* Ptr);
	void DrawEnemies(const GUI* pGUI);
	const Castle * GetCastle()const;
	void DrawPavedArea(const GUI* pGUI)const;
	void DrawCastle(const GUI* pGUI)const;
	void Activate(int time, ISoundEngine* pSound = NULL);
	void killEnemy(Enemy* e);
	void addKilledEnemy(const Tuple<int, int, Tuple<int, int, int>> &e);
	int get_EnemyCount()const;
	queue<Enemy*>& get_inactive_Enemies();
	void setInactiveEnemies(const queue<Enemy*>& Equeue);
	void setTowersConstants(double TH, double TP, int N);
	bool inactive_isEmpty()const;
	void PrintInformation(const GUI* pGUI)const;
	void clearEnemies();
	void reset();
	bool Output(const string& fileName);
	~Battle();
};

