#include "Battle.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include "public_functions.h"
using namespace std;

Battle::Battle()
{
	EnemyCount = 0;
}

void Battle::AddEnemy(Enemy* Ptr)
{
	if (EnemyCount < MaxEnemyCount) 
		BEnemiesForDraw[EnemyCount++] = Ptr;
	// Note that this function doesn't allocate any enemy objects
	// It only makes the first free pointer in the array
	// points to what is pointed to by the passed pointer Ptr
}

bool Battle::simulate(int t, ISoundEngine* pSound)
{
	BCastle.move_All();
	bool over = (BCastle.towersAttackEnemies(t, this, pSound) && inactive_isEmpty()) || 
		(BCastle.enemiesAttackTowers(&inactiveEnemies, pSound));
	return over;
}

void Battle:: killEnemy(Enemy* e)
{
	int i = 0;
	for (i = 0; i < EnemyCount; i++)
	{
		if( BEnemiesForDraw[i] == e )
			break;
	}
	delete BEnemiesForDraw[i];
	for(int j=i; j<EnemyCount-1; j++)
		BEnemiesForDraw[j] = BEnemiesForDraw[j+1];
	BEnemiesForDraw[EnemyCount] = nullptr;
	EnemyCount--;
}

void Battle::Activate(int time, ISoundEngine* pSound)
{
	while(!inactiveEnemies.isempty() && inactiveEnemies.peekFront()->getArrTime()<=time)
	{
		Enemy* E = inactiveEnemies.peekFront();
		if(pSound)
			E->deploy_sound(pSound);
		BCastle.Activate_Enemy(E);
		AddEnemy(E);
		inactiveEnemies.dequeue();
	}
}

void Battle::addKilledEnemy(const Tuple<int, int, Tuple<int, int, int>> &e)
{
	killedInfo.push_back(e);
}

void Battle::DrawEnemies(const GUI * pGUI)
{
	pGUI->DrawEnemies(BEnemiesForDraw, EnemyCount);
}

void Battle::DrawPavedArea(const GUI* pGUI)const
{
	int a,b,c,d;
	BCastle.getUnPvdMtrs(a, b, c, d);
	pGUI->DrawPavedAreas(a,b,c,d);
}

void Battle::DrawCastle(const GUI* pGUI)const
{
	bool a, b, c, d;
	BCastle.towersAreDestroyed(a, b, c, d);
	pGUI->DrawCastle(a, b, c, d);
}

const Castle * Battle::GetCastle()const
{
	return &BCastle;
}

void Battle::setInactiveEnemies(const queue<Enemy*>& Equeue)
{
	inactiveEnemies = Equeue;
}

void Battle::setTowersConstants(double TH, double TP, int N)
{
	BCastle.SetTowersMaxHealth(TH);
	BCastle.SetTowersPower(TP);
	BCastle.SetAttackNum(N);
}

queue<Enemy*>& Battle::get_inactive_Enemies()
{
	return inactiveEnemies;
}

int Battle::get_EnemyCount()const
{
	return EnemyCount;
}

bool Battle::inactive_isEmpty()const
{
	return (inactiveEnemies.isempty());
}

void Battle::PrintInformation(const GUI * pGUI)const
{
	const Castle* pCastle = GetCastle();
	const Tower* Towers = pCastle->get_towers();
	int cnt=0;
	int cnt2=0;
	pGUI->PrintMessage("");
	for(int i=0;i<NoOfRegions;i++)
	{
		if(i==2)
		{
			cnt=0;
			cnt2=600;
		}
		pGUI->PrintMessage("Tower "+Towers[i].get_region()+":",false,cnt,cnt2,12);
		cnt-=12;
		pGUI->PrintMessage("Health= "+to_string(Towers[i].getCurrentHealth())+
	    +"  Unpaved meters= "+to_string(Towers[i].get_unpaved_meters()),false,cnt,cnt2,12);
		cnt-=12;
		pGUI->PrintMessage("Active Enemies:"+to_string(Towers[i].getActiveNum()),false,cnt,cnt2,12);
		cnt-=12;
		pGUI->PrintMessage("Killed Enemies:"+to_string(Towers[i].get_killed_enemies_num()),false,cnt,cnt2,12);
		cnt-=20;
		pGUI->DrawStatusRegions();
	}
}

void Battle::clearEnemies()
{
	for (int i = 0; i < EnemyCount; i++)
	{
		delete BEnemiesForDraw[i];
		BEnemiesForDraw[i] = nullptr;
	}
	EnemyCount = 0;
	BCastle.clearEnemies();
	inactiveEnemies.clear();
}

void Battle::reset()
{
	clearEnemies();
	BCastle.reset();
}

bool Battle::Output(const string& fileName)
{
	killedInfo.sort(tuple_cmp);
	ofstream OutputFile;
	OutputFile.open("Output Files/"+fileName+".txt");
	double total_FD = 0;
	double total_KD = 0;
	int killed = killedInfo.size();
	int active = 0;
	int inactive = inactiveEnemies.get_count();
	OutputFile<<"KTS\t"<<"S\t"<<"FD\t"<<"KD\t"<<"LT\n";

	List<Tuple<int, int, Tuple<int, int, int>>>::iterator it = killedInfo.begin();
	while(!killedInfo.isempty())
	{
		int KTS = (*it).get_first();
		int S = (*it).get_third().get_first();
		int FD = (*it).get_second();
		int KD = (*it).get_third().get_second();
		int LT = (*it).get_third().get_third();
		OutputFile<<KTS<<'\t'<<S<<'\t'<<FD<<'\t'<<KD<<'\t'<<LT<<'\n';
		total_FD += FD;
		total_KD += KD;

		killedInfo.erase(it);
	}

	const Tower* towers = BCastle.get_towers();
	OutputFile<<"T1_Total_Damage\t"<<"T2_Total_Damage\t"<<"T3_Total_Damage\t"<<"T4_Total_Damage\n";
	for(int i=0;i<NoOfRegions;i++)
	{
		OutputFile<<to_string(towers[i].get_damage())<<"\t";
	}
	OutputFile<<endl;

	OutputFile<<"R1_Unpaved_Dist\t"<<"R2_Unpaved_Dist\t"<<"R3_Unpaved_Dist\t"<<"R4_Unpaved_Dist\t"<<endl;
	for(int i=0;i<NoOfRegions;i++)
	{
		OutputFile<<to_string(towers[i].get_unpaved_meters())<<"\t\t";
	}
	OutputFile<<endl;

	bool x=false;
	for(int i=0;i<NoOfRegions;i++)
	{
		if(towers[i].getCurrentHealth()>0)
			x=true;
		active += towers[i].getActiveNum();
	}

	if(x)
	{
		OutputFile<<"Game is Win"<<endl;
		OutputFile<<"Total Enemies = "<<to_string(killed)<<endl;
	}
	else
	{
		OutputFile<<"Game is Loss"<<endl;
		OutputFile<<"Killed Enemies = "<<to_string(killed)<<endl;
		OutputFile<<"Active Enemies = "<<to_string(active)<<endl;
		OutputFile<<"Inactive Enemies = "<<to_string(inactive)<<endl;

	}
	double avg_KD = 0; 
	double avg_FD = 0;
	if(killed!=0)
	{
		avg_FD = total_FD/killed;
		avg_KD = total_KD/killed;
	}

	OutputFile<<"Average First-Shot Delay = "<<to_string(avg_FD)<<endl;
	OutputFile<<"Average Kill Delay = "<<to_string(avg_KD)<<endl;
	return x;
}

Battle::~Battle()
{
	clearEnemies();
}
