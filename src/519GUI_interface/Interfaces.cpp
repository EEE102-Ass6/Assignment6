#include <iostream>
#include "windows.h"
#include "Interfaces.h"

using namespace std;
void show_Welcome()
{
	int i;
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
