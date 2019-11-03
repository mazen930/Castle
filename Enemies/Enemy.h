#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include <irrKlang.h>
using namespace irrklang;

class Tower;	//forward declaration

// Enemy is the base class of each type of enemy
// Enemy is an abstract class.
class Enemy
{
	const int ID;         //Each enemy has a unique ID (sequence number)
	color Clr;	    //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;  //Region of this enemy
	const EnemyType type;
	bool was_shot;	//to indecate if an enemy was shot before by a tower or not
	int time_first_shot;
	const double MaxHealth;		//health loaded from the file
	const int arrival_time;
	

protected:
	
	int Distance;	//Horizontal distance between enemy & the tower of its region
	                //Always positive (ranges from 2 to 60)
	const int Reload_Period;
	double CurrentHealth;
	const double firepower;
	const int speed;
	int remaining_time_to_shoot;
    double priority;
	void set_remaining_time();
	
	//
public:
	Enemy(int id, EnemyType typ, REGION r_region, double h, double fp, int arr_t, int RP,int sp);
	virtual ~Enemy();

	void decrement_health(double);
	bool isKilled()const;
	bool wasShot()const;
	void setWasShot();
	
	void set_time_first_shot(int);
	void SetDistance(int d);
	void set_region(REGION);
	void heal(double h);

	int getArrTime()const;
	int get_time_first_shot()const;
	int getID()const ;
	int getDistance() const;
	EnemyType getType()const;
	color getColor() const;
	REGION getRegion() const;
	bool can_shoot()const;
	bool operator< (const Enemy&);
	///////////////
	// Virtual Functions: ----------------

	virtual void calcPriority();
	//return false only if a dragon reached min distance in a region
    virtual bool Move(int unpaved_meteres);	    //All enemies can move
	virtual void Attack(Tower* T, ISoundEngine* pSound = NULL) = 0;	//All enemies can attack (attacking is paving or shooting)
	virtual void deploy_sound(ISoundEngine* pSound) = 0;
	virtual void death_sound(ISoundEngine* pSound) = 0;
};

