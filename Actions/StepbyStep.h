#pragma once
#include "Action.h"
class StepbyStep:public Action
{
public:
	StepbyStep(ApplicationManager *pApp);
	virtual void Execute();
	~StepbyStep();
};

