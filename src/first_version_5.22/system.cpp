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

	sMailer.setServerName("smtp.sina.com");                                                        //����smtp,��"smtp.126.com"
	sMailer.setUserName("zhaozhihe2333@sina.com");                                                                //�����˺�������"****@126.com"
	sMailer.setUserPwd("Daohaolaji@");                                                                //��������
	sMailer.setSenderName("zzh");                                                                //����������
	sMailer.setSenderAddress("zhaozhihe2333@sina.com");                                                //���������ַ�������˺ŵĵ�ַ,����������˺���"****@126.com"

	sMailer.setReceiver("zzh", "zhaozhihe2333@sina.com");                                            //����ʼ�������

	sMailer.AddFilePath("D:\\canimma.txt");             //��Ӹ���

	

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
			
			if (sMailer.Connent())                                                                        //ÿ�η��ʼ�ǰ����Ҫconnect
			{
				std::string title, content;
				title = "MMP";
				content = "Test success��";
				if (sMailer.SendMail(title, content))                                                        //��һ���ַ������ʼ����⣬�ڶ������ʼ�����
					cout << "Sent success��\n";
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
			//����ת��
			char* szStr = "AS6.exe";
			WCHAR wszClassName[256];
			memset(wszClassName, 0, sizeof(wszClassName));
			MultiByteToWideChar(CP_ACP, 0, szStr, strlen(szStr) + 1, wszClassName,
				sizeof(wszClassName) / sizeof(wszClassName[0]));

			STARTUPINFO si = { sizeof(si) };
			PROCESS_INFORMATION pi;
			si.dwFlags = STARTF_USESHOWWINDOW; // ָ��wShowWindow��Ա��Ч  
			si.wShowWindow = TRUE; // �˳�Ա��ΪTRUE�Ļ�����ʾ�½����̵�������  
			BOOL bRet = CreateProcess(
				NULL,   // ���ڴ�ָ����ִ���ļ����ļ���  
				wszClassName,// �����в���  
				NULL,   // Ĭ�Ͻ��̰�ȫ��  
				NULL,   // Ĭ�Ͻ��̰�ȫ��  
				FALSE,  // ָ����ǰ�����ھ�������Ա��ӽ��̼̳�  
				CREATE_NEW_CONSOLE | REALTIME_PRIORITY_CLASS, // Ϊ�½��̴���һ���µĿ���̨����  
				NULL,   // ʹ�ñ����̵Ļ�������  
				NULL,   // ʹ�ñ����̵���������Ŀ¼  
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
