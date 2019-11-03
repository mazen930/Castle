#include "ApplicationManager.h"

int main()
{
	ActionType ActType;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;

	do
	{		
		//Read user action
		ActType = AppManager.WaitUserAction();

		//Exexute the action
		AppManager.ExecuteAction(ActType);

	}while(ActType != EXIT);
	
	return 0;
}

