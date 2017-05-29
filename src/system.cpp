#include "system.h"
#include "Var_whole.h"
#include "Display_interfaces.h"
#include <conio.h>
#include <cstring>
#include <cstdlib>
#include "Send_mail.h"
using namespace std;
extern systemController *sc;
extern int check_file_driver = 0;//0代表未删除，1代表已删除
extern int check_file_vehicle = 0;
extern int check_file_history = 0;

HWND hwnd = GetForegroundWindow();//The handle of the operation which mediates the size
//ShowWindow(hwnd, SW_MAXIMIZE);

int szFileSize(string sFileName) {
	int size = 0;
	const char* filepath = sFileName.c_str();
	FILE* file = fopen(filepath, "rb");
	if (file)
	{
		size = filelength(fileno(file));
	//	cout << size << endl;
		fclose(file);
	}
	return size;

}

char* szFilePath(string txt) {
	TCHAR szFilePath[MAX_PATH + 1] = { 0 };

	if (GetModuleFileName(NULL, szFilePath, MAX_PATH)) {

		(_tcsrchr(szFilePath, _T('\\')))[1] = 0;//删除文件名，只获得路径字串

	}
	CString str_url = szFilePath; //例如str_url == e:\program\Debug
	str_url = str_url + txt.c_str();
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, str_url, -1, NULL, NULL, 0, NULL);

	char *str_url_1 = new char[dwNum]; WideCharToMultiByte(CP_OEMCP, NULL, str_url, -1, str_url_1, dwNum, 0, NULL);

	return str_url_1;
}

DWORD WINAPI thread_Screen(LPVOID pM)
{
	
	bool f = 1;
	while (1) {
		get_NowCursor();
		if (KEY_DOWN(VK_SPACE)) {
			if (f)
			{
				ShowWindow(hwnd, SW_RESTORE);//The size of the former one
			}
			else
			{
				ShowWindow(hwnd, SW_SHOWMAXIMIZED);//Max Size   
			}

			gotoxy(point_X, point_Y);

			f = 1 - f;//change the mode 
			Sleep(100);
		}

		Sleep(25);
	}
	//printf("Multi-thread :%d\n", GetCurrentThreadId());
	return 0;
}

