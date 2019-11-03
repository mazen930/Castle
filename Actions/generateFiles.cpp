#include "generateFiles.h"
#include "../ApplicationManager.h"
#include <time.h>

generateFiles::generateFiles(ApplicationManager *pApp):Action(pApp)
{
	path = "tests/";
}

void generateFiles::Execute()
{
	srand(time(NULL));
	GUI* pGUI = pManager->GetGUI();
	string name;

	pGUI->PrintMessage("Generate random File: Please Enter the File name to generate, or press \"Escape\" to cancel ");
	name = pGUI->GetString();

	if(name == "")		//the user pressed Esc
	{
		pGUI->PrintMessage("Load is canceled!");
		return ;
	}
	
	path+=name;
	path+=".txt";

	out.open(path);
	if(out.is_open())
	{
		int enemiesNum = rand()%MaxEnemyCount +1;	//integer number from 1 to max enemy count
		int TH = rand()%1000 + enemiesNum;
		int N = rand()%(enemiesNum/4) +1;
		int TP = rand()%50 +(enemiesNum)/4;
		out<<TH<<'\t'<<N<<'\t'<<TP<<'\n';

		double C1 = ((double)rand()/RAND_MAX);	//double number from 0 to 1
		double C2 = ((double)rand()/RAND_MAX);
		double C3 = ((double)rand()/RAND_MAX);
		out<<C1<<'\t'<<C2<<'\t'<<C3<<'\n';

		int currentEnemiesCount = 0;
		int S = 1;
		for (int time = 1; currentEnemiesCount<enemiesNum; time++)
		{

			int propability = rand()%7;			//probability of how many enemies can arrive at this time step
												//(from 0 to 7)

			if(currentEnemiesCount+propability > enemiesNum)
				propability = enemiesNum - currentEnemiesCount;

			for (int i = 0; i < propability; i++)
			{
				int TYP = rand()%5 ;
				int H = rand()%91 +10;	//from 10 to 100
				int POW = rand()%50 +1;
				if(TYP == PAVER)  
					POW = rand()%5 +1;
				int RLD = rand()%7 +1;
				char R = rand()%NoOfRegions +'A';
				int speed = rand()%10 +1;
				out<<S<<'\t'<<TYP<<'\t'<<time<<'\t'<<H<<'\t'<<POW<<'\t'<<RLD<<'\t'<<R<<'\t'<<speed<<'\n';
				S++;
			}
			currentEnemiesCount += propability;
		}
		out<<-1;
		pGUI->PrintMessage("The file was generated successfully, you can load it now from load icon");
		out.close();
	}
	else
		pGUI->PrintMessage("Error: could't find the file. Please check if the file name is correct, then try again");
}


generateFiles::~generateFiles()
{
}
