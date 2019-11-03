#ifndef LOAD_ACTION_H
#define LOAD_ACTION_H

#include"Action.h"
#include<string>
#include<fstream>
using namespace std;

class LoadAction: public Action
{
	string path;
	ifstream InputFile;

public:
	LoadAction(ApplicationManager *pApp);

	virtual void Execute();
};


#endif