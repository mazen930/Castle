#include "LoadAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include "..\Enemies\shielded_fighter.h"
#include "..\Enemies\fighter.h"
#include "..\Enemies\paver.h"
#include "..\Enemies\healer.h"
#include "..\Enemies\Dragon.h"

LoadAction::LoadAction(ApplicationManager * pApp):Action(pApp)
{
	path="tests/";
}

void LoadAction::Execute()
{
	GUI* pGUI = pManager->GetGUI();

	pGUI->PrintMessage("Load a File: Please Enter the File name to Load, or press \"Escape\" to cancel ");
	FileName = pGUI->GetString();

	if(FileName == "")		//the user pressed Esc
	{
		pGUI->PrintMessage("Load is canceled!");
		return ;
	}
	
	path+=FileName;
	path+=".txt";

	Battle* pBattle = pManager->GetBattle();

	pBattle->reset();	//in case of the user loaded a file, then loaded another file


	InputFile.open(path);
	if( InputFile.is_open() )
	{
		double TH, TP;
		int N;
		InputFile>>TH>>N>>TP;
		if(TH<=0 || N<=0 ||TP<=0)
		{
			pGUI->PrintMessage("Error: The file is corrupted");
			InputFile.close();
			return;
		}
		pBattle->setTowersConstants(TH, TP, N);
		pManager->UpdateInterface();

		double C1, C2, C3;
		InputFile>>C1>>C2>>C3;
		if(C1<0 || C2<0 ||C3<0)
		{
			pGUI->PrintMessage("Error: The file is corrupted");
			InputFile.close();
			return;
		}
		shielded_fighter::set_priority_constants(C1, C2, C3);

		int S, TYP, T, RLD,speed ; 
		char R;
		double H, POW;
		REGION region;
		Enemy* pEnemy;
		queue<Enemy*>Enemies;

		while (true)
		{
			InputFile>>S;
			if(S == -1)
				break;
			InputFile>>TYP>>T>>H>>POW>>RLD>>R>>speed;
			if(InputFile.fail() || T<0 || H<=0 || POW<=0 ||RLD<0 ||speed<=0)
			{
				pGUI->PrintMessage("Error: The file is corrupted");
				InputFile.close();
				return;
			}

			toupper(R);
			switch (R)
			{
			case 'A':
				region = A_REG;
				break;
			case 'B':
				region = B_REG;
				break;
			case 'C':
				region = C_REG;
				break;
			case 'D':
				region = D_REG;
				break;

			default:
				pGUI->PrintMessage("Error: The file is corrupted");
				InputFile.close();
				return;
			}
			
			switch (TYP)
			{
			case PAVER:
				pEnemy = new paver(S, (EnemyType)TYP, region, H, POW, T, RLD, speed); 
				break;
			case FIGHTER:
				pEnemy = new fighter(S, (EnemyType)TYP, region, H, POW, T, RLD, speed);
				break;
			case SHIELDED_FIGHTER:
				pEnemy = new shielded_fighter(S, (EnemyType)TYP, region, H, POW, T, RLD, speed);
				break;
			case HEALER:
				pEnemy = new healer(S, (EnemyType)TYP, region, H, POW, T, RLD, speed);
				break;
			case DRAGON:
				pEnemy = new Dragon(S, (EnemyType)TYP, region, H, POW, T, RLD, speed);
				break;
			default:
				pGUI->PrintMessage("Error: The file is corrupted");
				InputFile.close();
				return;
			}
			Enemies.enqueue(pEnemy);
		}
		InputFile.close();
		pGUI->PrintMessage("The file is loaded successfully");
		pBattle->setInactiveEnemies(Enemies);
	}
	else
		pGUI->PrintMessage("Error: could't find the file. Please check if the file name is correct, then try again");
}
