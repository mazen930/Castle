#include "ApplicationManager.h"

#include "Actions\LoadAction.h"
#include "Actions\interActive.h"
#include "Actions\StepbyStep.h"
#include "Actions\Silent.h"
#include "Actions\generateFiles.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;
	pGameBattle = new Battle;
	pSound = createIrrKlangDevice();
}

ActionType ApplicationManager::WaitUserAction() const
{
	//Ask the input to get the action from the user.
	return pGUI->WaitUserAction();
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{

		case LOAD:
			pAct = new LoadAction(this);
			break;
		case INTERACTIVE_MODE:
			pAct = new interActive(this);
			break;
		case STEP_BY_STEP_MODE:
			pAct = new StepbyStep(this);
			break;
		case SILENT_MODE:
			pAct = new Silent(this);
			break;
		case GENERATE:
			pAct = new generateFiles(this);
			break;
		case RETURN:
			pGameBattle->reset();
			UpdateInterface();
			pGUI->DrawMenu();
			pGUI->ClearStatusBar();
			break;
		case EXIT:
			return;
		default:
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}

void ApplicationManager::UpdateInterface()const
{
	pGUI->ClearBattleArea();
	pGameBattle->DrawPavedArea(pGUI);
	pGameBattle->DrawCastle(pGUI);
	pGameBattle->DrawEnemies(pGUI);
}

GUI* ApplicationManager::GetGUI() const
{	return pGUI; }

Battle* ApplicationManager::GetBattle()const
{
	return pGameBattle;
}

ISoundEngine* ApplicationManager::GetSound()const
{
	return pSound;
}

////////////////////////////////////////////////////////////////////////////////////
//Destructor

ApplicationManager::~ApplicationManager()
{
	delete pGUI;
	delete pGameBattle;
	pSound->drop();
}
