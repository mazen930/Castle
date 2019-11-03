#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Battle.h"
#include "GUI\GUI.h"
#include <irrKlang.h>

using namespace irrklang;
//Main class that manages everything in the application.
class ApplicationManager
{

private:
	
	GUI *pGUI;
	Battle* pGameBattle ;
	ISoundEngine* pSound;

public:	
	ApplicationManager(); 
	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType WaitUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	void UpdateInterface()const;

	GUI* GetGUI() const; //Return pointer to the GUI
	Battle* GetBattle()const; //Return pointer to the Battle
	ISoundEngine* GetSound()const;

	~ApplicationManager();
};

#endif