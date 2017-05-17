/*Name: Hotel Management Information System
File Name: Assignment6-GroupProject-Project F
Author: Jiaheng Wang
*/
//Header Files list:
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>      /*call functions about characters*/
#include <conio.h>      /*general I/O library*/
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//stucture (self-defined variable type) list:
typedef struct room {
	char class;
	char status;
};
typedef struct time{
	int sec;
	int min;
	int hour;
	int day;
	int mon;
	int year;
};
typedef struct date{
	int year;
	int month;
	int day;
};
typedef struct staff_use{
	int identity;
	char name[30];
	char password[30];
};
typedef struct customer{
	char name[30];
	char phonenumber[30];
	char VIP_number[30];
	char status;
	char VIP_status;
};
typedef struct Customer_Node{
	//basic property
	char name[30];
	char phonenumber[30];
	char VIP_number[30];
	char status;
	char VIP_status;
	//in-file property
	int position;
	struct Customer_Node *next;
};
typedef struct registration{
	int r;	/*room position*/
	int c;	/*room position*/
	struct customer registrant;	/*customer info*/
	struct date regist_day;		/*date info*/
	int price;	/*the real-time price at that time*/
};
typedef struct room_price{
	int price1;
	int price2;
	int price3;
	int price_vip;
	float group_price;
	float price_after_week;
	float price_after_month;
};
typedef struct hotel_statistics{
	int total_income;
	int history_customers;
};
//function list (extra functions):
int gotoxy(int x, int y) {
	//position of cursor on the screen
	COORD coord;
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return 0;
}
void setcolor(unsigned short ForeColor, unsigned short BackGroundColor) {
	//color operattion
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);
}
void Call_Time(struct time *t) {
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	t->day = (*timeinfo).tm_mday;
	t->mon = (*timeinfo).tm_mon + 1;
	t->year = (*timeinfo).tm_year + 1900;
	t->hour = (*timeinfo).tm_hour;
	t->min = (*timeinfo).tm_min;
	t->sec = (*timeinfo).tm_sec;
}

////////////////////////////////////////*elegant division line*////////////////////////////////////////

//"consealed" function list (functional):
void Print_All(void);
void Print_All_hash(struct Customer_Node **Hasharray, int *n);
void Print_All_Customer(void);
void Reduce_All(void);
void Note_Print(void);
void Check_R(struct room **Room_Board);
void Check_U(struct room **Room_Board);
//judge function list:
int judgenum(char *a);
int judgechar(char *a);
char *Random_Six(void);

////////////////////////////////////////*elegant division line*////////////////////////////////////////

