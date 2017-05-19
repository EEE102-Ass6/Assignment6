/*
* File      :Taxi_Company.cpp
* Author: Zhao zhihe£¨Kyrie£©
* ID number: 1405180
* Description: This file is the main file of the project.
* Change Logs:
* Date           Author       Notes
* 2017-05-16     Kyrie      Get familiar to the Question and design the model.
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
#include "Interfaces.h"
#include "Administrator.h"
#include "system.h"
using namespace std;

extern int point_X;
extern int point_Y;
extern int point_A;
extern int point_B;
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
	char* password = sudo_check.get_password();
	int pw_check=0;
	flg:
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
							printf("*");
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
						cout << sudo_check.get_passwd_len() << "sss"<<(strlen(account_PW) - 1) << endl;
						check = 0;
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
		//else if (1)
		//{

		//}
		/*----------------Interfaces for the database;----------------*/

		//cout << "Wrong Name." << endl;
	} while (check = 0);
	

	/*----------------------SHOW WAIT------------------------*/
	for (int count1 = 0; count1 < 2; count1++)
	{
		cout << "Congratulations! Wait for a second please.";
		for (int count = 0; count < 3; count++)
		{
			cout << ".";
			Sleep(600);
		}
		system("cls");
	}
	/*----------------------SHOW WAIT------------------------*/

	cout << "\n\n"<<endl;
	
	show_Welcome();
	system_Show();

	HANDLE handle = CreateThread(NULL, 0, ThreadFun, NULL, 0, NULL);
	WaitForSingleObject(handle, 200);

	while (1)
	{
		
	}
	system("pause");
	return 0;
}