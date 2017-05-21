/*
* File      :Taxi_Company.cpp
* Author: Zhao zhihe£¨Kyrie£©
* ID number: 1405180
* Description: This file is the main file of the project.
* Change Logs:
* Date           Author          Notes
* 2017-05-16     Kyrie.Zhao      Get familiar to the Question and design the model.
* 2017-05-17     Kyrie.Zhao      Finish the super account check part
* 2017-05-17     Kyrie.Zhao      Modify the structure of the account checking part, Spare the space for the normal users account check.
* 2017-05-18     Kyrie.Zhao      Add the multi-thread function which allows the user to ENTER SPACE to flexibly MAXIMIZE/MINIMIZE the window into the system 
* 2017-05-18     Kyrie.Zhao      Design the multi-thread function which involves of the system commands.
* 2017-05-19     Kyrie.Zhao      Implement the structure of the main function loop
* 2017-05-19     Kyrie.Zhao      Cooperate with the interfaces with the function interfaces.
* 2017-05-20     Kyrie.Zhao      Cooperate with the interfaces with the function interfaces.
* 2017-05-21     Kyrie.Zhao      Improve the rubostness of the input/output, Control the I/O stream.
* 2017-05-21     Kyrie.Zhao      Finish the basic function of the main process.
* 2017-05-22     Kyrie.Zhao      Check and do final function testing part.
*/
#include <math.h>
#include <windows.h>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include<cstring>
#include <iostream>
#include <conio.h>
#include "systemController.h"
#include "Screen.h"
#include "Display_interfaces.h"
#include "Administrator.h"
#include "system.h"
using namespace std;

