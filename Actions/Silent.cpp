#include "Silent.h"
#include "..\ApplicationManager.h"
#include <string>
#include <cstring>
#include <iostream>
#include<Windows.h>
#include<mmsystem.h>
using namespace std;

Silent::Silent(ApplicationManager *pAp):Action(pAp)
{
}

void Silent::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	Battle * pGameBattle=pManager->GetBattle();
	if(pGameBattle->inactive_isEmpty())							//check whether inactive queue is empty or not
	{
		pGUI->PrintMessage("Please load a file first");
		return;
	}
	int time=1;
	bool over=false;
	while(!over)
	{
		pGameBattle->Activate(time);
		over=pGameBattle->simulate(time);
		time++;
	}
	bool x = pGameBattle->Output(FileName);
	if(x)
		pGUI->PrintMessage("WIN",true,-30,490,100);
	else
		pGUI->PrintMessage("LOSS",true,-30,460,100);
	pGameBattle->clearEnemies();	//in case of any enemy wasn't deleted
}

Silent::~Silent()
{
}
