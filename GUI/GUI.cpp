#include "GUI.h"

//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	pWind = new window(WindWidth+15,WindHeight,0,0);
	pWind->ChangeTitle("The Castle Game");

	DrawMenu();

	ClearStatusBar();
	ClearBattleArea();
	DrawPavedAreas(MaxDistance/2,MaxDistance/2,MaxDistance/2,MaxDistance/2);
	DrawCastle(false, false, false, false);
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::GetPointClicked(Point &P) const
{
	pWind->FlushMouseQueue();
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}

//////////////////////////////////////////////////////////////////////////////////////////
//This function reads the position where the user clicks to determine the desired action
ActionType GUI::determineAction(int X, int Y)const
{
	//[0] No Click
	if(Y == -1 && X == -1)
		return BLANK_AREA;

	//[1] User clicks on the battle or status bar area
	if (Y >= MenuBarHeight && Y < WindHeight)
		return BLANK_AREA;


	//[2] If user clicks on the Menubar
	else
	{
		//Check which Menu item was clicked
		//==> This assumes that menu items are lined up horizontally <==
		int ClickedItemOrder = (X / MenuItemWidth);
		//Divide x coord of the point clicked by the menu item width (int division)
		//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
		if(interfaceMode == MODE_NORMAL)
		{
			switch (ClickedItemOrder)
			{
		
			case ITM_INTERACTIVE_MODE: return INTERACTIVE_MODE;
			case ITM_STEP_BY_STEP_MODE: return STEP_BY_STEP_MODE;
			case ITM_SILENT_MODE: return SILENT_MODE;
			case ITM_LOAD: return LOAD;
			case ITM_GENERATE: return GENERATE;
			case ITM_EXIT: return EXIT;

			default: return BLANK_AREA;	//a click on empty area in the menu bar

			}
		}
		else
		{
			switch (ClickedItemOrder)
			{
			case ITM_INCREASE_SPEED: return INCREASE_SPEED;
			case ITM_DECREASE_SPEED: return DECREASE_SPEED;
			case ITM_RETURN: return RETURN;
			default: return BLANK_AREA;
			}
		}
	}
}

ActionType GUI::WaitUserAction() const
{
	pWind->FlushMouseQueue();		//Empty the mouse queue
	int X,Y;
	pWind->WaitMouseClick(X, Y);	//Get the coordinates of the user click

	return determineAction(X,Y);
}

ActionType GUI::GetUserAction()const
{
	int X,Y;
	pWind->GetMouseClick(X, Y);	//Get the coordinates of the user click

	return determineAction(X,Y);
}

/////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const 
{
	pWind->FlushKeyQueue();		//before doing anything, flush the key queue first
	string Label;
	char Key;
	keytype kt;
	unsigned int i=0;
	while(1)
	{
		kt=pWind->WaitKeyPress(Key);
		if(kt == ESCAPE )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		
		if(kt == ARROW)
		{
			if(Key == 4)	//left arrow key is pressed
				if( i>0 )
					i--;
			if(Key == 6)	//right arrow key is pressed
				if ( i<Label.size() )
					i++;
		}

		if(kt == ASCII)
		{
			if(Key == 13 )	//ENTER key is pressed
				return Label;

			if((Key == 8) && (i >= 1))	//BackSpace is pressed
				Label.erase( Label.begin() + (--i) );
			else if(Key == 8)	//if BackSpace is pressed and there is nothing to delete,just do not do anything
				continue;
			else
				Label.insert( Label.begin()+(i++) , Key );
		}

		PrintMessage(Label);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg,bool x,int y ,int z,int font) const	//Prints a message on status bar
{
	if(x)
		ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(DARKRED);
	pWind->SetFont(font, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10+z, WindHeight - (int) (StatusBarHeight)-y, msg); 

	
}
void GUI::DrawStatusRegions()const
{
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(600,WindHeight-StatusBarHeight,600,WindHeight);
	pWind->DrawLine(0,WindHeight-StatusBarHeight/2-35,1200,WindHeight-StatusBarHeight/2-35);

}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawMenu()
{
	interfaceMode = MODE_NORMAL;

	//Draw a White rectangle to clear the toolbar
	pWind->SetPen(WHITE);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0,0,WindWidth,MenuBarHeight);

	//You can draw the menu icons any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in enum MenuItem
	string MenuItemImages[MENU_ITM_COUNT];
	MenuItemImages[ITM_INTERACTIVE_MODE] = "images\\MenuItems\\interactive.jpg";
	MenuItemImages[ITM_STEP_BY_STEP_MODE] = "images\\MenuItems\\step_by_step.jpg";
	MenuItemImages[ITM_SILENT_MODE] = "images\\MenuItems\\mute.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\Menu_Load.jpg";
	MenuItemImages[ITM_GENERATE] = "images\\MenuItems\\random.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Exit.jpg";


	//Draw menu item one image at a time
	for(int i=0; i<MENU_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);

	//Draw a line under the menu bar
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, MenuBarHeight, WindWidth, MenuBarHeight);	

}

