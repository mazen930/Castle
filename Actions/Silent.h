#pragma once
#include"Action.h"
class Silent:public Action
{
public:
	Silent(ApplicationManager *pApp);
	virtual void Execute();
	~Silent();
};

