#include "StepbyStep.h"
#include "..\ApplicationManager.h"
#include<irrKlang.h>
using namespace irrklang;
StepbyStep::StepbyStep(ApplicationManager *pApp)
: Action(pApp)
{
}

void StepbyStep::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	Battle * pGameBattle = pManager->GetBattle();
	if (pGameBattle->inactive_isEmpty())							//check whether inactive queue is empty or not
	{
		pGUI->PrintMessage("Please load a file first ");
		return;
	}
	pGUI->DrawSpeedMenu();
	ActionType actType;
	pGUI->PrintMessage("Step by step mode:On");
	ISoundEngine* pSound = pManager->GetSound();
	pSound->play2D("Sound\\alliance_jingle_v2.wav",true);
	int time = 1;
	double speed = 1;
	bool over = false;
	while (!over)
	{
		actType = pGUI->GetUserAction();
		switch (actType)
		{
		
		case RETURN:
			pSound->stopAllSounds();
			pGameBattle->reset();
			pManager->UpdateInterface();
			pGUI->DrawMenu();
			pGUI->ClearStatusBar();
			return;

		case INCREASE_SPEED:
			speed *= 2;
			break;
		case DECREASE_SPEED:
			speed /= 2;
			break;
		default:
			break;
		}
		pGameBattle->Activate(time, pSound);
		over = pGameBattle->simulate(time, pSound);
		pGameBattle->PrintInformation(pGUI);
		pGUI->PrintMessage("Time Step = "+to_string(time),false,0,1055);
		pManager->UpdateInterface();
		time++;
		Sleep(1000/speed);
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


StepbyStep::~StepbyStep()
{
}