void GUI::DrawSpeedMenu()
{
	interfaceMode = MODE_SPEED;

	//Draw a White rectangle to clear the toolbar
	pWind->SetPen(WHITE);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0,0,WindWidth,MenuBarHeight);

	string MenuItemImages[SPEED_MENU_ITM_COUNT];
	MenuItemImages[ITM_INCREASE_SPEED] = "images\\MenuItems\\increase_speed.jpg";
	MenuItemImages[ITM_DECREASE_SPEED] = "images\\MenuItems\\decrease_speed.jpg";
	MenuItemImages[ITM_RETURN] = "images\\MenuItems\\return.jpg";

	//Draw menu item one image at a time
	for(int i=0; i<SPEED_MENU_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);

	//Draw a line under the menu bar
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, MenuBarHeight, WindWidth, MenuBarHeight);	
}

////////////////////////////////////////////////////1//////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(WHITE, 3);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearBattleArea() const
{
	// Clearing the battle area	
	pWind->SetPen(LIGHTSKYBLUE, 3);
	pWind->SetBrush(LIGHTSKYBLUE);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawPavedAreas(int a,int b,int c,int d)const
{
	int A_paved=(MaxDistance+1-a)*(EnemyWidth+1), B_paved=(MaxDistance+1-b)*(EnemyWidth+1),
		C_paved=(MaxDistance+1-c)*(EnemyWidth+1),D_paved=(MaxDistance+1-d)*(EnemyWidth+1);
	const color PavedColor = KHAKI ;
	//Drawing A Region
	pWind->SetPen(PavedColor);
	pWind->SetBrush(PavedColor);
	pWind->DrawRectangle(0, MenuBarHeight, A_paved, (WindHeight - StatusBarHeight)/2+25);
	//Drawing B Region
	pWind->SetPen(PavedColor);
	pWind->SetBrush(PavedColor);
	pWind->DrawRectangle(WindWidth-B_paved, MenuBarHeight, WindWidth, (WindHeight - StatusBarHeight)/2+25);
	//Drawing C Region
	pWind->SetPen(PavedColor);
	pWind->SetBrush(PavedColor);
	pWind->DrawRectangle(WindWidth-C_paved, (WindHeight-StatusBarHeight)/2+25,WindWidth , WindHeight - StatusBarHeight);
	//Drawing D Region
	pWind->SetPen(PavedColor);
	pWind->SetBrush(PavedColor);
	pWind->DrawRectangle(0, (WindHeight-StatusBarHeight)/2+25, D_paved, (WindHeight - StatusBarHeight));



}
///////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawCastle(bool a, bool b, bool c, bool d) const
{
	int L = CastleWidth / 2;
	// 1- Drawing the image of the castle
	pWind->DrawImage("images\\castle2.jpg",CastleStartX, CastleStartY,CastleWidth,CastleEndY-CastleStartY);
	// 2- Drawing the 2 brown crossed lines (for making 4 regions)
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, YHalfBattleArea, WindWidth, YHalfBattleArea);
	pWind->DrawLine(WindWidth/2, MenuBarHeight, WindWidth/2, WindHeight-StatusBarHeight);

	// 3- Drawing the 2 white crossed lines (inside the castle)
	pWind->SetPen(WHITE);
	pWind->DrawLine(WindWidth/2, YHalfBattleArea - CastleWidth/2, WindWidth/2, YHalfBattleArea + CastleWidth/2);
	pWind->DrawLine(WindWidth/2 - CastleWidth/2, YHalfBattleArea, WindWidth/2 + CastleWidth/2, YHalfBattleArea);

	// 4- Drawing the 4 white squares inside the castle (one for each tower)
	pWind->SetPen(WHITE);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(CastleStartX, CastleStartY , CastleStartX + 30, CastleStartY + 30);
	pWind->DrawRectangle(CastleStartX , CastleEndY - 30, CastleStartX + 30 , CastleEndY );
	pWind->DrawRectangle(CastleEndX - 30, CastleStartY , CastleEndX , CastleStartY + 30);
	pWind->DrawRectangle(CastleEndX - 30, CastleEndY - 30, CastleEndX , CastleEndY );

	// 5- Writing the letter of each region (A, B, C, D)
	pWind->SetPen(BROWN);
	pWind->SetFont(25, BOLD , BY_NAME, "Arial");
	pWind->DrawString(CastleStartX +7 , CastleStartY +5 ,(a ? "X" : "A"));
	pWind->DrawString(CastleEndX-23, CastleStartY+4,(b ? "X" : "B"));
	pWind->DrawString(CastleEndX-23, CastleEndY-24,(c ? "X" : "C"));
	pWind->DrawString(CastleStartX +7, CastleEndY-25, (d ? "X" : "D"));

	// 6- Drawing the 2 vertical brown lines at distance 60
	// that is because some rounding errors may occur if you choose another width and height for the window
	// so we draw 2 vertical lines at distance 60 to mark it
	pWind->SetPen(BROWN);
	pWind->DrawLine(CastleStartX - MaxDistance*EnemyWidth - MaxDistance -1, MenuBarHeight,
		CastleStartX - MaxDistance*EnemyWidth - MaxDistance -1, WindHeight-StatusBarHeight);
	pWind->DrawLine(CastleEndX + MaxDistance*EnemyWidth + MaxDistance +1, MenuBarHeight,
		CastleEndX + MaxDistance*EnemyWidth + MaxDistance +1, WindHeight-StatusBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawEnemy(const Enemy & E, int YPos) const       // It's a private function
{
	color clr = E.getColor();
	REGION Region = E.getRegion();
	int Distance = E.getDistance();

	int x, y, refX, refY;
	//First calculate x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	switch (Region)
	{
	case A_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case B_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the enemy
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	pWind->DrawRectangle(x, y, x + EnemyWidth, y + EnemyHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw a list of enemies and ensure there is no overflow in the drawing*/
// To use this function, you must prepare its input parameters as specified
// [Input Parameters]:
//    enemies [ ] : array of enemy pointers (ALL enemies from all regions in one array)
//    size : the size of the array (total no. of enemies)
void GUI::DrawEnemies(Enemy* enemies[], int size) const
{
	//draw enemies at each region 
	for(int region = A_REG; region <= D_REG; region++)
	{
		int CountEnemies = 0;	// count Enemies at the same distance to draw them vertically if they are <= 15 enemy 
		                        // else print number of enemy in the region
		bool draw=true;
		for(int distance = MaxDistance ; distance >= MinDistance ; distance--)
		{
			CountEnemies = 0;

			for(int i = 0 ; i < size ; i++)
			{	
				if(enemies[i]->getDistance() == distance && enemies[i]->getRegion() == region)
				{
					CountEnemies++;
				}
			}
			if(CountEnemies > 15)
			{
				draw=false;
				break;
			}
		}
		if(draw)
		{
			for( int distance = MaxDistance ; distance > 1 ; distance-- )
			{
				CountEnemies=0;

				for(int i = 0 ; i < size ; i++)
				{	
					if(enemies[i]->getDistance() == distance && enemies[i]->getRegion() == region)
					{
						DrawEnemy(*(enemies[i]), CountEnemies + 1);
						CountEnemies++;
					}
				}
			}
		}
		else // print message maximum reached in this region
		{
			PrintMessage("Cannot Draw Enemies of region " + to_string(region+1) + 
				"! More than" + to_string(MaxVerticaEnemies) + " enemies are in the same region and distance..");
			Sleep(1000); // because may be more than one region has drawing overflow
		}
	}
}
