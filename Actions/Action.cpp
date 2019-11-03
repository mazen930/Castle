#include "Action.h"

Action::Action(ApplicationManager *pApp)
{
	pManager = pApp;
}

string Action::FileName = "";	//intialization