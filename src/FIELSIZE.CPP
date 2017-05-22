#include <iostream>
#include  <fstream>
#include <windows.h>
#include <atlstr.h>
#include <stdio.h>
#include <sys\stat.h>
#include <io.h>
using namespace std;

char*szFilePath(string txt){
  TCHAR szFilePath[MAX_PATH + 1] = { 0 };

  if (GetModuleFileName(NULL, szFilePath, MAX_PATH)){

    (_tcsrchr(szFilePath, _T('\\')))[1] = 0;//删除文件名，只获得路径字串

  }
  CString str_url = szFilePath; //例如str_url == e:\program\Debug
  str_url = str_url + txt.c_str();
  DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, str_url, -1, NULL, NULL, 0, NULL);

  char *str_url_1 = new char[dwNum]; WideCharToMultiByte(CP_OEMCP, NULL, str_url, -1, str_url_1, dwNum, 0, NULL);
  
  return str_url_1;
}

long szFileSize(string sFileName){
  TCHAR szFilePath[MAX_PATH + 1] = { 0 };

  if (GetModuleFileName(NULL, szFilePath, MAX_PATH)){

    (_tcsrchr(szFilePath, _T('\\')))[1] = 0;//删除文件名，只获得路径字串

  }
  CString str_url = szFilePath; //例如str_url == e:\program\Debug
  str_url = str_url + sFileName.c_str();
  sFileName = (CStringA)str_url;//string s(CString.GetBuffer());
  //string sFileName = "D:/aa.txt";
  ifstream in(sFileName.c_str());
  in.seekg(0, ios::end);
  long size = in.tellg();
  in.close();

  return size;
}
int main(){
  string txt_name = "1.txt";
  char* a = szFilePath(txt_name);
  cout << a<< endl;
  long b = szFileSize(txt_name);
  cout << "The size of file is：" << b << " byte" << endl;
return 0;
}
