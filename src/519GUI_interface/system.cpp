#include "system.h"
#include "var_Whole.h"
using namespace std;
HWND hwnd = GetForegroundWindow();//The handle of the operation which mediates the size
bool f = 1;
//ShowWindow(hwnd, SW_MAXIMIZE);
DWORD WINAPI ThreadFun(LPVOID pM)
{
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
