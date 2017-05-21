#include "system.h"
#include "Var_whole.h"
#include "Display_interfaces.h"
#include <conio.h>
#include <cstring>
#include <cstdlib>
#include "Send_mail.h"
using namespace std;

HWND hwnd = GetForegroundWindow();//The handle of the operation which mediates the size
//ShowWindow(hwnd, SW_MAXIMIZE);
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
				ShowWindow(hwnd, SW_MAXIMIZE);//Max Size   
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
//	char ch_cmd = '\0';
	//char command[1000];
	//int tmp_cmd = 0;
	//input_check[0] = 'c';
	char rm_tmp[30];
	int len_tmp;
	int count_tmp;
	Send_mail sMailer;
	//    freopen("F://mailfile//out.txt","w+",stdout);

	sMailer.setServerName("smtp.sina.com");                                                        //邮箱smtp,如"smtp.126.com"
	sMailer.setUserName("zhaozhihe2333@sina.com");                                                                //邮箱账号名，如"****@126.com"
	sMailer.setUserPwd("Daohaolaji@");                                                                //邮箱密码
	sMailer.setSenderName("zzh");                                                                //发件人名字
	sMailer.setSenderAddress("zhaozhihe2333@sina.com");                                                //发送邮箱地址，填你账号的地址,上面的邮箱账号名"****@126.com"

	sMailer.setReceiver("zzh", "zhaozhihe2333@sina.com");                                            //添加邮件接收者

	sMailer.AddFilePath("D:\\canimma.txt");             //添加附件

	

	while(1)
	{
		Sleep(25);
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
			memset(input_check, '\0', 1000);
			show_Welcome();
			system_Show();
			memset(input_check, '\0', 30);
			continue;
		}
		else if (strcmp(input_check, "ls") == 0)
		{
			memset(input_check, '\0', 30);
			continue;
		}		
		else if (strcmp(input_check, "ls -l") == 0)
		{
			memset(input_check, '\0', 30);
			continue;
		}
		else if (strncmp(input_check, "mail/", 5) == 0)
		{
			len_tmp = strlen(input_check);
			for (count_tmp = 0; count_tmp < (len_tmp - 5); count_tmp++)
			{
				rm_tmp[count_tmp] = input_check[count_tmp + 5];
			}
			rm_tmp[count_tmp] = '\0';
			cout << rm_tmp << "\n";
			
			if (sMailer.Connent())                                                                        //每次发邮件前都需要connect
			{
				std::string title, content;
				title = "MMP";
				content = "Test success。";
				if (sMailer.SendMail(title, content))                                                        //第一个字符串是邮件标题，第二个是邮件内容
					cout << "Sent success！\n";
			}

			system_Show();
			memset(rm_tmp, '\0', 30);
			memset(input_check, '\0', 30);
			continue;
		}
		else if (strncmp(input_check, "rm/",3) == 0)
		{
			len_tmp = strlen(input_check);
			for (count_tmp = 0; count_tmp < (len_tmp-3); count_tmp++)
			{
				rm_tmp[count_tmp] = input_check[count_tmp + 3];
			}
			rm_tmp[count_tmp] = '\0';
			cout << rm_tmp<<"\n";


			system_Show();
			memset(rm_tmp, '\0', 30);
			memset(input_check, '\0', 30);
			continue;
		}
		else if (strcmp(input_check, "exit") == 0)
		{
			//类型转换
			char* szStr = "AS6.exe";
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
		else if(input_check[0]!='\0') {
			cout << "\n" << input_check << ": Command not found.\n";
			memset(input_check, '\0', 30);
			system_Show();
			continue;
		}
		
		//Sleep(25);
	}
	cout << input_check;
//	while (1)
//	{
	//	show_Search();
//		Sleep(1222);
///	}

	return 0;
}
