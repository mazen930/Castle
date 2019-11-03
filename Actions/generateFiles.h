#pragma once
#include "Action.h"
#include <fstream>

class generateFiles:public Action
{
	string path;
	ofstream out;
public:
	generateFiles(ApplicationManager *pApp);
	virtual void Execute();
	~generateFiles();
};

