/*
* Project: Mangement information system of the BMW taxi loan company
* Author: Zhao zhihe(Kyrie);Chen qianshan(Sameul);Wang jiaheng(Djaha);Yi yongwei(Jack);Li kainan(Eric)
* Description: This project is demanded by a Taxi company for the management of taxies and drivers.	The system must be able to store the information of the vehicles and drivers of a Taxi Company. The
	administrator of this system should have higher authority to perform all the editing, while the driver user
	can only search for their own information and rewards and punishment records.
	The system should be able to provide functionality as listed below:
	 -Browse, add, modify and delete the vehicle information and driver information;
	 -Make sure every vehicle is driving by one to two drivers;
	 -Register the payment information of every vehicle;
	 -Register rewards and punishments for every driver;
	 -Provides different authority to different type of users.

* Change Logs:
* Date           Author          Notes
* 2017-05-16     Kyrie.Zhao      Get familiar to the Question and design the model.
				 Samuel.Chen
				 Djaha.Wang
				 Jack.Yi
				 Eric.Li
* 2017-05-17     Kyrie.Zhao      Finish the super account check part
				 Samuel.Chen
				 Djaha.Wang
				 Jack.Yi
				 Eric.Li
* 2017-05-17     Kyrie.Zhao      Modify the structure of the account checking part, Spare the space for the normal users account check.
				 Samuel.Chen
				 Djaha.Wang
				 Jack.Yi
				 Eric.Li
* 2017-05-18     Kyrie.Zhao      Add the multi-thread function which allows the user to ENTER SPACE to flexibly MAXIMIZE/MINIMIZE the window into the system
				 Samuel.Chen
				 Djaha.Wang
				 Jack.Yi
				 Eric.Li
* 2017-05-18     Kyrie.Zhao      Design the multi-thread function which involves of the system commands.
				 Samuel.Chen
				 Djaha.Wang
				 Jack.Yi
				 Eric.Li
* 2017-05-19	 Kyrie.Zhao		 Design the Hash table data structure.
				 Samuel.Chen
				 Djaha.Wang
				 Jack.Yi
				 Eric.Li
* 2017-05-19     Kyrie.Zhao      Design the core operation interfaces "systemController"
				 Samuel.Chen
				 Djaha.Wang
				 Jack.Yi
				 Eric.Li
* 2017-05-19     Kyrie.Zhao      Implement the structure of the main function loop
				 Samuel.Chen
				 Djaha.Wang
				 Jack.Yi
				 Eric.Li
* 2017-05-19     Kyrie.Zhao      Cooperate with the interfaces with the function interfaces.
				 Samuel.Chen
				 Djaha.Wang
				 Jack.Yi
				 Eric.Li
* 2017-05-20     Kyrie.Zhao      Cooperate with the interfaces with the function interfaces.
				 Samuel.Chen
				 Djaha.Wang
				 Jack.Yi
				 Eric.Li
* 2017-05-21     Kyrie.Zhao      Improve the rubostness of the input/output, Control the I/O stream.
				 Samuel.Chen
				 Djaha.Wang
				 Jack.Yi
				 Eric.Li
* 2017-05-21     Kyrie.Zhao      Finish the basic function of the main process.
				 Samuel.Chen
				 Djaha.Wang
				 Jack.Yi
				 Eric.Li
* 2017-05-22     Kyrie.Zhao      Finish the implemention of interfaces file: "systemController"
				 Samuel.Chen
				 Djaha.Wang
				 Jack.Yi
				 Eric.Li
* 2017-05-22     Kyrie.Zhao      Check and do final function testing part.
				 Samuel.Chen
				 Djaha.Wang
				 Jack.Yi
				 Eric.Li
* 2017-05-25     Kyrie.Zhao      Finish the project
				 Samuel.Chen
				 Djaha.Wang
				 Jack.Yi
				 Eric.Li
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
#include <imm.h>  
#pragma comment (lib ,"imm32.lib") 
using namespace std;
extern int check_file_driver;
extern int check_file_vehicle;
extern int check_file_history;
extern int point_X;
extern int point_Y;
extern int point_A;
extern int point_B;
extern char input_check[30];

systemController *sc = new systemController;
//extern systemController *sc;

int main()
{
	string authority_check;

	int check = 0;
	int tmp_pw = 0;
	int tmp_counter_pw = 0;
	int chance = 3;
	int lp_tmp;
	char ch = '\0';
	char account_Name[20], account_PW[30];
	SetConsoleTitle(L"Company ");
	Admin sudo_check;
	//systemController user_operation;
	char* password = sc->readPassword();
	char new_password[30];
	int pw_check = 0;
	bool function_check;

	char input_second_check[30];
	HWND m_hWnd=NULL;
	//systemController *sc = new systemController;
	//sc = new systemController;
	//sc->noteHistory("hola");

	//HWND hwnd1 = GetForegroundWindow();
	//ShowWindow(hwnd1, SW_MAXIMIZE);
	memset(input_check, '\0', 30);
	memset(input_second_check, '\0', 30);
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	
	sudo_check.set_newPW(sc->readPassword());
	/*--------------------------------------------------------*/
	
	/*--------------------------------------------------------*/

	do {
		show_Search();
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
					account_PW[tmp_pw] = ch;
					if (ch == '\b')
					{
						system("cls");
						show_Super();
						if (tmp_pw <= 0)
						{
							tmp_pw = 0;
							continue;
						}
						for (tmp_counter_pw = 0; tmp_counter_pw < (tmp_pw - 1); tmp_counter_pw++)
						{
							cout << "*";
						}
						account_PW[tmp_pw-1] = '\0';
						//else {
							tmp_pw -= 2;
						//}
						continue;
					}
					else if (ch == '\r')
					{
						printf("\n");

						//To clean the buffer left the string.
						account_PW[tmp_pw] = '\0';
						break;
					}
					else
					{
						cout << "*";

					}
				}

				for (lp_tmp = 0; lp_tmp < (sudo_check.get_passwd_len()); lp_tmp++)
				{
					if ((password[lp_tmp] != account_PW[lp_tmp]) || (sudo_check.get_passwd_len() != (strlen(account_PW))))
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
				if (chance == 0) {
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
		else if (sc->searchKey(account_Name))
		{
			bool tmp;
			system("cls");
			cout << "\n\n\n";
			tmp = sc->searchKey(account_Name);
			
			cout << "\nEnter anything to getback\n\n";
			system_Show_client(account_Name);
		
			getch();
			system("cls");
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
	handle = CreateThread(NULL,
		0,
		thread_Screen,
		NULL,
		0,
		NULL);

	WaitForSingleObject(handle, 200);

	/*Multi-thread 2 --- The system commands*/
	handle_sys = CreateThread(NULL,
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
			sc->vehicleListAll();
			cout << "\n";
			vehicle_Board();
			system_Show_vehicle();
			cin >> input_check;
			thread_check = true;
			if (strcmp(input_check, "a") == 0) {
				thread_check = false;
				//thread_check = false;
				sc->modifyVehicle();
				memset(input_check, '\0', 30);
			}
			else if (strcmp(input_check, "b") == 0) {
				thread_check = false;
				sc->vehicleDelete();
				memset(input_check, '\0', 30);

			}
			else if(strcmp(input_check, "c") == 0) {
				thread_check = false;
				sc->payment();
				memset(input_check, '\0', 30);
			}
			system_Show();
			memset(input_second_check, '\0', 30);
			//ResumeThread(handle_sys);
		}
		//board 1----Driver
		else if (strcmp(input_check, "b") == 0) {
			thread_check = false;
			memset(input_check, '\0', 30);
			sc->driverListAll();

			driver_Board();
			system_Show_driver();
			cin >> input_check;
			thread_check = true;
			if (strcmp(input_check, "a") == 0) {
				thread_check = false;
				sc->modifyDriver();
				memset(input_check, '\0', 30);

			}
			else if (strcmp(input_check, "b") == 0) {
				thread_check = false;
				sc->driverDelete();
				memset(input_check, '\0', 30);

			}
			else if (strcmp(input_check, "c") == 0) {
				thread_check = false;
				sc->doRewardsAndPunishiment();
				memset(input_check, '\0', 30);
			}
			system_Show();
			memset(input_second_check, '\0', 30);

			//ResumeThread(handle_sys);
		}
		//board 1----Add_vehicle
		else if (strcmp(input_check, "c") == 0) {
			//	sc->addDriver();
			thread_check = false;
			if (!(function_check = sc->addVehicle()))
			{
				perror("perror"); // 回错误返1				
			}
			check_file_vehicle = 0;//变成未删除
			memset(input_check, '\0', 30);
			system_Show();
			//ResumeThread(handle_sys);
		}
		//board 1----Add_Driver
		else if (strcmp(input_check, "d") == 0) {
			thread_check = false;
			if (!(function_check = sc->addDriver()))
			{
				perror("perror"); // 回错误返1				
			}
			check_file_driver = 0;//变成未删除
			//sc->DeleteAllDriver();
			memset(input_check, '\0', 30);
			system_Show();
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
					cout << "*";
					//cout << new_password[tmp_pw];
				}
			}
			
			cout << new_password << "\nSuccess set!\n";

			sudo_check.set_newPW(new_password);

			sc->changePassword(new_password);

			system_Show();

			memset(new_password, '\0', 30);

			memset(input_check, '\0', 30);

			//ResumeThread(handle_sys);
			//WaitForSingleObject(handle_sys, 200);
		}
		//board 1----Show records
		else if (strcmp(input_check, "f") == 0) {
			thread_check = false;
			
			sc->showEditingRecords();
			system_Show();

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
	//system("pause");
	if (CloseHandle(handle)) {
		if (CloseHandle(handle_sys))
		{
			cout << "Checked.";
		}
	}
	else {
		return 0;
	}
	system("pause");
}