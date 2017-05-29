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
	cout << "  \t\t\t\tEnter [SPACE] to MAX/MINIMIZE the screen" << endl;
	cout << "  \t\t\t\tEnter \"help\" to check the system commands" << endl;
	cout << "\t\t\t£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤" << endl;
	for (i = 0; i < 3; i++)
	{
		cout << "\t\t\t£¤\t\t\t\t\t\t  £¤" << endl;
	}
	cout << "\t\t\t£¤¡ï¡¾   Welcom to BMW Taxi mangement system  ¡¿¡ï£¤" << endl;
	for (i = 0; i < 3; i++)
	{
		cout << "\t\t\t£¤\t\t\t\t\t\t  £¤" << endl;
	}
	cout << "\t\t\t£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤£¤\n" << endl;	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "\t  a.Vehicle  b.Driver  c.Add vehicle  d. Add Driver  e. Edit Password  f. Show records \n\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
}

void system_Show() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "BMW:¡«sudo$ ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
}

void system_Show_client(char* tmp) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "BMW:¡«"<<tmp<<"$ ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
}

void system_Show_driver() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "BMW:¡«sudo¡«driver$ ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
}

void system_Show_vehicle() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "BMW:¡«sudo¡«vehicle$ ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
}

void show_Vehicle_second() {
	cout << "\t  a.Modify information  b.Delete information  c.Payment information  d. Quit \n\n";
}

void show_Driver_second() {
	cout << "\t  a.Modify information  b.Delete information  c.Payment information  d. Quit \n\n";
}

void vehicle_Board() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "\t  a.Modify information  b.Delete information  c.Payment information \n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
}

void driver_Board() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "\t  a.Modify information  b.Delete information  c.Rewards & Punishments \n";

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
	cout << "\n\n\n\t\t\tFailed to search the account! \t   ";
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
		cout << "\n\n\n\n\t\tCongratulations! Wait for a second please.";
		for (int count = 0; count < 3; count++)
		{
			cout << ".";
			//Sleep(400);
		}
		system("cls");
	}
}

void show_man()
{
	cout << "\nhelp: help[HELP]\n";
	cout << "         Illustrate the system commands which initially set.\n";
	cout << "\nclear: clear[CLR]\n";
	cout << "         Directly enter the clear command any information on the current terminal can be cleared.\n";
	cout << "\ncd: cd[CD]\n";
	cout << "         Get back to the main menu.\n";
	cout << "\nls (parameter): ls[LS]\n";
	cout << "	 Directly display the databases list.\n";
	cout << "     /-l: Display all databases list including the size of them.\n";
	cout << "\nrm/(option): delete[RM]\n";
	cout << "	 Delete the file you choose\n";
	cout << "\nmail/(option): mail[MAIL]\n";
	cout << "	 Choose a database file to send to the mailbox, the set mailbox is zhaozhihe2333@sina.com\n";	
	cout << "\ncd: change directory[CD]\n";
	cout << "	 Switch the working directory to the main menu.\n";
	cout << "\nexit: exit[EXIT]\n";
	cout << "	 Exit the sudo account.\n";
	cout << "\nquit: quit[QUIT]\n";
	cout << "	 Quit the software\n";
}	
