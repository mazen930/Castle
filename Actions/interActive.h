#pragma once
#include"Action.h"
class interActive:public Action
{
public:
	interActive(ApplicationManager *pApp);
	virtual void Execute();
	~interActive();
};