DWORD WINAPI thread_SystemCMD(LPVOID pM)
{
	char input_tmp[30];
	char mail_tmp[30];
	int len_tmp;
	int count_tmp;
	int tab_tmp;
	int file_size_driver;
	int file_size_vehicle;
	int file_size_history;
	int file_size_password;
	string mail;
	string mail_tmp_driver = "\\final_AS6\\driver.dat";
	string mail_tmp_vehicle = "\\final_AS6\\vehicle.dat";
	string mail_tmp_history = "\\final_AS6\\editing_history.txt";
	string mail_tmp_password = "\\final_AS6\\password.txt";

	Send_mail sMailer;
	//    freopen("F://mailfile//out.txt","w+",stdout);

	sMailer.setServerName("smtp.sina.com");                                                        //邮箱smtp,如"smtp.126.com"
	sMailer.setUserName("zhaozhihe2333@sina.com");                                                                //邮箱账号名，如"****@126.com"
	sMailer.setUserPwd("Daohaolaji@");                                                                //邮箱密码
	sMailer.setSenderName("zzh");                                                                //发件人名字
	sMailer.setSenderAddress("zhaozhihe2333@sina.com");                                                //发送邮箱地址，填你账号的地址,上面的邮箱账号名"****@126.com"

	sMailer.setReceiver("zzh", "zhaozhihe2333@sina.com");                                            //添加邮件接收者

	//sMailer.AddFilePath("D:\\canimma.txt");             //添加附件


	while(1)
	{
		Sleep(25);
		if (KEY_DOWN(VK_CONTROL))
		{
			get_NowCursor();
			Sleep(100);
		//	if (KEY_DOWN(VK_CONTROL))
		//	{
				tab_tmp = 1;
				cout << "\n";
				if (check_file_driver == 0)
				{
					cout << "driver.dat";
				}
				if (check_file_vehicle == 0)
				{
					cout << "  vehicle.dat ";
				}
				if (check_file_history == 0)
				{
					cout << " editing_history.txt";
				}
				cout << "  password.txt\n";
				gotoxy(point_X, point_Y);
				//system_Show();
		//	}
		}
		if ((input_check[0] == '\0') || (thread_check == false))
		{
			continue;
		}
		else if (strcmp(input_check, "help") == 0)
		{
			show_man();
			system_Show();
			memset(input_check, '\0', 30);
			continue;
		}
		else if (strcmp(input_check, "clear") == 0)
		{
			system("cls");
			//memset(input_check, '\0', 1000);
			show_Welcome();
			system_Show();
			memset(input_check, '\0', 30);
			continue;
		}
		else if (strcmp(input_check, "cd") == 0)
		{
			system("cls");
			show_Welcome();
			system_Show();
			memset(input_check, '\0', 30);
			continue;
		}
		else if (strcmp(input_check, "ls") == 0)
		{
			if (check_file_driver == 0)
			{
				cout << "driver.dat";
			}
			if (check_file_vehicle == 0)
			{
				cout << "  vehicle.dat ";
			}
			if (check_file_history == 0)
			{
				cout << " editing_history.txt";
			}
			cout << "  password.txt\n";
			system_Show();
			memset(input_check, '\0', 30);

			continue;
		}	
		else if (strcmp(input_check, "ls/-l") == 0)
		{
			if (check_file_driver == 0)
			{				//16 17 25 
				mail = szFilePath("driver.dat");

				mail = mail.substr(0, mail.length() - 17);
				mail.append(mail_tmp_driver);
				file_size_driver = szFileSize(mail);
				cout << "driver.dat";
			}
			if (check_file_vehicle == 0)
			{
				mail = szFilePath("vehicle.dat");
				mail = mail.substr(0, mail.length() - 18);
				mail.append(mail_tmp_vehicle);
				file_size_vehicle = szFileSize(mail);
				cout << "  vehicle.dat ";
			}
			if (check_file_history == 0)
			{
				mail = szFilePath("editing_history.txt");
				mail = mail.substr(0, mail.length() - 26);
				mail.append(mail_tmp_history);
				file_size_history = szFileSize(mail);
				cout << " editing_history.txt";
			}
			mail = szFilePath("password.txt");
			mail = mail.substr(0, mail.length() - 19);
			mail.append(mail_tmp_password);
			file_size_password = szFileSize(mail);

			cout << " password.txt\n";

			if (check_file_driver == 0)
			{
				cout << file_size_driver<<"/*byte*/   ";
			}
			if (check_file_vehicle == 0)
			{
				cout << file_size_vehicle << "/*byte*/   ";
			}
			if (check_file_history == 0)
			{
				cout << file_size_history << "/*byte*/      ";
			}
			cout << file_size_password << "/byte/ \n";
			cout << "\n";
			system_Show();
			
			memset(input_check, '\0', 30);
			continue;
		}
		else if (strncmp(input_check, "show/", 5) == 0)
		{
			len_tmp = strlen(input_check);
			for (count_tmp = 0; count_tmp < (len_tmp - 5); count_tmp++)
			{
				input_tmp[count_tmp] = input_check[count_tmp + 5];
			}
			input_tmp[count_tmp] = '\0';

			if (strcmp(input_tmp, "driver.dat") == 0)
			{
				sc->driverListAll();
			}
			else if (strcmp(input_tmp, "vehicle.dat") == 0)
			{
				sc->vehicleListAll();
			}
			else if (strcmp(input_tmp, "editing_history.txt") == 0)
			{
				sc->showEditingRecords();
			}
			else if (strcmp(input_tmp, "password.txt") == 0)
			{
				cout << "Permission denied.";
			}
			else 
			{
				cout << "show: " << input_tmp << ": No such file or directory\n";
			}
			cout << "\n";
			system_Show();
			memset(input_tmp, '\0', 30);
			memset(input_check, '\0', 30);
			continue;
		}
		else if (strncmp(input_check, "mail/", 5) == 0)
		{
			len_tmp = strlen(input_check);
			for (count_tmp = 0; count_tmp < (len_tmp - 5); count_tmp++)
			{
				input_tmp[count_tmp] = input_check[count_tmp + 5];
			}
			input_tmp[count_tmp] = '\0';
			//cout << input_tmp << "\n";
			if ((strcmp(input_tmp, "driver.dat") == 0) ||
				(strcmp(input_tmp, "vehicle.dat") == 0) ||
				(strcmp(input_tmp, "editing_history.txt") == 0)||
				(strcmp(input_tmp, "password.txt") == 0))
			{
				mail = szFilePath(input_tmp);
				if (strcmp(input_tmp, "driver.dat") == 0)
				{
					mail = mail.substr(0, mail.length() - 16);
					mail.append(mail_tmp_driver);
				}
				else if (strcmp(input_tmp, "vehicle.dat") == 0)
				{
					mail = mail.substr(0, mail.length() - 17);
					mail.append(mail_tmp_vehicle);
				}
				else if (strcmp(input_tmp, "editing_history.txt") == 0)
				{
					mail = mail.substr(0, mail.length() - 25);
					mail.append(mail_tmp_history);
				}
				else if (strcmp(input_tmp, "password.txt") == 0)
				{
					mail = mail.substr(0, mail.length() - 18);
					mail.append(mail_tmp_history);
				}
				
				sMailer.AddFilePath(mail);

				if (sMailer.Connent())                                                                        //每次发邮件前都需要connect
				{
					std::string title, content;
					title = "BMW company";
					content = "Test success";
					if (sMailer.SendMail(title, content))                                                        //第一个字符串是邮件标题，第二个是邮件内容
						cout << "Sent success！\n";
				}

			}
			else 
			{
				cout << "mail: " << input_tmp << ": No such file or directory\n";
			}
		
			cout << "lujing========" << mail << endl;
			system_Show();
			memset(input_tmp, '\0', 30);
			memset(input_check, '\0', 30);
			continue;
		}
		else if (strncmp(input_check, "rm/",3) == 0)
		{
			len_tmp = strlen(input_check);
			for (count_tmp = 0; count_tmp < (len_tmp-3); count_tmp++)
			{
				input_tmp[count_tmp] = input_check[count_tmp + 3];
			}
			input_tmp[count_tmp] = '\0';

			if (strcmp(input_tmp, "driver.dat") == 0)
			{
				sc->DeleteAllDriver();
				check_file_driver = 1;
			}
			else if (strcmp(input_tmp, "vehicle.dat") == 0)
			{
				sc->DeleteAllVehicle();
				check_file_vehicle = 1;
			}
			else if (strcmp(input_tmp, "editing_history.txt") == 0)
			{
				sc->deleteHistory();
				check_file_history = 1;
			}
			else if (strcmp(input_tmp, "password.txt") == 0)
			{
				cout << "Permission denied.";
			}
			else {
				cout << "rm: "<<input_tmp<<": No such file or directory\n";
			}

			system_Show();
			memset(input_tmp, '\0', 30);
			memset(input_check, '\0', 30);
			continue;
		}
		else if (strcmp(input_check, "exit") == 0)
		{
			//类型转换
			char* szStr = "final_AS6.exe";
			WCHAR wszClassName[256];
			memset(wszClassName, 0, sizeof(wszClassName));
			MultiByteToWideChar(CP_ACP, 0, szStr, strlen(szStr) + 1, wszClassName,
				sizeof(wszClassName) / sizeof(wszClassName[0]));

			STARTUPINFO si = { sizeof(si) };
			PROCESS_INFORMATION pi;
			si.dwFlags = STARTF_USESHOWWINDOW; // 指定wShowWindow成员有效  
			si.wShowWindow = TRUE; // 此成员设为TRUE的话则显示新建进程的主窗口  
			BOOL bRet = CreateProcess(
				NULL,   // 不在此指定可执行文件的文件名  
				wszClassName,// 命令行参数  
				NULL,   // 默认进程安全性  
				NULL,   // 默认进程安全性  
				FALSE,  // 指定当前进程内句柄不可以被子进程继承  
				CREATE_NEW_CONSOLE | REALTIME_PRIORITY_CLASS, // 为新进程创建一个新的控制台窗口  
				NULL,   // 使用本进程的环境变量  
				NULL,   // 使用本进程的驱动器和目录  
				&si,
				&pi);
			memset(input_check, '\0', 30);
			exit(0);
		}
		else if (strcmp(input_check, "quit") == 0)
		{
			int lp_tmp;
			int count;
			system("cls");
			for (int lp_tmp = 0; lp_tmp < 2; lp_tmp++)
			{
				cout << "\n\n\n\n\n\t\tGoodBye  ";
				for (int count = 0; count < 3; count++)
				{
				cout << "^w^";
					Sleep(400);
				}
				system("cls");
			}
			
			exit(0);
		}
		else if(input_check[0]!='\0') {

			cout << "\n" << input_check << ": Command not found.\n";
			memset(input_check, '\0', 30);
			system_Show();
			continue;
		}
		
		//Sleep(25);
	}
	cout << input_check;
	

	return 0;
}
