#pragma once

#define NoOfRegions 4
#define MaxDistance  60         // the maximum distance between any enemy and its tower
#define MinDistance  2          // the minimum distance between any enemy and its tower
#define MaxVerticaEnemies  15   // the maximum number of enemies that can be drawn
		                        // if they are in the same region and same distance
								// (will be drawn vertical to each other)
#define MaxEnemyCount 300       // the maximum number of enemies the application can work on

//The four regions: A, B, C , and D
enum REGION
{	
	A_REG,
	B_REG,
	C_REG,
	D_REG
};

enum GUI_MODE
{
	MODE_NORMAL,
	MODE_SPEED
};

enum MenuItem
{
	//Note: menu icons are ordered here as they appear in menu
	//If you want to change the menu icons order, change the order here
	ITM_INTERACTIVE_MODE,
	ITM_STEP_BY_STEP_MODE,
	ITM_SILENT_MODE,
	ITM_LOAD,
	ITM_GENERATE,
	ITM_EXIT,

				
	MENU_ITM_COUNT	//no. of menu icons ==> This should be the last line in this enum
};

enum SpeedMenuItem
{
	ITM_DECREASE_SPEED,
	ITM_INCREASE_SPEED,
	ITM_RETURN,

	SPEED_MENU_ITM_COUNT
};

enum ActionType //The actions supported (you can add more if needed)
{
	INTERACTIVE_MODE,
	STEP_BY_STEP_MODE,
	SILENT_MODE,
	LOAD,			//Load a from a file
	GENERATE,
	EXIT,
	INCREASE_SPEED,
	DECREASE_SPEED,
	RETURN,
	BLANK_AREA
};

const enum EnemyType
{
	PAVER,
	FIGHTER,
	SHIELDED_FIGHTER,
	HEALER,
	DRAGON
};

struct Point
{
	int x;
	int y;
	Point(int a=0, int b=0)	//constructor
	{ x=a;	y=b;	}
};