//function list (main menu):
void Daily_Check(struct room **Room_Board);
void Prework(struct room **Room_Board, struct room_price *parameters, struct hotel_statistics *income_x_customers);
void Room_With_Price(struct room **Room_Board, struct room_price *parameters);
void Main_Menu(struct room **Room_Board, struct room_price *parameters, struct hotel_statistics *income_x_customers, struct Customer_Node **Hasharray, int *n);
//function list (about Hashtable):
void Hash_Expand(struct Customer_Node **Hasharray, struct customer *target, int *n);
int Hash_Key_Function(char *name);
static void Hashtable_Free(struct Customer_Node **Hasharray);
//fuction list (hotel parameters, all kinds of prices):
void Hotel_Parameters_Initialization(struct room_price *parameters);
void File_Parameters_Info_Write(struct room_price *parameters);
void File_Parameters_Info_Read(struct room_price *parameters);
//function list (hotel statistics):
void Hotel_Statistics_Initialization(struct hotel_statistics *income_x_customers);
void File_Statistics_Info_Write(struct hotel_statistics *income_x_customers);
void File_Statistics_Info_Read(struct hotel_statistics *income_x_customers);
//function list (room board demonstration):
void Room_Info_Initialization(struct room **Room_Board);
void Room_Demonstration(struct room **Room_Board);
void Room_Board_Free(struct room **Room_Board);
void File_Room_Info_Write(struct room **Room_Board);
void File_Room_Info_Read(struct room **Room_Board);
//function list (account):
void File_Staff_Write(int user_identity);
int File_Staff_Read(int user_identity, struct staff_use *person);
//function list (manager menu):
void Manager_Menu(struct room **Room_Board, struct room_price *parameters, struct hotel_statistics *income_x_customers, struct Customer_Node **Hasharray, int *n);
void VIP_Handle(struct Customer_Node **Hasharray);
void Room_Info_Amend(struct room **Room_Board);
void manager_amend_booking_info(struct room_price *parameters);
//function list (booking operator menu):
void Booking_Operator_Menu(struct room **Room_Board, struct room_price *parameters, struct hotel_statistics *income_x_customers, struct Customer_Node **Hasharray, int *n);
void Registration_Interface(struct room **Room_Board, struct room_price *parameters, struct Customer_Node **Hasharray, int *n);
int Arrival_Date(int *y, int *m, int *d);
int Judge_On_Date(int y, int m, int d, int coi);
int Calculate_Date(int year, int month, int day);
int Calculate_Price(int level, int basic, struct room_price *parameters);
int Apply_For_VIP(void);
int Random_Allocation(struct room **Room_Board, char class, int *r, int *c, int condition);
//function list (check in/out operator menu):
void Checker_Operator_Menu(struct room **Room_Board, struct room_price *parameters, struct hotel_statistics *income_x_customers, struct Customer_Node **Hasharray, int *n);
void Customer_Services(struct room **Room_Board, struct room_price *parameters, struct hotel_statistics *income_x_customers, struct Customer_Node **Hasharray, int *n);
void New_Customer(struct customer *customer, struct Customer_Node **Hasharray, int *n);
void Customer_Check_In(struct room **Room_Board, struct room_price *parameters, struct Customer_Node **Hasharray, int *n);
void Customer_Check_Out(struct room **Room_Board, struct room_price *parameters, struct hotel_statistics *income_x_customers, struct Customer_Node **Hasharray, int *n);
//global variable list:
struct staff_use Current_User;	//identity, name, password
struct customer Current_Customer; //name, phone number, VIP number, date
struct date Current_Date;	//year, month, day
int Manager_Login_Satus = 0;
int BO_Login_Satus = 0;
int CO_Login_Satus = 0;
//function: 'main()', so-called entrance of the program
int main()
{	//dynamic memory space allocation:
	struct room **Room_Board = (struct room**)malloc(6 * sizeof(struct room*));
	for (int i = 0; i < 6; i++)
		Room_Board[i] = (struct room*)malloc(20 * sizeof(struct room));
	//hotel parameters, hotel statistics:
	struct room_price parameters;
	struct hotel_statistics income_x_customers;
	//Prework:
	Prework(Room_Board, &parameters, &income_x_customers);
	Daily_Check(Room_Board);
	//hasharray create (60buckets):
	int location_in_file = 0, *lif = &location_in_file;
	//memory allocation process for hashtable
	struct Customer_Node **Hasharray = (struct Customer_Node**)malloc(60 * sizeof(struct Customer_Node*));
	for (int i = 0; i < 60; i++) {	//60buckets
		Hasharray[i] = (struct Customer_Node*)malloc(sizeof(struct Customer_Node));
		Hasharray[i]->next = NULL;
	}
	//create hashtable:
	FILE *ptr_customer;
	fflush(stdin);
	ptr_customer = fopen("customer database.txt", "r");	//open file (read only)
	if (ptr_customer == NULL) {	/*Test the success of opening(reading) the file*/
		printf("There was a problem opening the file, please restart the program.\n\n");
		Hashtable_Free(Hasharray);
		Sleep(3000); exit(0);
	}
	else {
		printf("\nOpening file success!\nHashtable is creating...\n\n");
		while (fread(&Current_Customer, sizeof(struct customer), 1, ptr_customer)) {
			//put each account into its 'bucket'
			Hash_Expand(Hasharray, &Current_Customer, lif);
			fflush(stdin);
		}
	}
	fclose(ptr_customer);
	printf("\nHashtable inspection compelete!\nCloseing file success!\n\n");
	system("PAUSE");
	//access to the main menu:
	Main_Menu(Room_Board, &parameters, &income_x_customers, Hasharray, lif);
	//Free memory space:
	Room_Board_Free(Room_Board);
	Hashtable_Free(Hasharray);
	return 0;
}
//function list (main menu):
void Daily_Check(struct room **Room_Board) {
	struct registration temp;
	FILE *ptr_temp;
	FILE *ptr_registration;
	ptr_temp = fopen("temp.bat", "wb");
	ptr_registration = fopen("reg.bat", "rb");
	if (ptr_registration == NULL || ptr_temp == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	else {
		while (fread(&temp, sizeof(struct registration), 1, ptr_registration)) {
			if (Judge_On_Date(temp.regist_day.year, temp.regist_day.month, temp.regist_day.day, 1) < 0)
				fwrite(&temp, sizeof(struct registration), 1, ptr_temp);
			else {
				printf("\n%10s, %20s did not come.", temp.registrant.name, temp.registrant.phonenumber);
				//amend Room_Board£»
				Room_Board[temp.r][temp.c].status = 'N';
				File_Room_Info_Write(Room_Board);
			}
		}
	}
	fclose(ptr_temp);
	fclose(ptr_registration);
	remove("reg.bat");	//delete the origin file
	DeleteFile(TEXT("reg.bat"));	//delete the origin file (confirm, delete again)
	rename("temp.bat", "reg.bat");	//change name into origin file
}

void Prework(struct room **Room_Board, struct room_price *parameters, struct hotel_statistics *income_x_customers) {
	//Version information:
	printf("Final Version 2.0.\n");
	//time calling test
	struct time current_time;
	Call_Time(&current_time);
	printf("Date today: %4d / %02d / %02d\n", current_time.year, current_time.mon, current_time.day);
	Current_Date.year = current_time.year;
	Current_Date.month = current_time.mon;
	Current_Date.day = current_time.day;
	//elegant division line
	system("PAUSE");
	//at least there exist a file about room information
	FILE *ptr_r;
	ptr_r = fopen("room info.txt", "r");
	if (ptr_r == NULL) {
		Room_Info_Initialization(Room_Board);
		File_Room_Info_Write(Room_Board);
	}
	else {
		fclose(ptr_r);
		File_Room_Info_Read(Room_Board);
	}
	printf("'room info.txt'is ready!\n");
	//at least there exist a file about hotel parameters
	FILE *ptr_p;
	ptr_p = fopen("hotel parameters.txt", "r");
	if (ptr_p == NULL) {
		Hotel_Parameters_Initialization(parameters);
		File_Parameters_Info_Write(parameters);
	}
	else {
		fclose(ptr_p);
		File_Parameters_Info_Read(parameters);
	}
	printf("'hotel parameters.txt' is ready\n");
	//at least there exist a file about hotel statistics
	FILE *ptr_s;
	ptr_s = fopen("hotel statistics.txt", "r");
	if (ptr_s == NULL) {
		Hotel_Statistics_Initialization(income_x_customers);
		File_Statistics_Info_Write(income_x_customers);
	}
	else {
		fclose(ptr_s);
		File_Statistics_Info_Read(income_x_customers);
	}
	printf("'hotel statistics.txt' is ready\n");
	//at least there exist a file about staff information
	FILE *ptr1;
	ptr1 = fopen("staff.txt", "a");
	if (ptr1 == NULL) {
		printf("There was a problem opening the file, please restart the program\n\n");
		Sleep(3000); exit(0);
	}
	fclose(ptr1);
	printf("'staff.txt'is ready!\n");
	//at least there exist a file about staff login time
	FILE *ptr2;
	ptr2 = fopen("staff login record.txt", "a");
	if (ptr2 == NULL) {
		printf("There was a problem opening the file, please restart the program\n\n");
		Sleep(3000); exit(0);
	}
	fclose(ptr2);
	printf("'staff login record.txt'is ready!\n");
	//at least there exist a file about customer info
	FILE *ptr3;
	ptr3 = fopen("customer database.txt", "a");
	if (ptr3 == NULL) {
		printf("There was a problem opening the file, please restart the program\n\n");
		Sleep(3000); exit(0);
	}
	fclose(ptr3);
	printf("'customer database.txt'is ready!\n");
	//at least there exist a file about R info
	FILE *ptr4;
	ptr4 = fopen("reg.bat", "ab");
	if (ptr4 == NULL) {
		printf("There was a problem opening the file, please restart the program\n\n");
		Sleep(3000); exit(0);
	}
	fclose(ptr4);
	printf("'reg.bat'is ready!\n");
	//at least there exist a file about U info
	FILE *ptr5;
	ptr5 = fopen("in hotel.bat", "ab");
	if (ptr5 == NULL) {
		printf("There was a problem opening the file, please restart the program\n\n");
		Sleep(3000); exit(0);
	}
	fclose(ptr5);
	printf("'in hotel.bat'is ready!\n");
	//at least there exist a file about Waiting VIP confirm
	FILE *ptr6;
	ptr6 = fopen("VIP wait.txt", "a");
	if (ptr6 == NULL) {
		printf("There was a problem opening the file, please restart the program\n\n");
		Sleep(3000); exit(0);
	}
	fclose(ptr6);
	printf("'VIP wait.txt'is ready!\n");
	//wait for 1s
	for (int i = 0; i < 10; i++) {
		printf("."); Sleep(100);
	}
}

void Room_With_Price(struct room **Room_Board, struct room_price *parameters) {
	Room_Demonstration(Room_Board);
	printf("\n\n");
	printf("class '*' . %d\n", parameters->price1);
	printf("class '**' . %d\n", parameters->price2);
	printf("class '***' . %d\n", parameters->price3);
	printf("class 'VIP' . %d\n", parameters->price_vip);
	printf("Waiting for your option...\n");
}

void Main_Menu(struct room **Room_Board, struct room_price *parameters, struct hotel_statistics *income_x_customers, struct Customer_Node **Hasharray, int *n) {
	int option;
	char option_char;
	while (1) {
		system("cls");
		//the main interface:
		gotoxy(0, 3); printf("***Hotel Management Information System***");
		gotoxy(2, 3); printf("<---------------MAIN MENU--------------->");
		gotoxy(3, 3); printf("||                                     ||");
		gotoxy(4, 3); printf("||-------(1) Mananger------------------||");
		gotoxy(5, 3); printf("||                                     ||");
		gotoxy(6, 3); printf("||-------(2) Booking operator----------||");
		gotoxy(7, 3); printf("||                                     ||");
		gotoxy(8, 3); printf("||-------(3) Check-in/out operator-----||");
		gotoxy(9, 3); printf("||                                     ||");
		gotoxy(10, 3); printf("||-------(0) Exit----------------------||");
		gotoxy(11, 3); printf("||                                     ||");
		gotoxy(12, 3); printf("<--------------------------------------->");
		//the sub-interface:
		gotoxy(2, 46); printf("<------------Sub-Menu----------->");
		gotoxy(3, 46); printf("||                             ||");
		gotoxy(4, 46); printf("||---");
		setcolor(12, 0); printf("(8) Rewrite rooms info");
		setcolor(7, 0); printf("----||");
		gotoxy(5, 46); printf("||                             ||");
		gotoxy(6, 46); printf("||---(9) Print out rooms info--||");
		gotoxy(7, 46); printf("||                             ||");
		gotoxy(8, 46); printf("<------------------------------->");
		gotoxy(10, 47); printf("Selecting your identity: < >\b\b");
		if (scanf_s("%d", &option) == 1) {
			if (option < 0 || (option > 3 && option != 8 && option != 9)) {
				fflush(stdin);
				gotoxy(11, 47); printf("Warning: wrong input character!");
				Sleep(2000); continue;
			}
			else break;
		}
		else {
			option_char = getchar();
			//'P' means 'print'
			if (option_char == 'p' || option_char == 'P') {
				fflush(stdin);
				Print_All(); continue;
			}
			//'R' means 'reduce'
			else if (option_char == 'r' || option_char == 'R') {
				fflush(stdin);
				Reduce_All(); continue;
			}
			//'N' means 'note'
			else if (option_char == 'n' || option_char == 'N') {
				fflush(stdin);
				Note_Print(); continue;
			}
			//'H' means 'hashtable'
			else if (option_char == 'h' || option_char == 'H') {
				fflush(stdin);
				Print_All_hash(Hasharray, n); continue;
			}
			//'C' means 'customer'
			else if (option_char == 'c' || option_char == 'C') {
				fflush(stdin);
				Print_All_Customer(); continue;
			}
			//'X' means...
			else if (option_char == 'x' || option_char == 'X') {
				fflush(stdin);
				Check_R(Room_Board); continue;
			}
			//'Y' means...
			else if (option_char == 'y' || option_char == 'Y') {
				fflush(stdin);
				Check_U(Room_Board); continue;
			}
			else {
				fflush(stdin);
				gotoxy(11, 47); printf("Warning: wrong input character!");
				Sleep(2000); continue;
			}
		}

	}
	switch (option) {
	case 0:
		gotoxy(11, 46); printf("Have a nice day, see you again.");
		Room_Board_Free(Room_Board);
		Hashtable_Free(Hasharray);
		Sleep(3000); exit(0);
	case 1:
		Manager_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 2:
		Booking_Operator_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 3:
		Checker_Operator_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 8:
		gotoxy(16, 2); printf("Rewriting is an irreversible process, are you sure? y/n");
		char confirm;
		do {
			confirm = getch();
			fflush(stdin);
		} while (confirm != 'y' && confirm != 'n');
		if (confirm == 'n')
			Main_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
		else if (confirm == 'y') {
			//reduce basic parameters of hotel:
			Room_Info_Initialization(Room_Board);
			File_Room_Info_Write(Room_Board);
			Hotel_Parameters_Initialization(parameters);
			File_Parameters_Info_Write(parameters);
			Hotel_Statistics_Initialization(income_x_customers);
			File_Statistics_Info_Write(income_x_customers);
			//reduce customer information:
			FILE *clean;
			clean = fopen("customer database.txt", "w");
			fclose(clean);
			clean = fopen("reg.bat", "wb");
			fclose(clean);
			clean = fopen("in hotel.bat", "wb");
			fclose(clean);
			clean = fopen("VIP wait.txt", "w");
			fclose(clean);
			//hashtable free:
			Hashtable_Free(Hasharray);
			gotoxy(17, 2); printf("Everything rewriting success, exiting...");
			Sleep(1500); exit(0);
		}
		Main_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 9:
		File_Room_Info_Read(Room_Board);
		Room_Demonstration(Room_Board);
		Sleep(5000);
		Main_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	default: break;
	}
}
//function list (about Hashtable):
void Hash_Expand(struct Customer_Node **Hasharray, struct customer *target, int *n) {
	//hasharray //target unit //location in file
	//calculate the hash key
	int key;
	key = Hash_Key_Function(target->name);
	//adress variable 'head' (and it does is a 'head')
	struct Customer_Node *head;
	head = Hasharray[key];
	//add node in the certain linked list
	while ((head->next) != NULL)
		head = head->next;
	head->next = (struct Customer_Node*)malloc(sizeof(struct Customer_Node));
	head = head->next;
	head->next = NULL;
	//value assign...
	head->position = *n;
	strcpy(head->name, target->name);
	strcpy(head->phonenumber, target->phonenumber);
	strcpy(head->VIP_number, target->VIP_number);
	//value assign...
	head->status = target->status;
	head->VIP_status = target->VIP_status;
	//value assign...
	printf("HashTable is expanded.\n");
	//location in file increases
	(*n)++;
}

int Hash_Key_Function(char *name) {
	int key, plus = 0;
	//plus: total ASCII value
	for (int i = 0; i < strlen(name); i++) {
		int value = (int)name[i];
		plus += value;
	}
	//key: average ASCII value minus 60
	key = plus / strlen(name);
	key -= 60;
	return key;
}

static void Hashtable_Free(struct Customer_Node **Hasharray) {
	struct Customer_Node *head, *move, *store;
	for (int i = 0; i < 10; i++) {
		head = Hasharray[i];
		move = head;
		while ((move->next) != NULL) {
			store = move->next;
			free(move);
			move = store;
		}
	}
	free(Hasharray);
}
//fuction list (hotel parameters, all kinds of prices):
void Hotel_Parameters_Initialization(struct room_price *parameters) {
	parameters->price1 = 150;
	parameters->price2 = 200;
	parameters->price3 = 300;
	parameters->price_vip = 500;
	parameters->group_price = 0.8;	//ratio
	parameters->price_after_week = 0.8;	//ratio
	parameters->price_after_month = 0.6;	//ratio
}

void File_Parameters_Info_Write(struct room_price *parameters) {
	//Write the 'parameters' into the file
	FILE *ptr_p;
	ptr_p = fopen("hotel parameters.txt", "w");
	if (ptr_p == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}

	else
		fwrite(parameters, sizeof(struct room_price), 1, ptr_p);
	fclose(ptr_p);
	fflush(stdin);
}

void File_Parameters_Info_Read(struct room_price *parameters) {
	//Read the 'parameters' from the file
	FILE *ptr_p;
	ptr_p = fopen("hotel parameters.txt", "r");
	if (ptr_p == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	else
		fread(parameters, sizeof(struct room_price), 1, ptr_p);
	fclose(ptr_p);
	fflush(stdin);
}
//function list (hotel statistics):
void Hotel_Statistics_Initialization(struct hotel_statistics *income_x_customers) {
	income_x_customers->history_customers = 0;
	income_x_customers->total_income = 0;
}

void File_Statistics_Info_Write(struct hotel_statistics *income_x_customers) {
	//Write the 'total income & history customers' into the file
	FILE *ptr_s;
	ptr_s = fopen("hotel statistics.txt", "w");
	if (ptr_s == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	else
		fwrite(income_x_customers, sizeof(struct hotel_statistics), 1, ptr_s);
	fclose(ptr_s);
	fflush(stdin);
}

void File_Statistics_Info_Read(struct hotel_statistics *income_x_customers) {
	//Read the 'total income & history customers' from file
	FILE *ptr_s;
	ptr_s = fopen("hotel statistics.txt", "r");
	if (ptr_s == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	else
		fread(income_x_customers, sizeof(struct hotel_statistics), 1, ptr_s);
	fclose(ptr_s);
	fflush(stdin);
}
//function list (room board demonstration):
void Room_Info_Initialization(struct room **Room_Board) {
	//initialization of the 2D array: 'Room_Board'
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 20; j++) {
			if (j < 2) Room_Board[i][j].class = 'V';		//room class: VIP
			else if (j < 8) Room_Board[i][j].class = 49;	//room class: *
			else if (j < 14) Room_Board[i][j].class = 50;	//room class: **
			else if (j < 20) Room_Board[i][j].class = 51;	//room class: ***
			Room_Board[i][j].status = 'N';
			//status type: 
			//N: no customer and register	color: white
			//R: on registration	color: green
			//U: currently in use	color: red
		}
	}
}

void Room_Demonstration(struct room **Room_Board) {
	//room information demonstration (merely depends on the variable: 'Room_Board' passed in)
	gotoxy(14, 5); printf("Hotel Information:");
	for (int i = 0; i < 6; i++) {
		gotoxy(15 + i * 2, 2);	printf(" ");
		for (int j = 0; j != 20 * 3 + 1; j++)
			printf("-");
		gotoxy(16 + i * 2, 2);
		if (5 - i == 0) {
			setcolor(14, 0); printf("G");
			setcolor(7, 0);
		}
		else
			printf("%d", 5 - i);
		for (int j = 0; j < 20; j++) {
			printf("|");
			if (Room_Board[i][j].status == 'N'){
				setcolor(0, 7); printf(" %c", Room_Board[i][j].class);
				setcolor(7, 0);
			}
			else if (Room_Board[i][j].status == 'R'){
				setcolor(0, 2); printf(" %c", Room_Board[i][j].class);
				setcolor(7, 0);
			}
			else if (Room_Board[i][j].status == 'U'){
				setcolor(0, 4); printf(" %c", Room_Board[i][j].class);
				setcolor(7, 0);
			}
		}
		printf("|");
	}
	gotoxy(27, 3);
	for (int i = 0; i != (20 * 3 + 1); i++)
		printf("-");
	gotoxy(28, 3);
	for (int i = 0; i != 20; i++)
		printf(" %02d", i + 1);
}

void Room_Board_Free(struct room **Room_Board) {
	//free memory space
	for (int i = 0; i < 6; i++)
		free(Room_Board[i]);
	free(Room_Board);
}

void File_Room_Info_Write(struct room **Room_Board) {
	//Write the 'Room_Board' into the file
	FILE *ptr_room_info;
	ptr_room_info = fopen("room info.txt", "w");
	if (ptr_room_info == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	else {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 20; j++)
				fwrite(&Room_Board[i][j], sizeof(struct room), 1, ptr_room_info);
		}
	}
	fclose(ptr_room_info);
	fflush(stdin);
}

void File_Room_Info_Read(struct room **Room_Board) {
	//read the 'Room_Board' from the file
	FILE *ptr_room_info;
	ptr_room_info = fopen("room info.txt", "r");
	if (ptr_room_info == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	else {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 20; j++)
				fread(&Room_Board[i][j], sizeof(struct room), 1, ptr_room_info);
		}
	}
	fclose(ptr_room_info);
}
//function list (account):
void File_Staff_Write(int user_identity) {
	struct staff_use user, compare;
	FILE *ptr_staff;
	fflush(stdin);
	system("cls");
	//identity set process:
	user.identity = user_identity;
	//name set process:
	while (1) {
		int restart = 0, No_Space = 0;
		printf("Please enter the name of your account:\n\t");
		gets(user.name);
		//limitation: the length of user's name
		if (strlen(user.name) >= 10) {
			fflush(stdin);
			printf("Please try again set account name less than 10 characters.\n");
			Sleep(2000); system("cls");
			continue;
		}
		//limitation: 'enter' key in user's name
		else if (user.name[0] == '\0') {
			fflush(stdin);
			printf("Please try again set account name.");
			Sleep(2000); system("cls");
			continue;
		}
		//open file (read only)
		ptr_staff = fopen("staff.txt", "r");
		//Test the success of opening the file
		if (ptr_staff == NULL) {
			printf("There was a problem opening the file, please restart the program.\n\n");
			Sleep(3000); exit(0);
		}
		//judge on identical account
		while (fread(&compare, sizeof(struct staff_use), 1, ptr_staff)) {
			if (strcmp(user.name, compare.name) == 0 && user.identity == compare.identity) {
				restart = 1; break;
			}
		}
		fclose(ptr_staff);
		if (restart) {
			fflush(stdin);	//empty the buffer
			printf("This account has been already in existence, try another.");
			Sleep(2000);
			system("cls"); continue;
		}
		//judge on spaces
		for (int i = 0; i < strlen(user.name); i++) {
			if (user.name[i] == 32)		//this position is 'space'
				No_Space = 1;			//'space' key exists
		}
		if (No_Space) {
			fflush(stdin);
			printf("Space in the account name is not allowed!\n");
			Sleep(2000);
			system("cls"); continue;
		}
		else break;
	}
	fflush(stdin);
	//password set process:
	while (1) {
		int No_Space = 0;
		printf("Please enter the password of your account:\n\t");
		gets(user.password);	//record user's password by function: 'gets()'
		//limitation: the length of user's password
		if (strlen(user.password) >= 10) {
			fflush(stdin);
			printf("Please try again set account password less than 10 characters.");
			Sleep(2000);
			system("cls"); continue;
		}
		//limitation: 'enter' key in user's password
		else if (user.password[0] == '\0') {
			fflush(stdin);
			printf("Please try again set account password.");
			Sleep(2000); gotoxy(2, 0);
			continue;
		}
		//judge on spaces
		for (int i = 0; i < strlen(user.password); i++) {
			if (user.password[i] == 32)	//'space' exists
				No_Space = 1;			//'space' exists
		}
		if (No_Space) {		//space in the password is banned
			fflush(stdin);	//empty the buffer
			printf("Space in the account password is not allowed!\n");
			Sleep(2000);
			system("cls"); continue;
		}
		else break;
	}
	fflush(stdin);
	//write information into the file, open file (append)
	ptr_staff = fopen("staff.txt", "a");
	//Test the success of opening the file
	if (ptr_staff == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	else {
		fwrite(&user, sizeof(struct staff_use), 1, ptr_staff);
		fclose(ptr_staff);
		printf("file updating success!");
		Sleep(2000);
	}
	fflush(stdin);
	//back to ... interface again
}

int File_Staff_Read(int user_identity, struct staff_use *person) {
	//function for login process, login! login!! login!!!
	int n = 0, Try_Time;	//'n': number of accounts
	int Account_Exist = 0, Password_Correct = 0;
	//read form file to variable 'person'
	struct staff_use user, empty, compare;
	FILE *ptr_staff;
	fflush(stdin);
	system("cls");
	//identity set process:
	user.identity = user_identity;
	//judge on empty file
	ptr_staff = fopen("staff.txt", "r");
	if (ptr_staff == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	if (!fread(&empty, sizeof(struct staff_use), 1, ptr_staff)) {
		printf("No account in the file, back to the menu...");
		Sleep(3000);
		//as the file is empty, return 1.
		return 1;
	}
	//calculate number of accounts
	else {
		//move the pointer (in file) to the head of the file
		rewind(ptr_staff);
		printf("Opening file success!\n");
		while (fread(&empty, sizeof(struct staff_use), 1, ptr_staff))
			n++;
	}
	fflush(stdin);
	//name inspection process:
	rewind(ptr_staff);
	Try_Time = 0;
	while (1) {
		printf("Please enter your account name.\nInput: ");
		gets(user.name);
		//limitation: the length of user's name
		if (strlen(user.name) >= 10) {
			fflush(stdin);
			printf("The account name is less than 10 characters.\n");
			Sleep(2000);
			system("cls"); continue;
		}
		rewind(ptr_staff);
		for (int i = 0; i < n; i++) {
			fread(&compare, sizeof(struct staff_use), 1, ptr_staff);
			if (strcmp(user.name, compare.name) == 0 && user.identity == compare.identity) {
				Account_Exist = 1; break;
			}
		}
		if (Account_Exist == 1) {
			//the account is in the file
			printf("Reading account success!\n"); break;
		}
		else {
			//the account is not found
			fflush(stdin);
			printf("\nAccount doesn't exist, check your account.\n");
			Try_Time++;	//time of error increases
			if (Try_Time == 3) {
				printf("3 times error, quit the system...");
				Sleep(3000); exit(0);
			}
			else continue;
		}
	}
	fflush(stdin);
	//password inspection process:
	Try_Time = 0;
	while (1) {
		printf("Please enter your account password.\nInput: ");
		gets(user.password);
		//limitation: the length of user's password
		if (strlen(user.password) >= 10) {
			fflush(stdin);
			printf("The account password is less than 10 characters.\n");
			Sleep(2000);
			system("cls"); continue;
		}
		if (!strcmp(user.password, compare.password))
			Password_Correct = 1;
		if (Password_Correct) {
			printf("Password inspection success!\n"); break;
		}
		else {
			//password is not correct
			fflush(stdin);
			printf("\nPassword isn't correct\n\n");
			Try_Time++;
			if (Try_Time == 3) {
				printf("3 times error, quit the system...");
				Sleep(3000); exit(0);
			}
			else continue;
		}
	}
	fflush(stdin);
	//current: someone has logged in!
	strcpy(person->name, user.name);	//string assigning
	strcpy(person->password, user.password);	//string assigning
	person->identity = user.identity;	//'int' variable assigning
	fclose(ptr_staff);	//close the file
	//determine which type of staff
	if ((*person).identity == 1)
		Manager_Login_Satus = 1;
	else if ((*person).identity == 2)
		BO_Login_Satus = 1;
	else if ((*person).identity == 3)
		CO_Login_Satus = 1;
	//"login record" updating:
	struct time current_time;
	FILE *ptr_login_record;
	fflush(stdin);
	ptr_login_record = fopen("staff login record.txt", "a");
	if (ptr_staff == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	fwrite(person, sizeof(struct staff_use), 1, ptr_login_record);		//write personal information
	Call_Time(&current_time);
	fwrite(&current_time, sizeof(struct time), 1, ptr_login_record);	//write login time
	fclose(ptr_login_record);
	fflush(stdin);
	//back to ... interface again
	return 0;
}
//function list (manager menu):
void Manager_Menu(struct room **Room_Board, struct room_price *parameters, struct hotel_statistics *income_x_customers, struct Customer_Node **Hasharray, int *n) {
	int option;
	while (1) {
		system("cls");
		Room_Demonstration(Room_Board);
		//the manager interface:
		gotoxy(0, 3); printf("***Hotel Management Information System***");
		gotoxy(2, 3); printf("<----------MANAGER MENU--------->");
		gotoxy(3, 3); printf("||                             ||");
		gotoxy(4, 3); printf("||-(1) Mananger Account Create-||");
		gotoxy(5, 3); printf("||                             ||");
		gotoxy(6, 3); printf("||-");
		if (Manager_Login_Satus) {	//12: red
			setcolor(12, 0); printf("(2) Manager Account Login");
		}
		else if (!Manager_Login_Satus) {	//14: yello
			setcolor(14, 0); printf("(2) Manager Account Login");
		}
		setcolor(7, 0); printf("---||");
		gotoxy(7, 3); printf("||                             ||");
		gotoxy(8, 3); printf("||-");
		if (Manager_Login_Satus) {
			setcolor(14, 0); printf("(3) Manager Account Logout");
		}
		else if (!Manager_Login_Satus) {
			setcolor(12, 0); printf("(3) Manager Account Logout");
		}
		setcolor(7, 0); printf("--||");
		gotoxy(9, 3); printf("||                             ||");
		gotoxy(10, 3); printf("||-(0) Back To Main Menu-------||");
		gotoxy(11, 3); printf("||                             ||");
		gotoxy(12, 3); printf("<------------------------------->");
		if (Manager_Login_Satus) {
			//the sub-interface:
			gotoxy(2, 38); printf("<----Account information---->");
			gotoxy(3, 38); printf("||------Account Name-------||");
			gotoxy(4, 38); printf("||'   %10s          '||", Current_User.name);
			gotoxy(5, 38); printf("||-(4) VIP Customers-------||");	//still need a further interface
			gotoxy(6, 38); printf("||-(5) Amend Room Info-----||");	//'room class' and 'class price'
			gotoxy(7, 38); printf("||-(6) Amend Booking Info--||");	//'booking discount'(month prior/group booking)
			gotoxy(8, 38); printf("||-(7) Business Statistics-||");	//total income, total customers
			gotoxy(9, 38); printf("<--------------------------->");
		}
		gotoxy(11, 39); printf("Selecting your operation: < >\b\b");
		//make desicion
		if (scanf_s(" %d", &option) != 1) {
			fflush(stdin);
			gotoxy(12, 39); printf("Warning: wrong input character!");
			Sleep(2000); continue;
		}
		else {
			if (!Manager_Login_Satus) {
				gotoxy(12, 39);
				if (option == 3) {
					fflush(stdin);
					printf("No account currently log in.");
					Sleep(2000); continue;
				}
				else if (option < 0 || option > 3) {
					fflush(stdin);
					printf("Warning: wrong input character!");
					Sleep(2000); continue;
				}
				else break;
			}
			else if (Manager_Login_Satus) {
				gotoxy(12, 39);
				if (option == 2) {
					fflush(stdin);
					printf("Please log out first.");
					Sleep(2000); continue;
				}
				else if (option < 0 || option > 7) {
					fflush(stdin);
					printf("Warning: wrong input character!");
					Sleep(2000); continue;
				}
				else break;
			}
		}
	}
	switch (option) {
	case 0:
		//log out first
		if (Manager_Login_Satus)
			Manager_Login_Satus = !Manager_Login_Satus;
		//back to 'main menu'
		Main_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 1:
		File_Staff_Write(1);
		Manager_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 2:
		if (File_Staff_Read(1, &Current_User) == 1)
			Manager_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
		Manager_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 3:
		if (Manager_Login_Satus)
			Manager_Login_Satus = !Manager_Login_Satus;
		Manager_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 4:
		VIP_Handle(Hasharray);
		printf("Hadling VIP application success!");
		Sleep(2000);
		Manager_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 5:
		Room_Info_Amend(Room_Board);
		Manager_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 6:
		File_Parameters_Info_Read(parameters);
		manager_amend_booking_info(parameters);
		Manager_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 7:
		File_Statistics_Info_Read(income_x_customers);
		printf("Total income: %d ", income_x_customers->total_income);
		printf("History customers: %d", income_x_customers->history_customers);
		Sleep(5000);
		Manager_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	default: break;
	}
}

void VIP_Handle(struct Customer_Node **Hasharray) {
	int key;
	FILE *ptr_wait;
	FILE *ptr_customer;
	struct customer customer;
	struct Customer_Node *head;
	ptr_wait = fopen("VIP wait.txt", "r+");
	if (ptr_wait == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	while (fread(&customer, sizeof(struct customer), 1, ptr_wait)) {
		key = Hash_Key_Function(customer.name);
		head = Hasharray[key];
		while ((head->next) != NULL) {
			head = head->next;
			if (!strcmp(customer.name, head->name) && !strcmp(customer.phonenumber, head->phonenumber)) {
				strcpy(customer.VIP_number, head->VIP_number);
				customer.status = head->status;
				customer.VIP_status = 'V';
				head->VIP_status = 'V'; break;
			}
		}
		ptr_customer = fopen("customer database.txt", "r+");
		fseek(ptr_customer, (head->position)*sizeof(struct customer), SEEK_SET);
		fwrite(&customer, sizeof(struct customer), 1, ptr_customer);
		fclose(ptr_customer);
	}
	fclose(ptr_wait);
}

void Room_Info_Amend(struct room **Room_Board) {
	//ask for manager's will (target room)
	int judge, read, room[3];
	char confirm, y;
	while (1) {
		system("cls");
		Room_Demonstration(Room_Board);
		gotoxy(0, 0); printf("Sir, which room needs to be amended?\nSelecting room: ");
		judge = 0; read = 0;
		do {
			if (scanf_s(" %d", &room[read++]) != 1) {
				judge = 1; break;
			}
		} while ((y = getchar()) != '\n');
		if (judge) {
			fflush(stdin);
			printf("Wrong form of room, characters are invalid!");
			Sleep(1000); continue;
		}
		else if (read != 2 || (read == 2 && ((room[0] < 0 || room[0] > 5) || (room[1] < 0 || room[1] > 20)))) {
			fflush(stdin);
			printf("Wrong form of room, input 2 numbers!");
			Sleep(1000); continue;
		}
		//room entered is correct
		printf("Target room is floor: %d, No.%d, Right? y/n", room[0], room[1]);
		do {
			confirm = getch();
			fflush(stdin);
		} while (confirm != 'y' && confirm != 'n');
		if (confirm == 'y')
			break;
		else if (confirm == 'n') {
			fflush(stdin);
			continue;
		}
	}
	//check 2D array: 'Room_Board'
	printf("\nThe class of this room is: ");
	if (Room_Board[5 - room[0]][room[1] - 1].class == 51)
		printf("***");
	else if (Room_Board[5 - room[0]][room[1] - 1].class == 50)
		printf("**");
	else if (Room_Board[5 - room[0]][room[1] - 1].class == 49)
		printf("*");
	else if (Room_Board[5 - room[0]][room[1] - 1].class == 'V')
		printf("VIP");
	//ask for manager's will (target class)
	char VIP;
	int New_Class;
	while (1) {
		gotoxy(5, 0); printf("                               ");
		gotoxy(4, 0); printf("Your expectation is: < >\b\b");
		if (scanf_s(" %d", &New_Class) != 1) {
			VIP = getchar();
			if (VIP == 'v' || VIP == 'V') {
				fflush(stdin); break;
			}
			else {
				fflush(stdin);
				printf("Warning: wrong input character!");
				Sleep(1000); continue;
			}
		}
		else if (New_Class < 0 || New_Class > 3) {
			fflush(stdin);
			printf("Warning: wrong input character!");
			Sleep(1000); continue;
		}
		else
			break;
	}
	//amend 2D array: 'Room_Board'
	if (New_Class < 4)
		Room_Board[5 - room[0]][room[1] - 1].class = 48 + New_Class;
	if (VIP == 'v' || VIP == 'V')
		Room_Board[5 - room[0]][room[1] - 1].class = 'V';
	File_Room_Info_Write(Room_Board);
	//real-time room information
	Room_Demonstration(Room_Board);
	//continue do this operation?
	char again;
	gotoxy(5, 0); printf("*Would you tend to continue? y/n*");
	do {
		again = getch();
		fflush(stdin);
	} while (again != 'y' && again != 'n');
	if (again == 'y')
		Room_Info_Amend(Room_Board);
	else if (again == 'n')
		return;
}

void manager_amend_booking_info(struct room_price *parameters) {
	int class_choice;
	system("cls");
	//interface:
	printf("\t***Price Amend***\n\n");
	//int
	printf("1. price: class '*' . %d\n", parameters->price1);
	printf("2. price: class '**' . %d\n", parameters->price2);
	printf("3. price: class '***' . %d\n", parameters->price3);
	printf("4. price: class 'VIP' . %d\n", parameters->price_vip);
	//float
	printf("5. price: Group Price . %f\n", parameters->group_price);
	printf("6. price: registration after a week . %f\n", parameters->price_after_week);
	printf("7. price: registration after a month . %f\n", parameters->price_after_month);
	printf("\n0. back to manager menu.");
	//selection
	printf("\n\nPlease choose an operation:\n");
	while ((scanf_s(" %d", &class_choice) != 1) || (class_choice < 0 || class_choice > 7)) {
		fflush(stdin);
		printf("Your choice is invalid, please make sure your choice is from 0-7:\n");
	}
	if (class_choice == 0) {
		fflush(stdin);
		printf("Back to manager menu...");
		Sleep(1000); return;
	}
	printf("Your will is: ");
	if (class_choice == 1) {
		while (scanf_s(" %d", &(parameters->price1)) != 1) {
			fflush(stdin);
			printf("Your choice is invalid");
			printf("Please make your choice again:\n");
		}
	}
	if (class_choice == 2) {
		while (scanf_s(" %d", &parameters->price2) != 1) {
			fflush(stdin);
			printf("Your choice is invalid");
			printf("Please make your choice again:\n");
		}
	}
	if (class_choice == 3) {
		while (scanf_s(" %d", &parameters->price1) != 1) {
			fflush(stdin);
			printf("Your choice is invalid");
			printf("Please make your choice again:\n");
		}
	}
	if (class_choice == 4) {
		while (scanf_s(" %d", &parameters->price_vip) != 1) {
			fflush(stdin);
			printf("Your choice is invalid");
			printf("Please make your choice again:\n");
		}
	}
	if (class_choice == 5) {
		while (scanf_s(" %f", &parameters->group_price) != 1) {
			fflush(stdin);
			printf("Your choice is invalid");
			printf("Please make your choice again:\n");
		}
	}
	if (class_choice == 6) {
		while (scanf_s(" %f", &parameters->price_after_week) != 1 || parameters->price_after_week >= 1.0) {
			fflush(stdin);
			printf("Your choice is invalid");
			printf("Please make your choice again:\n");
		}
	}
	if (class_choice == 7) {
		while (scanf_s(" %f", &parameters->price_after_month) != 1 || parameters->price_after_week >= 1.0) {
			fflush(stdin);
			printf("Your choice is invalid");
			printf("Please make your choice again:\n");
		}
	}
	File_Parameters_Info_Write(parameters);
	printf("hotel parameters amending complete!");
	//continue do this operation?
	char again;
	printf("*Would you tend to continue? y/n*");
	do {
		again = getch();
		fflush(stdin);
	} while (again != 'y' && again != 'n');
	if (again == 'y')
		manager_amend_booking_info(parameters);
	else if (again == 'n')
		return;
}
//function list (booking operator menu):
void Booking_Operator_Menu(struct room **Room_Board, struct room_price *parameters, struct hotel_statistics *income_x_customers, struct Customer_Node **Hasharray, int *n) {
	int option;
	while (1) {
		system("cls");
		Room_Demonstration(Room_Board);
		//the booking operator interface:
		gotoxy(0, 3); printf("***Hotel Management Information System***");
		gotoxy(2, 3); printf("<-----BOOKING OPERATOR MENU----->");
		gotoxy(3, 3); printf("||                             ||");
		gotoxy(4, 3); printf("||---(1) BO Account Create-----||");
		gotoxy(5, 3); printf("||                             ||");
		gotoxy(6, 3); printf("||---(2) BO Account Login------||");
		gotoxy(7, 3); printf("||                             ||");
		gotoxy(8, 3); printf("||---(3) BO Account Logout-----||");
		gotoxy(9, 3); printf("||                             ||");
		gotoxy(10, 3); printf("||---(0) Back To Main Menu-----||");
		gotoxy(11, 3); printf("||                             ||");
		gotoxy(12, 3); printf("<------------------------------->");
		if (BO_Login_Satus) {
			//the sub-interface:
			gotoxy(2, 38); printf("<----Account information---->");
			gotoxy(3, 38); printf("||------Account Name-------||");
			gotoxy(4, 38); printf("||'   %10s          '||", Current_User.name);
			gotoxy(5, 38); printf("||-(4) Register A Booking--||");	//still need a further interface
			gotoxy(6, 38); printf("<--------------------------->");
		}
		gotoxy(11, 39); printf("Selecting your operation: < >\b\b");
		//make desicion
		if (scanf_s(" %d", &option) != 1) {
			fflush(stdin);
			gotoxy(12, 39); printf("Warning: wrong input character!");
			Sleep(2000); continue;
		}
		else {
			if (!BO_Login_Satus) {
				if (option < 0 || option > 3) {
					fflush(stdin);
					gotoxy(12, 39); printf("Warning: wrong input character!");
					Sleep(2000); continue;
				}
				else break;
			}
			if (BO_Login_Satus) {
				if (option < 0 || option > 4) {
					fflush(stdin);
					gotoxy(12, 39); printf("Warning: wrong input character!");
					Sleep(2000); continue;
				}
				else break;
			}
		}
	}
	switch (option) {
	case 0:
		//log out first
		if (BO_Login_Satus)
			BO_Login_Satus = !BO_Login_Satus;
		//back to main menu
		Main_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 1:
		File_Staff_Write(2);
		Booking_Operator_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 2:
		if (File_Staff_Read(2, &Current_User) == 1)
			Booking_Operator_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
		Booking_Operator_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 3:
		if (BO_Login_Satus)
			BO_Login_Satus = !BO_Login_Satus;
		Booking_Operator_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 4:
		Registration_Interface(Room_Board, parameters, Hasharray, n);
		Booking_Operator_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	default: break;
	}
}

void Registration_Interface(struct room **Room_Board, struct room_price *parameters, struct Customer_Node **Hasharray, int *n) {
	//location in file: "*n"
	//create customer database
	gotoxy(2, 38); printf("<----Account information---->");
	gotoxy(3, 38); printf("||------Account Name-------||");
	gotoxy(4, 38); printf("||'   %10s          '||", Current_User.name);
	gotoxy(5, 38); printf("<--------------------------->");
	//main body:
	struct customer customer;
	struct registration reg;
	/*'customer': the structure for recording customer info*/
	FILE *ptr_customer;
	fflush(stdin);
	system("cls");
	//clean the screen!
	while (1) {	//while loop: customer info
		//ask for customer's name and phone number
		int judge_valid = Customer_Info_Input(&customer);
		fflush(stdin);
		if (judge_valid) break;
		else continue;
	}
	//call the hashtable:
	int judge = 0, key;
	struct Customer_Node *head;
	key = Hash_Key_Function(customer.name);
	head = Hasharray[key];
	while ((head->next) != NULL) {
		head = head->next;
		if (!strcmp(customer.name, head->name) && !strcmp(customer.phonenumber, head->phonenumber)) {
			if (head->status == 'U') {
				printf("\nYou have checked-in already.");
				Sleep(2000); return;
			}
			else if (head->status == 'R') {
				printf("\nYou have registed already.");
				Sleep(2000); return;
			}
			else {
				judge = 1; break;
			}
		}
	}
	//exist (in the file & hashtable)
	if (judge) {
		//VIP number: "000000" or "Random_Six"
		strcpy(customer.VIP_number, head->VIP_number);
		customer.VIP_status = head->VIP_status;
		customer.status = 'N';
	}
	//not exist, create new customer data in database
	else if (!judge)
		New_Customer(&customer, Hasharray, n);
	//customer info (VIP status) demonstration:
	gotoxy(6, 38); printf("<----Customer information--->");
	gotoxy(7, 38); printf("||------Customer Name------||");
	gotoxy(8, 38); printf("||'   %10s          '||", customer.name);
	gotoxy(9, 38); printf("||--------VIP Status-------||");
	gotoxy(10, 38);
	if (customer.VIP_status == 'W')
		printf("||'       Auditing        '||");
	else if (customer.VIP_status == 'N')
		printf("||'        Non-VIP        '||");
	else if (customer.VIP_status == 'V')
		printf("||'          VIP          '||");
	gotoxy(11, 38); printf("<--------------------------->");
	//room information & price list
	Room_With_Price(Room_Board, parameters);
	//registration process:
	//date of arrival
	int year, month, day, date_price_level;
	date_price_level = Arrival_Date(&year, &month, &day);	/*record "arrival date", and date price level (2, 7, 30)*/
	//target class of room
	char VIP = 0, y;
	int r, c, basic;
	int New_Class, number = 0;
	while (1) {
		printf("\nWhich class you have demand for?");
		if (scanf_s(" %d", &New_Class) != 1) {
			y = getchar();
			if (customer.VIP_status == 'V' && (y == 'v' || y == 'V')) {
				VIP = 'V';
				number = 0;
			}
			else {
				fflush(stdin);
				printf("Warning: wrong input character!");
				Sleep(1000); continue;
			}
		}
		else if (New_Class < 0 || New_Class > 3) {
			fflush(stdin);
			printf("Warning: wrong input character!");
			Sleep(1000); continue;
		}
		else
			number = 1;
		//'random' or 'target'
		int sure;
		char class;
		if (number && New_Class < 4) {
			basic = New_Class;
			class = New_Class + 48;
			sure = Random_Allocation(Room_Board, class, &r, &c, 1);
		}
		else if (!number && VIP == 'V') {
			basic = 4;
			sure = Random_Allocation(Room_Board, VIP, &r, &c, 1);
		}
		if (sure)
			break;
		else if (!sure){
			fflush(stdin);
			printf("\nSorry, hotel has run out of rooms in this class, try another.");
			continue;
		}
	}
	fflush(stdin);
	//'R' change
	customer.status = 'R';
	if (judge) {
		//amend in hashtable
		head->status = 'R';
		//amend in file
		ptr_customer = fopen("customer database.txt", "r+");
		if (ptr_customer == NULL) {
			printf("There was a problem opening the file, please restart the program.\n\n");
			Sleep(3000); exit(0);
		}
		fseek(ptr_customer, (head->position)*sizeof(struct customer), SEEK_SET);
		fwrite(&customer, sizeof(struct customer), 1, ptr_customer);
		fclose(ptr_customer);
	}
	else if (!judge) {
		//add in: hashtable
		Hash_Expand(Hasharray, &customer, n);
		//add in: file
		ptr_customer = fopen("customer database.txt", "a+");
		if (ptr_customer == NULL) {
			printf("There was a problem opening the file, please restart the program.\n\n");
			Sleep(3000); exit(0);
		}
		fwrite(&customer, sizeof(struct customer), 1, ptr_customer);
		fclose(ptr_customer);
	}
	//time to write 'registration info' into a file!
	//position
	reg.r = r;
	reg.c = c;
	//customer info
	strcpy(reg.registrant.name, customer.name);
	strcpy(reg.registrant.phonenumber, customer.phonenumber);
	strcpy(reg.registrant.VIP_number, customer.VIP_number);
	reg.registrant.status = customer.status;
	reg.registrant.VIP_status = customer.VIP_status;
	//date
	reg.regist_day.year = year;
	reg.regist_day.month = month;
	reg.regist_day.day = day;
	//price
	reg.price = Calculate_Price(date_price_level, basic, parameters);	/*further calculate the therotical price*/
	//write in, file updating:
	FILE *ptr_reg;
	ptr_reg = fopen("reg.bat", "ab");
	if (ptr_reg == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	fwrite(&reg, sizeof(struct registration), 1, ptr_reg);
	fclose(ptr_reg);
	Check_R(Room_Board);
	printf("\nRegistration Complete.");
	Sleep(2000);
}

int Arrival_Date(int *y, int *m, int *d) {
	//assign for variables (date), and return value represents for how many days left before the customer arrive
	char confirm, c;
	int judge, read, date[4], jod;
	while (1) {
		printf("\nWhich day you'll arrive?\n");
		judge = 0; read = 0;
		do {
			if (scanf_s(" %d", &date[read++]) != 1) {
				judge = 1; break;
			}
		} while ((c = getchar()) != '\n');
		if (judge) {
			fflush(stdin);
			printf("\nWrong form of date, characters are invalid!");
			Sleep(1000); continue;
		}
		else if (read != 3) {
			fflush(stdin);
			printf("\nWrong form of date, please check again");
			Sleep(1000); continue;
		}
		else {
			fflush(stdin);
			//assign to each adress:
			*y = date[0];
			*m = date[1];
			*d = date[2];
		}
		jod = Judge_On_Date(*y, *m, *d, 0);
		if (jod == 0 || jod == 1) {
			fflush(stdin);
			printf("\nWrong form of date, please check again");
			Sleep(1000); continue;
		}
		else {
			printf("Correct form of date: %d. %d. %d\n", *y, *m, *d);
			break;
		}
	}
	fflush(stdin);
	return jod; /*after "less than a week" or "a week" or "a month"*/
}

int Judge_On_Date(int y, int m, int d, int coi) {
	//how many days left before the customer come
	int date1 = 0, date2 = 0;
	if (y >= Current_Date.year) {
		date1 = Calculate_Date(y, m, d);	//'future' or 'past'
		date2 = Calculate_Date(Current_Date.year, Current_Date.month, Current_Date.day);	//that day
		if (coi == 1)	//just for calculate difference between dates
			return (date2 - date1);
		else if (coi == 0) {
			if ((date1 - date2) > 0) {	/*date1 is after date2*/
				if ((date1 - date2) > 30)
					return 30;	//over a month
				else if ((date1 - date2) > 7)
					return 7;	//over a week
				else
					return 2;	//less than a week
			}
			else return 1;	//wrong input
		}
	}
	else return 0;
}

int Calculate_Date(int year, int month, int day) {
	//caluculate date form 2016.1.1 till "variables passed in"
	//return 'int' variable 'cds', "the days"
	int cds = 0;
	//year
	for (int tyear = 2016; tyear < year; tyear++) {
		if ((tyear % 4 == 0 && tyear % 100 != 0) || tyear % 400 == 0)
			cds += 366;
		else cds += 365;
	}
	//month
	for (int tmonth = 1; tmonth < month; tmonth++) {
		switch (tmonth) {
		case 1: cds += 31; break;
		case 2: if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
					cds += 29; break;
		}
				else cds += 28; break;
		case 3: cds += 31; break;
		case 4: cds += 30; break;
		case 5: cds += 31; break;
		case 6: cds += 30; break;
		case 7: cds += 31; break;
		case 8: cds += 31; break;
		case 9: cds += 30; break;
		case 10: cds += 31; break;
		case 11: cds += 30; break;
		case 12: cds += 31; break;
		}
	}
	//day
	cds += day;
	return cds;
}

int Calculate_Price(int level, int basic, struct room_price *parameters) {
	int price;
	if (basic == 1) price = parameters->price1;
	else if (basic == 2) price = parameters->price2;
	else if (basic == 3) price = parameters->price3;
	else if (basic == 4) price = parameters->price_vip;
	if (level == 2) {
		return (1 * price);
	}
	else if (level == 7) {
		return ((parameters->price_after_week) * price);
	}
	else if (level == 30) {
		return ((parameters->price_after_month) * price);
	}
	else
		return 0;
}

int Apply_For_VIP(void) {
	//do you want a VIP now?
	char confirm;
	printf("\nWanna apply for VIP identity?: y/n");
	do {
		confirm = getch();
		fflush(stdin);
	} while (confirm != 'y' && confirm != 'n');
	if (confirm == 'y') return 1;
	else if (confirm == 'n') return 0;
}

int Random_Allocation(struct room **Room_Board, char class, int *r, int *c, int condition) {
	//as this function gets a certain class which the customer demands for, choose one randomly. 
	File_Room_Info_Read(Room_Board);
	struct meterial {
		int floor;
		int room;
	};
	struct meterial unit[120];
	int n = 0, p;
	//go through the 'Room_Board'
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 20; j++) {
			if (Room_Board[i][j].class == class && Room_Board[i][j].status == 'N') {
				unit[n].floor = i;
				unit[n].room = j;
				n++;
			}
		}
	}
	if (n == 0)
		return 0;
	else {
		srand((unsigned)time(NULL));
		p = rand() % n;
		//change room status:
		*r = unit[p].floor;
		*c = unit[p].room;
		if (condition == 1)
			Room_Board[*r][*c].status = 'R';
		if (condition == 2)
			Room_Board[*r][*c].status = 'U';
		File_Room_Info_Write(Room_Board);
		return 1;
	}
}
//function list (check in/out operator menu):
void Checker_Operator_Menu(struct room **Room_Board, struct room_price *parameters, struct hotel_statistics *income_x_customers, struct Customer_Node **Hasharray, int *n) {
	int option;
	while (1) {
		system("cls");
		Room_Demonstration(Room_Board);
		//the check in/out operator interface:
		gotoxy(0, 3); printf("***Hotel Management Information System***");
		gotoxy(2, 3); printf("<---CHECK IN/OUT OPERATOR MENU--->");
		gotoxy(3, 3); printf("||                              ||");
		gotoxy(4, 3); printf("||---(1) Staff Account Create---||");
		gotoxy(5, 3); printf("||                              ||");
		gotoxy(6, 3); printf("||---(2) Staff Account Login----||");
		gotoxy(7, 3); printf("||                              ||");
		gotoxy(8, 3); printf("||---(3) Staff Account Logout---||");
		gotoxy(9, 3); printf("||                              ||");
		gotoxy(10, 3); printf("||---(0) Back To Main Menu------||");
		gotoxy(11, 3); printf("||                              ||");
		gotoxy(12, 3); printf("<-------------------------------->");
		if (CO_Login_Satus) {
			//the sub-interface:
			gotoxy(2, 38); printf("<----Account information---->");
			gotoxy(3, 38); printf("||------Account Name-------||");
			gotoxy(4, 38); printf("||'   %10s          '||", Current_User.name);
			gotoxy(5, 38); printf("||-(4) Customer Services---||");	//still need a further interface
			gotoxy(6, 38); printf("<--------------------------->");
		}
		gotoxy(11, 39); printf("Selecting your operation: < >\b\b");
		if (scanf_s(" %d", &option) != 1) {
			fflush(stdin);
			gotoxy(12, 39); printf("Warning: wrong input character!");
			Sleep(2000); continue;
		}
		else {
			if (!CO_Login_Satus) {
				if (option < 0 || option > 3) {
					fflush(stdin);
					gotoxy(12, 39); printf("Warning: wrong input character!");
					Sleep(2000); continue;
				}
				else break;
			}
			if (CO_Login_Satus) {
				if (option < 0 || option > 4) {
					fflush(stdin);
					gotoxy(12, 39); printf("Warning: wrong input character!");
					Sleep(2000); continue;
				}
				else break;
			}
		}
	}
	switch (option) {
	case 0:
		//log out first
		if (CO_Login_Satus)
			CO_Login_Satus = !CO_Login_Satus;
		//back to main menu
		Main_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 1:
		File_Staff_Write(3);
		Checker_Operator_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 2:
		if (File_Staff_Read(3, &Current_User) == 1)
			Checker_Operator_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
		Checker_Operator_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 3:
		if (CO_Login_Satus)
			CO_Login_Satus = !CO_Login_Satus;
		Checker_Operator_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 4:
		Customer_Services(Room_Board, parameters, income_x_customers, Hasharray, n);
	default: break;
	}
}

void Customer_Services(struct room **Room_Board, struct room_price *parameters, struct hotel_statistics *income_x_customers, struct Customer_Node **Hasharray, int *n) {
	int option;
	while (1) {
		system("cls");
		//the booking operator interface:
		gotoxy(0, 3); printf("***Hotel Management Information System***");
		gotoxy(2, 3); printf("<-----Customer Services Menu---->");
		gotoxy(3, 3); printf("||                             ||");
		gotoxy(4, 3); printf("||---(1) Customer Arrival------||");
		gotoxy(5, 3); printf("||                             ||");
		gotoxy(6, 3); printf("||---(2) Customer Check-Out----||");
		gotoxy(7, 3); printf("||                             ||");
		gotoxy(8, 3); printf("||---(0) Back To CO Menu-------||");
		gotoxy(9, 3); printf("||                             ||");
		gotoxy(10, 3); printf("<------------------------------->");
		//the sub-interface:
		gotoxy(2, 38); printf("<----Account information---->");
		gotoxy(3, 38); printf("||------Account Name-------||");
		gotoxy(4, 38); printf("||'   %10s          '||", Current_User.name);
		gotoxy(5, 38); printf("<--------------------------->");
		gotoxy(11, 39); printf("Selecting your operation: < >\b\b");
		//make desicion
		if (scanf_s(" %d", &option) != 1) {
			fflush(stdin);
			gotoxy(12, 39); printf("Warning: wrong input character!");
			Sleep(2000); continue;
		}
		if (option < 0 || option > 2) {
			fflush(stdin);
			gotoxy(12, 39); printf("Warning: wrong input character!");
			Sleep(2000); continue;
		}
		else break;
	}
	switch (option) {
	case 0:
		Checker_Operator_Menu(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 1:
		Customer_Check_In(Room_Board, parameters, Hasharray, n);
		Customer_Services(Room_Board, parameters, income_x_customers, Hasharray, n);
	case 2:
		Customer_Check_Out(Room_Board, parameters, income_x_customers, Hasharray, n);
		Customer_Services(Room_Board, parameters, income_x_customers, Hasharray, n);
	default: break;
	}
}

int Customer_Info_Input(struct customer *customer) {
	system("cls");
	//get [customer] name & phonenumber
	strcpy(customer->VIP_number, "000000");
	while (1) {
		printf("Please enter customer's name:\n\t");
		gets(customer->name);
		if (judgechar(customer->name) == 1)
			break;
		else if (judgechar(customer->name) == 2)
			printf("Array input is too long.");
		else if (judgechar(customer->name) == 0)
			printf("Only characters are valid.");
		fflush(stdin);
	}
	fflush(stdin);
	while (1) {
		printf("Please enter customer's phone number:\n\t");
		gets(customer->phonenumber);
		if (judgenum(customer->phonenumber) == 1)
			break;
		else if (judgenum(customer->phonenumber) == 2)
			printf("\tArray input is too long.\n");
		else if (judgenum(customer->phonenumber) == 0)
			printf("\tOnly numbers are valid.\n");
		fflush(stdin);
	}
	fflush(stdin);
	printf("\nCustomer name: %s", customer->name);
	printf("\nCustomer phonenumber: %s", customer->phonenumber);
	char confirm;
	printf("\nAre you sure? y/n");
	do {
		confirm = getch();
		fflush(stdin);
	} while (confirm != 'y' && confirm != 'n');
	if (confirm == 'y')
		return 1;
	else if (confirm == 'n') {
		return 0;
	}
}

void New_Customer(struct customer *customer, struct Customer_Node **Hasharray, int *n) {
	customer->status = 'N';
	if (Apply_For_VIP()) {
		strcpy(customer->VIP_number, Random_Six());
		printf("\n%s %d\n", customer->VIP_number, strlen(customer->VIP_number));
		customer->VIP_status = 'W';
		//write into another file, checked by manager
		FILE *ptr_wait;
		ptr_wait = fopen("VIP wait.txt", "a");
		if (ptr_wait == NULL) {
			printf("There was a problem opening the file, please restart the program.\n\n");
			Sleep(3000); exit(0);
		}
		fwrite(customer, sizeof(struct customer), 1, ptr_wait);
		fclose(ptr_wait);
	}
	else {
		strcpy(customer->VIP_number, "000000");
		customer->VIP_status = 'N';
	}
}

void Customer_Check_In(struct room **Room_Board, struct room_price *parameters, struct Customer_Node **Hasharray, int *n) {
	int choose_room = 0;
	int judge_exist = 0;
	//something will be write in file: "in hotel.txt"
	struct registration in_hotel;
	/*'customer': the structure for recording customer info*/
	struct customer customer;
	//create customer database
	gotoxy(2, 38); printf("<----Account information---->");
	gotoxy(3, 38); printf("||------Account Name-------||");
	gotoxy(4, 38); printf("||'   %10s          '||", Current_User.name);
	gotoxy(5, 38); printf("<--------------------------->");
	FILE *ptr_customer;
	FILE *ptr_in_hotel;
	FILE *ptr_reg;
	fflush(stdin);
	//clean the screen!
	system("cls");
	while (1) {	//while loop: customer info
		int judge_valid = Customer_Info_Input(&customer);
		fflush(stdin);
		if (judge_valid) break;
		else continue;
	}
	//judge on "whether is a registed customer"?
	int judge_correct = 0;
	ptr_reg = fopen("reg.bat", "rb");
	if (ptr_reg == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	else {
		while (fread(&in_hotel, sizeof(struct registration), 1, ptr_reg)) {
			printf("Reading file...\n");
			if (!strcmp(in_hotel.registrant.name, customer.name) && !strcmp(in_hotel.registrant.phonenumber, customer.phonenumber)) {
				printf("Registered customer!");
				//'in_hotel' recorded all information, arrival date is correct
				strcpy(customer.VIP_number, in_hotel.registrant.VIP_number);
				customer.status = in_hotel.registrant.status;
				customer.VIP_status = in_hotel.registrant.VIP_status;
				judge_correct = 1;
				judge_exist = 1;
				choose_room = 1;
				break;
			}
		}
		fclose(ptr_reg);
	}
	if (judge_correct) {
		Room_Board[in_hotel.r][in_hotel.c].status = 'N';
		File_Room_Info_Write(Room_Board);
		//correct date or not
		int correct_date = 0;
		if (in_hotel.regist_day.year == Current_Date.year &&
			in_hotel.regist_day.month == Current_Date.month &&
			in_hotel.regist_day.day == Current_Date.day)
			correct_date = 1;
		//amend in hashtable
		int key;
		struct Customer_Node *head;
		key = Hash_Key_Function(customer.name);
		head = Hasharray[key];
		while ((head->next) != NULL) {
			head = head->next;
			if (!strcmp(customer.name, head->name) && !strcmp(customer.phonenumber, head->phonenumber)) {
				if (correct_date) {
					choose_room = 1;
					customer.status = 'U';
					head->status = 'U';
				}
				else if (!correct_date) {
					choose_room = 0;
					customer.status = 'N';
					head->status = 'N';
				} break;
			}
		}
		fflush(stdin);
		//amend in file
		ptr_customer = fopen("customer database.txt", "r+");
		if (ptr_customer == NULL) {
			printf("There was a problem opening the file, please restart the program.\n\n");
			Sleep(3000); exit(0);
		}
		fseek(ptr_customer, (head->position)*sizeof(struct customer), SEEK_SET);
		fwrite(&customer, sizeof(struct customer), 1, ptr_customer);
		fclose(ptr_customer);
		//delete info in: 'reg.bat'
		FILE *ptr_temp;
		FILE *ptr_reg2;
		ptr_temp = fopen("temp.bat", "wb");
		ptr_reg2 = fopen("reg.bat", "rb");
		if (ptr_reg2 == NULL || ptr_temp == NULL) {
			printf("There was a problem opening the file, please restart the program.\n\n");
			Sleep(3000); exit(0);
		}
		else {
			struct registration temp;
			while (fread(&temp, sizeof(struct registration), 1, ptr_reg2)) {
				if (strcmp(temp.registrant.name, customer.name) != 0 || strcmp(temp.registrant.phonenumber, customer.phonenumber) != 0)
					fwrite(&temp, sizeof(struct registration), 1, ptr_temp);
				fflush(stdin);
			}
		}
		fclose(ptr_temp);
		fclose(ptr_reg2);
		remove("reg.bat");	//delete the origin file
		DeleteFile(TEXT("reg.bat"));	//delete the origin file (confirm, delete again)
		rename("temp.bat", "reg.bat");	//change name into origin file
	}
	//non-registered customer
	else if (!judge_correct) {
		choose_room = 0;
		//call the hashtable:
		int key;
		struct Customer_Node *head;
		key = Hash_Key_Function(customer.name);
		head = Hasharray[key];
		while ((head->next) != NULL) {
			head = head->next;
			if (!strcmp(customer.name, head->name) && !strcmp(customer.phonenumber, head->phonenumber)) {
				if (head->status == 'U') {
					printf("\nYou have checked-in already.");
					Sleep(2000); return;
				}
				judge_exist = 1; break;
			}
		}
		fflush(stdin);
		//in the database.
		if (judge_exist) {
			//VIP number : "000000" or "Random_Six"
			strcpy(customer.VIP_number, head->VIP_number);
			customer.VIP_status = head->VIP_status;
			customer.status = 'N';
			head->status = 'N';
		}
		//not in the database
		else if (!judge_exist)
			New_Customer(&customer, Hasharray, n);
		//in_hotel.registrant. info assign
		strcpy(in_hotel.registrant.name, customer.name);
		strcpy(in_hotel.registrant.phonenumber, customer.phonenumber);
		strcpy(in_hotel.registrant.VIP_number, customer.VIP_number);
		in_hotel.registrant.status = customer.status;
		in_hotel.registrant.VIP_status = customer.VIP_status;
	}
	//choose room
	if (!choose_room) {
		//customer info (VIP status) demonstration:
		gotoxy(6, 38); printf("<----Customer information--->");
		gotoxy(7, 38); printf("||------Customer Name------||");
		gotoxy(8, 38); printf("||'   %10s          '||", customer.name);
		gotoxy(9, 38); printf("||--------VIP Status-------||");
		gotoxy(10, 38);
		if (customer.VIP_status == 'W')
			printf("||'       Auditing        '||");
		else if (customer.VIP_status == 'N')
			printf("||'        Non-VIP        '||");
		else if (customer.VIP_status == 'V')
			printf("||'          VIP          '||");
		gotoxy(11, 38); printf("<--------------------------->");
		//need to order a room
		//room information & price list
		Room_With_Price(Room_Board, parameters);
		//date
		in_hotel.regist_day.year = Current_Date.year;
		in_hotel.regist_day.month = Current_Date.month;
		in_hotel.regist_day.day = Current_Date.day;
		//target class of room
		char VIP = 0, y;
		int r, c, basic;
		int New_Class, number = 0;
		while (1) {
			printf("\nWhich class you have demand for?");
			if (scanf_s(" %d", &New_Class) != 1) {
				y = getchar();
				if (customer.VIP_status == 'V' && (y == 'v' || y == 'V')) {
					VIP = 'V'; number = 0;
				}
				else {
					fflush(stdin);
					printf("Warning: wrong input character!");
					Sleep(1000); continue;
				}
			}
			else if (New_Class < 0 || New_Class > 3) {
				fflush(stdin);
				printf("Warning: wrong input character!");
				Sleep(1000); continue;
			}
			else
				number = 1;
			//'random' or 'target'
			int sure;
			char class;
			if (number && New_Class < 4) {
				basic = New_Class;
				class = New_Class + 48;
				sure = Random_Allocation(Room_Board, class, &r, &c, 2);
			}
			else if (!number && VIP == 'V') {
				basic = 4;
				sure = Random_Allocation(Room_Board, VIP, &r, &c, 2);
			}
			if (sure)
				break;
			else if (!sure){
				printf("\nSorry, hotel has run out of rooms in this class, try another.");
				fflush(stdin); continue;
			}
		}
		fflush(stdin);
		//position
		in_hotel.c = c;
		in_hotel.r = r;
		//price
		in_hotel.price = Calculate_Price(2, basic, parameters);	/*'2' means 'no discount'*/
		//'U' change
		customer.status = 'U';
		if (judge_exist) {
			//amend in hashtable
			int key;
			struct Customer_Node *head;
			key = Hash_Key_Function(customer.name);
			head = Hasharray[key];
			while ((head->next) != NULL) {
				head = head->next;
				if (!strcmp(customer.name, head->name) && !strcmp(customer.phonenumber, head->phonenumber)) {
					head->status = 'U'; break;
				}
			}
			fflush(stdin);
			//amend in file
			ptr_customer = fopen("customer database.txt", "r+");
			if (ptr_customer == NULL) {
				printf("There was a problem opening the file, please restart the program.\n\n");
				Sleep(3000); exit(0);
			}
			fseek(ptr_customer, (head->position)*sizeof(struct customer), SEEK_SET);
			fwrite(&customer, sizeof(struct customer), 1, ptr_customer);
			fclose(ptr_customer);
		}
		else if (!judge_exist) {
			//add in: hashtable
			Hash_Expand(Hasharray, &customer, n);
			//add in: file
			ptr_customer = fopen("customer database.txt", "a");
			if (ptr_customer == NULL) {
				printf("There was a problem opening the file, please restart the program.\n\n");
				Sleep(3000); exit(0);
			}
			fwrite(&customer, sizeof(struct customer), 1, ptr_customer);
			fclose(ptr_customer);
		}
	}
	//amend room board info
	Room_Board[in_hotel.r][in_hotel.c].status = 'U';
	File_Room_Info_Write(Room_Board);
	//time to write 'registration info' into a file!
	ptr_in_hotel = fopen("in hotel.bat", "ab");
	if (ptr_in_hotel == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	//write in, file updating:
	fwrite(&in_hotel, sizeof(struct registration), 1, ptr_in_hotel);
	fclose(ptr_in_hotel);
	Check_U(Room_Board);
	printf("\nCheck-in Complete.");
	printf("\nHave a nice time these days.");
	Sleep(2000);
}

void Customer_Check_Out(struct room **Room_Board, struct room_price *parameters, struct hotel_statistics *income_x_customers, struct Customer_Node **Hasharray, int *n) {
	int judge = 0;
	//something will be write in file: "in hotel.txt"
	struct registration out_hotel;
	//create customer database
	gotoxy(2, 38); printf("<----Account information---->");
	gotoxy(3, 38); printf("||------Account Name-------||");
	gotoxy(4, 38); printf("||'   %10s          '||", Current_User.name);
	gotoxy(5, 38); printf("<--------------------------->");
	/*'customer': the structure for recording customer info*/
	struct customer customer;
	FILE *ptr_customer;
	FILE *ptr_out_hotel;
	fflush(stdin);
	//clean the screen!
	system("cls");
	while (1) {	//while loop: customer info
		int judge_valid = Customer_Info_Input(&customer);
		fflush(stdin);
		if (judge_valid) break;
		else continue;
	}
	ptr_out_hotel = fopen("in hotel.bat", "rb");
	if (ptr_out_hotel == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	else {
		while (fread(&out_hotel, sizeof(struct registration), 1, ptr_out_hotel)) {
			if (!strcmp(out_hotel.registrant.name, customer.name) && !strcmp(out_hotel.registrant.phonenumber, customer.phonenumber)) {
				//'out_hotel' recorded all information, arrival date is correct
				strcpy(customer.VIP_number, out_hotel.registrant.VIP_number);
				customer.status = out_hotel.registrant.status;
				customer.VIP_status = out_hotel.registrant.VIP_status;
				judge = 1; break;
			}
		}
	}
	fclose(ptr_out_hotel);
	if (judge) {
		Room_Board[out_hotel.r][out_hotel.c].status = 'N';
		File_Room_Info_Write(Room_Board);
		//income increase: //history customer increase:
		(income_x_customers->history_customers)++;
		int money_increase = out_hotel.price * (1 + Judge_On_Date(out_hotel.regist_day.year, out_hotel.regist_day.month, out_hotel.regist_day.day, 1));
		printf("\nMoney income: %d", money_increase); Sleep(1000);
		(income_x_customers->total_income) += money_increase;
		File_Statistics_Info_Write(income_x_customers);
		//delete info in: 'registration.txt'
		FILE *ptr_temp, *ptr_hotel;
		ptr_temp = fopen("temp.bat", "wb");
		ptr_hotel = fopen("in hotel.bat", "rb");
		if (ptr_hotel == NULL || ptr_temp == NULL) {
			printf("There was a problem opening the file, please restart the program.\n\n");
			Sleep(3000); exit(0);
		}
		else {
			struct registration temp;
			while (fread(&temp, sizeof(struct registration), 1, ptr_hotel)) {
				if (strcmp(temp.registrant.name, customer.name) != 0 && strcmp(temp.registrant.phonenumber, customer.phonenumber) != 0)
					fwrite(&temp, sizeof(struct registration), 1, ptr_temp);
				fflush(stdin);
			}
		}
		fclose(ptr_temp);
		fclose(ptr_hotel);
		remove("in hotel.bat");	//delete the origin file
		DeleteFile(TEXT("in hotel.bat"));	//delete the origin file (confirm, delete again)
		rename("temp.bat", "in hotel.bat");	//change name into origin file
		//amend in hashtable
		int key;
		struct Customer_Node *head;
		key = Hash_Key_Function(customer.name);
		head = Hasharray[key];
		while ((head->next) != NULL) {
			head = head->next;
			if (!strcmp(customer.name, head->name) && !strcmp(customer.phonenumber, head->phonenumber)) {
				customer.VIP_status = head->VIP_status;
				customer.status = 'N';
				head->status = 'N'; break;
			}
		}
		fflush(stdin);
		//amend in file
		ptr_customer = fopen("customer database.txt", "r+");
		if (ptr_customer == NULL) {
			printf("There was a problem opening the file, please restart the program.\n\n");
			Sleep(3000); exit(0);
		}
		fseek(ptr_customer, (head->position)*sizeof(struct customer), SEEK_SET);
		fwrite(&customer, sizeof(struct customer), 1, ptr_customer);
		fclose(ptr_customer);
		printf("\nCheck-out Complete.");
		Sleep(2000);
	}
	else if (!judge) {
		printf("\nYou are not customer in the hotel.");
		Sleep(2000); return;
	}
}

//sub-function list (functional):
void Print_All(void) {
	//print out all staff
	int n = 1;
	struct staff_use staff_print;
	FILE *ptr_staff;
	fflush(stdin);
	ptr_staff = fopen("staff.txt", "r");	//open file (read only)
	if (ptr_staff == NULL) {
		printf("There was a problem opening the file, please restart the program\n\n");
		Sleep(3000); exit(0);
	}
	//the print process
	else {
		gotoxy(14, 0); printf("Opening file success!\n");
		while (fread(&staff_print, sizeof(struct staff_use), 1, ptr_staff)) {
			printf("No.%d   ", n);
			if (staff_print.identity == 1)
				printf("Manager");
			else if (staff_print.identity == 2)
				printf("Booking operator ");
			else if (staff_print.identity == 3)
				printf("Check-in/out operator ");
			printf("%10s%10s\n", staff_print.name, staff_print.password);
			n++;
		}
		gotoxy(14 + n, 0); printf("Reading file success!\n");
		Sleep(5000);
	}
	fclose(ptr_staff);
	fflush(stdin);
}

void Print_All_hash(struct Customer_Node **Hasharray, int *n) {
	system("cls");
	printf("Hashsize: %d.\n", *n);
	struct Customer_Node *head;
	//print out customers in each busket
	for (int i = 0; i < 60; i++) {
		head = Hasharray[i];
		printf("%02d. bucket No.%02d\n", i, i + 1);
		while ((head->next) != NULL) {
			head = head->next;
			printf("%10s.%20s.%6s", (*head).name, (*head).phonenumber, (*head).VIP_number);
			printf(" . %c . %c\n", (*head).status, (*head).VIP_status);
		}
	}
	printf("Reading hashtable success!\n");
	Sleep(5000);	//show the content, wait for 5 seconds
}

void Print_All_Customer(void) {
	//print out all staff
	int n = 1;
	struct customer customer_print;
	FILE *ptr_customer;
	fflush(stdin);
	ptr_customer = fopen("customer database.txt", "r");	//open file (read only)
	if (ptr_customer == NULL) {
		printf("There was a problem opening the file, please restart the program\n\n");
		Sleep(3000); exit(0);
	}
	//the print process
	else {
		gotoxy(14, 0); printf("Opening file success!\n");
		while (fread(&customer_print, sizeof(struct customer), 1, ptr_customer)) {
			printf("No.%d   ", n);
			printf("%10s.%20s.%6s", customer_print.name, customer_print.phonenumber, customer_print.VIP_number);
			printf(" . %c . %c\n", customer_print.status, customer_print.VIP_status);
			n++;
		}
		gotoxy(14 + n, 0); printf("Reading file success!\n");
		Sleep(5000);
	}
	fclose(ptr_customer);
	fflush(stdin);
}

void Reduce_All(void) {	//empty everything in the file!
	//include: staff list, staff login record...
	FILE *ptr_staff;
	fflush(stdin);
	//clean the file
	ptr_staff = fopen("staff.txt", "w");
	if (ptr_staff == NULL) {
		printf("There was a problem opening the file, please restart the program\n\n");
		Sleep(3000); exit(0);
	}
	fclose(ptr_staff);
	gotoxy(14, 0); printf("'staff.txt'has been cleaned already!\n");
	//clean the file
	ptr_staff = fopen("staff login record.txt", "w");
	if (ptr_staff == NULL) {
		printf("There was a problem opening the file, please restart the program\n\n");
		Sleep(3000); exit(0);
	}
	fclose(ptr_staff);
	gotoxy(15, 0); printf("'staff login record.txt'has been cleaned already!\n");
	//wait for 2 second, showing content on the screen
	Sleep(2000);
	fflush(stdin);
}

void Note_Print(void) {
	//print out all staff
	int n = 1;
	struct staff_use staff_info;
	struct time login_time;
	FILE *ptr_login_note;
	fflush(stdin);
	ptr_login_note = fopen("staff login record.txt", "r");
	if (ptr_login_note == NULL) {
		printf("There was a problem opening the file, please restart the program\n\n");
		Sleep(3000); exit(0);
	}
	//the print process
	else {
		gotoxy(14, 0); printf("Opening file success!\n");
		while (fread(&staff_info, sizeof(struct staff_use), 1, ptr_login_note)) {
			if (staff_info.identity == 1)
				printf("Manager");
			else if (staff_info.identity == 2)
				printf("Booking operator ");
			else if (staff_info.identity == 3)
				printf("Check-in/out operator ");
			printf("%10s ", staff_info.name);
			fread(&login_time, sizeof(struct time), 1, ptr_login_note);
			printf("%d2/%2d/%4d %02d:%02d:%02d\n", login_time.mon, login_time.day, login_time.year, login_time.hour, login_time.min, login_time.sec);
			n++;
		}
		fclose(ptr_login_note);
		gotoxy(14 + n, 0); printf("Reading file success!\n");
	}
	Sleep(5000);
	fflush(stdin);
}

void Check_R(struct room **Room_Board) {
	system("cls");
	struct registration regist;
	FILE *ptr_regist;
	ptr_regist = fopen("reg.bat", "rb");
	if (ptr_regist == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	else {
		while (fread(&regist, sizeof(struct registration), 1, ptr_regist)) {
			printf("----\n|");
			setcolor(0, 2); printf(" %c", Room_Board[regist.r][regist.c]);
			setcolor(7, 0);
			printf("|   (%d, %d)", (5 - regist.r), (regist.c + 1));
			printf("\n----\n");
			printf("%10s.%20s.%6s ", regist.registrant.name, regist.registrant.phonenumber, regist.registrant.VIP_number);
			printf("%c . %c   ", regist.registrant.status, regist.registrant.VIP_status);
			printf("%d . %d . %d   ", regist.regist_day.year, regist.regist_day.month, regist.regist_day.day);
			printf("%d", regist.price);
			//
			printf("\n");
			//
		}
		printf("Reading file success.");
	}
	fclose(ptr_regist);
	fflush(stdin);
	Sleep(3000);
}

void Check_U(struct room **Room_Board) {
	system("cls");
	struct registration hotel;
	FILE *ptr_hotel;
	ptr_hotel = fopen("in hotel.bat", "rb");
	if (ptr_hotel == NULL) {
		printf("There was a problem opening the file, please restart the program.\n\n");
		Sleep(3000); exit(0);
	}
	else {
		while (fread(&hotel, sizeof(struct registration), 1, ptr_hotel)) {
			printf("----\n|");
			setcolor(0, 4); printf(" %c", Room_Board[hotel.r][hotel.c]);
			setcolor(7, 0);
			printf("|   (%d, %d)", 5 - hotel.r, hotel.c + 1);
			printf("\n----\n");
			printf("%10s.%20s.%6s ", hotel.registrant.name, hotel.registrant.phonenumber, hotel.registrant.VIP_number);
			printf("%c . %c   ", hotel.registrant.status, hotel.registrant.VIP_status);
			printf("%d . %d . %d   ", hotel.regist_day.year, hotel.regist_day.month, hotel.regist_day.day);
			printf("%d", hotel.price);
			//
			printf("\n");
			//
		}
		printf("Reading file success.");
	}
	fclose(ptr_hotel);
	fflush(stdin);
	Sleep(3000);
}

//judge function list:
int judgenum(char *a) {
	int length = strlen(a);
	if (length >= 20)
		return 2;
	int j = 0, i = 0;
	for (i = 0; i < length; i++) {
		if (a[i] <= 57 && a[i] >= 48)
			j++;
	}
	if (j == length) return 1;
	else return 0;
}

int judgechar(char *a) {
	int length = strlen(a);
	if (length >= 10)
		return 2;
	int j = 0, i = 0;
	for (i = 0; i<length; i++) {
		if ((a[i] <= 90 && a[i] >= 65) || (a[i] <= 122 && a[i] >= 97))
			j++;
	}
	if (j == length) return 1;
	else return 0;
}

char *Random_Six(void) {
	srand((unsigned)time(NULL));
	char vip_num[7];
	for (int i = 0; i < 6; i++) {
		if (i < 2)
			vip_num[i] = rand() % 26 + 97;
		else
			vip_num[i] = rand() % 10 + 48;
	}
	vip_num[6] = '\0';
	return vip_num;
}
//the code is over here, Ln 2524.