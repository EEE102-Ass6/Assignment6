#include "CSendMail.h"
#include "iostream"
using namespace std;


int main()
{
	CSendMail sMailer;
	//    freopen("F://mailfile//out.txt","w+",stdout);

	sMailer.setServerName("smtp.sina.com");                                                        //����smtp,��"smtp.126.com"
	sMailer.setUserName("zhaozhihe2333@sina.com");                                                                //�����˺�������"****@126.com"
	sMailer.setUserPwd("Daohaolaji@");                                                                //��������
	sMailer.setSenderName("zzh");                                                                //����������
	sMailer.setSenderAddress("zhaozhihe2333@sina.com");                                                //���������ַ�������˺ŵĵ�ַ,����������˺���"****@126.com"
	
	sMailer.setReceiver("zzh","zhaozhihe2333@sina.com");                                            //����ʼ�������
	//sMailer.addReceiver("zzh", "397142305@qq.com");

	sMailer.AddFilePath("D:\\canimma.txt");             //��Ӹ���
															 //    sMailer.AddFilePath("F:/mailfile/libcurl.exp");                                                //��Ӹ���

															 //���͵�һ���ʼ�
	if (sMailer.Connent())                                                                        //ÿ�η��ʼ�ǰ����Ҫconnect
	{
		if (sMailer.SendMail("CMailSender:����������", "������ٷ����¸�������һҹ�����𣿷��� http://www.sb.com"))            //��һ���ַ������ʼ����⣬�ڶ������ʼ�����
			cout << "�ʼ�������ɣ�";

	}
	Sleep(10000);
	//���͵ڶ����ʼ�
	if (sMailer.Connent())                                                                        //ÿ�η��ʼ�ǰ����Ҫconnect
	{
		std::string title, content;
		title = "�����ʼ�part_2";
		content = "�����Ǹ���˸£�";
		if (sMailer.SendMail(title, content))                                                        //��һ���ַ������ʼ����⣬�ڶ������ʼ�����
			cout << "�ʼ�������ɣ�";

	}


	return 0;
}