extern int point_X;
extern int point_Y;
extern int point_A;
extern int point_B;
extern char input_check[30];
int main()
{
	string authority_check;

	int check = 0;
	int tmp_pw = 0;
	int chance = 3;
	int lp_tmp;
	char ch = '\0';
	char account_Name[20], account_PW[30];

	Admin sudo_check;
	systemController user_operation;
	char* password = sudo_check.get_password();
	char new_password[30];
	int pw_check=0;
	//HWND hwnd1 = GetForegroundWindow();
	//ShowWindow(hwnd1, SW_MAXIMIZE);
	memset(input_check, '\0', 30);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	/*--------------------------------------------------------*/
	show_Search();
	/*--------------------------------------------------------*/

	do{
		cin >> account_Name;
		//cout << "Please enter again your password." << endl;
		//cin >> b;
		if (strcmp(account_Name, sudo_check.get_account()) == 0)
		{
			    system("cls");		

			    while (1)
			{
				/*--------------------------------------------------------*/
					show_Super();
				/*--------------------------------------------------------*/
				//To change the display of the passwords into the format of "*****"
			
					for (tmp_pw = 0;; tmp_pw++)
					{
						ch = getch();
						if (ch == '\r')
						{
							printf("\n");

							//To clean the buffer left the string.
							account_PW[tmp_pw] = '\0';
							break;
						}
						else
						{
							account_PW[tmp_pw] = ch;
							cout<<"*";
						}
					}

					for (lp_tmp = 0; lp_tmp < (sudo_check.get_passwd_len()); lp_tmp++)
					{
						if ((password[lp_tmp] != account_PW[lp_tmp])||(sudo_check.get_passwd_len()!=(strlen(account_PW))))
						{
							cout << "wrong" << account_PW;
							//cout << "wrong" << sudo_check.get_passwd_len();
							pw_check = 1;
							chance--;
							/*--------------------------------------------------------*/
							system("cls");
							cout << "\n\n\n\n\n\t\tWRONG PASSWORD! You have " << chance << " chances left! \n\t   ";
							
							/*--------------------------------------------------------*/
							Sleep(1500);
							break;
						}
					}

					if (pw_check == 0) {
						//The sign of getting out of the loop
						
						check = 1;
						system("cls");
						break;
					}
					if (chance == 0){
						system("cls");
						cout << "\n\n\n\n\n\t\tSYSTEM QUIT! " << endl;
						Sleep(1000);
						return 0;
					}
					else if ((chance == 1) || (chance == 2))
					{
						system("cls");
						pw_check = 0;
						continue;
					}					

			}
				//system("cls");
		}
		/*----------------Interfaces for the database;----------------*/
		else if(user_operation.searchKey(account_Name))
		{
			
			memset(account_Name, '\0', 30);
			continue;
		}
		else {
			system("cls");
			memset(account_Name, '\0', 30);
			wrong_Search();
			continue;
		}
		/*----------------Interfaces for the database;----------------*/


		/*----------------Reset the parameters concerning to the super;----------------*/
	
		/*----------------Reset the parameters concerning to the super;----------------*/
		//cout << "Wrong Name." << endl;
		
	} while (check == 0);

	/*----------------------SHOW WAIT------------------------*/
	show_Wait();
	/*----------------------SHOW WAIT------------------------*/
	
	show_Welcome();
	system_Show();

	/*Multi-thread 1 --- The screen*/
	handle = CreateThread(	NULL, 
							0, 
							thread_Screen, 
							NULL, 
							0, 
							NULL);

	WaitForSingleObject(handle, 200);

	/*Multi-thread 2 --- The system commands*/
	handle_sys = CreateThread(	NULL, 
								0, 
								thread_SystemCMD, 
								NULL, 
								0, 
								NULL);

	WaitForSingleObject(handle_sys, 200);

//	SuspendThread(handle);
	//ResumeThread(handle);
	
	//cout << "\nSuccess set!\n";
//	SuspendThread(handle_sys);
	while (1)
	{
		thread_check = true;
		//SuspendThread(handle_sys);
		//cout << "\nSuccess set!\n";
		cin >> input_check;
		
		//board 1----Vehicle
		if (strcmp(input_check, "a") == 0) {
			thread_check = false;
			memset(input_check, '\0', 30);
			//ResumeThread(handle_sys);
		}
		//board 1----Driver
		else if (strcmp(input_check, "b") == 0) {
			thread_check = false;
			memset(input_check, '\0', 30);
			//ResumeThread(handle_sys);
		}
		//board 1----Add_vehicle
		else if (strcmp(input_check, "c") == 0) {
			thread_check = false;
			memset(input_check, '\0', 30);
			//ResumeThread(handle_sys);
		}
		//board 1----Add_Driver
		else if (strcmp(input_check, "d") == 0) {
			thread_check = false;
			memset(input_check, '\0', 30);
			//ResumeThread(handle_sys);
		//	WaitForSingleObject(handle_sys, 200);
		}
		//board 1----Edit passwords
		else if (strcmp(input_check, "e") == 0) {
			thread_check = false;
			for (tmp_pw = 0;; tmp_pw++)
			{
				ch = getch();
				if (ch == '\r')
				{
					cout << "\n";
					//cout << "\nSuccess set!\n";
					//To clean the buffer left the string.
					new_password[tmp_pw] = '\0';
					break;
				}
				else
				{
					new_password[tmp_pw] = ch;
					cout << ch;
					//cout << new_password[tmp_pw];
				}
			}
			cout << new_password << "\nSuccess set!\n";
			sudo_check.set_newPW(new_password);
			system_Show();
			
			memset(new_password, '\0', 30);
			
			memset(input_check, '\0', 30);
			
			//ResumeThread(handle_sys);
			//WaitForSingleObject(handle_sys, 200);
		}
		//board 1----Show records
		else if (strcmp(input_check, "f") == 0) {
			thread_check = false;
			memset(input_check, '\0', 30);
			//ResumeThread(handle_sys);
		}
		//resume thread_sys
		else {
			//ResumeThread(handle_sys);
			thread_check = true;
			//out<<input_check<<endl;
		//	memset(input_check, '\0', 30);
		
		}
		Sleep(100);
		//cout << "1err";
	}
	system("pause");

	if (CloseHandle(handle)) {
		if (CloseHandle(handle_sys))
		{
			cout << "Checked.";
		}
	}
	else {
		return 0;
	}
	
}