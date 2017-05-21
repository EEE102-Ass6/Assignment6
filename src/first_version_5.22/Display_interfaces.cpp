/*
* File      :Display_interfaces.cpp
* Author: Zhao zhihe£¨Kyrie£©
* ID number: 1405180
* Description: This file is the implemention file concerning to the displaying function.
* Change Logs:
* Date           Author          Notes
* 2017-05-16     Kyrie.Zhao      Design the basic display such as "show_welcom()"
* 2017-05-18     Kyrie.Zhao      Add the display of "system_show"
* 2017-05-19     Kyrie.Zhao      Implement the interfaces concering to the lower interfaces'display
* 2017-05-21     Kyrie.Zhao      Finish the display part.
* 2017-05-22     Kyrie.Zhao      Check and do final function testing part.
*/
#include <iostream>
#include "windows.h"
#include "Display_interfaces.h"
#include "Screen.h"
#include "Var_whole.h"

using namespace std;
void show_Welcome()
{
	int i;
	cout << "\n\n" << endl;
	cout << "   \t\t\t\tEnter [SPACE] to MAX/MINIMIZE the screen" << endl;
	cout << "\t\t\t£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤" << endl;
	for (i = 0; i < 3; i++)
	{
		cout << "\t\t\t£¤\t\t\t\t\t\t  £¤" << endl;
	}
	cout << "\t\t\t£¤¡ï¡¾  Welcom to BMW Taxi mangement system  ¡¿¡ï£¤" << endl;
	for (i = 0; i < 3; i++)
	{
		cout << "\t\t\t£¤\t\t\t\t\t\t  £¤" << endl;
	}
	cout << "\t\t\t£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤\n" << endl;	
	cout << "\t  a.Vehicle  b.Driver  c.Add vehicle  d. Add Driver  e. Edit Password  f. Show records \n\n";
}
void system_Show() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "Taxi:¡«sudo$ ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
}

void show_VehicleList() {

}

void show_DriverList() {

}

void vehicle_Board() {
	cout << "\t  a.Modify information  b.Delete information  c.Payment information  d. Quit \n\n";
}

void driver_Board() {
	cout << "\t  a.Modify information  b.Delete information  c.Rewards & Punishments  d. Quit \n\n";
}

void show_Search()
{
	int lp_tmp;
	/*--------------------------------------------------------*/
	cout << "\n\n\n\t\t\t  SEARCH YOUR INFORMATION \n\t   ";

	cout << "-----------------------------------------------------\n";
	for (lp_tmp = 0; lp_tmp < 1; lp_tmp++)
	{
		cout << "\t  |     \t\t\t\t\t\t|\n";
	}
	cout << "\t  |\t\t\t";

	get_NowCursor_Start();
	cout << "   \t\t\t\t|\n";
	for (lp_tmp = 0; lp_tmp < 1; lp_tmp++)
	{
		cout << "\t  |     \t\t\t\t\t\t|\n";
	}
	cout << "\t   -----------------------------------------------------";
	gotoxy(point_A, point_B);
	/*--------------------------------------------------------*/
}

void wrong_Search()
{
	int lp_tmp;
	/*--------------------------------------------------------*/
	cout << "\n\n\n\t\t\tFailed to search the account! \n\t   ";

	cout << "-----------------------------------------------------\n";
	for (lp_tmp = 0; lp_tmp < 1; lp_tmp++)
	{
		cout << "\t  |     \t\t\t\t\t\t|\n";
	}
	cout << "\t  |\t\t\t";

	get_NowCursor_Start();
	cout << "   \t\t\t\t|\n";
	for (lp_tmp = 0; lp_tmp < 1; lp_tmp++)
	{
		cout << "\t  |     \t\t\t\t\t\t|\n";
	}
	cout << "\t   -----------------------------------------------------";
	gotoxy(point_A, point_B);
	/*--------------------------------------------------------*/
}

void show_Super()
{
	int lp_tmp;
	/*--------------------------------------------------------*/
	cout << "\n\n\n\t\tSuper Authority, ENTER THE PASSWORD PLEASE! \n\t   ";
	cout << "-----------------------------------------------------\n";
	for (lp_tmp = 0; lp_tmp < 1; lp_tmp++)
	{
		cout << "\t  |     \t\t\t\t\t\t|\n";
	}
	cout << "\t  |\t\t\t";

	get_NowCursor_Start();
	cout << "   \t\t\t\t|\n";
	for (lp_tmp = 0; lp_tmp < 1; lp_tmp++)
	{
		cout << "\t  |     \t\t\t\t\t\t|\n";
	}
	cout << "\t   -----------------------------------------------------";
	gotoxy(point_A, point_B);
	/*--------------------------------------------------------*/
}

void show_Wait()
{
	int lp_tmp;
	int count;
	for (int lp_tmp = 0; lp_tmp < 2; lp_tmp++)
	{
		cout << "Congratulations! Wait for a second please.";
		for (int count = 0; count < 3; count++)
		{
			cout << ".";
			//Sleep(500);
		}
		system("cls");
	}
}

void show_man()
{
	cout << "\nclear: clear[CLR]\n";
	cout << "         Directly enter the clear command any information on the current terminal can be cleared.\n";
	cout << "\nls (parameter): ls[LS]\n";
	cout << "	 Directly display the databases list.\n";
	cout << "     -l: Display all databases list including the size of them.\n";
	cout << "\nrm/(option): delete[RM]\n";
	cout << "	 Delete the file you choose\n";
	cout << "\nexit: exit[EXIT]\n";
	cout << "	 Exit the sudo account.\n";
	cout << "\ncd: change directory[CD]\n";
	cout << "	 Switch the working directory to the main menu.\n";
}