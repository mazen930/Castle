#ifndef ACTION_H
#define ACTION_H

#include "..\DEFS.h"
#include <string>
using namespace std;

class ApplicationManager; //forward class declaration


//Base class for all possible actions
class Action
{
protected:
	ApplicationManager *pManager;	//Actions needs AppMngr to do their job
	static string FileName;

public:

	Action(ApplicationManager *pApp);	//constructor

	//Execute action (code depends on action type)
	virtual void Execute() = 0;

};
#endif