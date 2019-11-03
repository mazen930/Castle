#include "interActive.h"
#include "../ApplicationManager.h"

interActive::interActive(ApplicationManager *pApp):Action(pApp)
{
}

void interActive::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	Battle * pGameBattle=pManager->GetBattle();

	if(pGameBattle->inactive_isEmpty())							//check whether inactive queue is empty or not
	{
		pGUI->PrintMessage("Please load a file first");
		return;
	}
	ISoundEngine* pSound = pManager->GetSound();
	ActionType actType;
	pGUI->PrintMessage("InterActive Mode:keep pressing till the Battle is Over");
	pSound->play2D("Sound\\alliance_jingle_v2.wav",true);
	int time=1;
	bool over=false;
	bool flag = true;
	while(!over)
	{
		actType = pGUI->WaitUserAction();
		if (actType == EXIT)
		{
			pSound->stopAllSounds();
			pGameBattle->reset();
			pManager->UpdateInterface();
			pGUI->ClearStatusBar();
			return;
		}
		pGameBattle->Activate(time, pSound);
		over=pGameBattle->simulate(time, pSound);
		pGameBattle->PrintInformation(pGUI);
		pGUI->PrintMessage("Time Step = "+to_string(time),false,0,1055);
		pManager->UpdateInterface();
		time++;
	}
	pSound->stopAllSounds();
	bool x = pGameBattle->Output(FileName);
	if (x)
	{
		pGUI->PrintMessage("WIN", true, -30, 490, 100);
		pSound->play2D("Sound\\Cheering-SoundBible.com-1115515042.wav");
	}
	else
	{
		pGUI->PrintMessage("LOSS", true, -30, 460, 100);
		pSound->play2D("Sound\\fail-trombone-01.wav");
	}
	pGameBattle->clearEnemies();	//in case of any enemy wasn't deleted
	pManager->UpdateInterface();
}

interActive::~interActive()
{
}
