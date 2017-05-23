#include <cstdio>  
#include<cstdlib>
#include <ctime>  
#include<iostream>
#include <Windows.h>
#include <string.h>
using namespace std;
//The interface of getting the current time
char* time_ret() {
	char year[5];
	char month[3];
	char day[3];
	char hour[3];
	char min[3];
	char second[3];
	char whole_time[100];
	char*   s = (char*)calloc(100, sizeof(char*));
	time_t timep;
	struct tm *p;
	time(&timep);
	p = localtime(&timep);

	memset(year, '\0', 5);
	memset(month, '\0', 3);
	memset(day, '\0', 3);
	memset(hour, '\0', 3);
	memset(min, '\0', 3);
	memset(second, '\0', 3);
	memset(whole_time, '\0', 100);

	itoa(1900 + p->tm_year, year, 10);
	itoa(1 + p->tm_mon, month, 10);
	itoa(p->tm_mday, day, 10);
	itoa(p->tm_hour, hour, 10);
	itoa(p->tm_min, min, 10);
	itoa(p->tm_sec, second, 10);

	switch (p->tm_wday)
	{
	case 1:
		sprintf(whole_time, "%s/%s/%s %s:%s:%s %s", year, month, day, hour, min, second, "Monday");		
	case 2:
		sprintf(whole_time, "%s/%s/%s %s:%s:%s %s", year, month, day, hour, min, second, "Tuesday");
	case 3:
		sprintf(whole_time, "%s/%s/%s %s:%s:%s %s", year, month, day, hour, min, second, "Wednesday");
	case 4:
		sprintf(whole_time, "%s/%s/%s %s:%s:%s %s", year, month, day, hour, min, second, "Thursday");
	case 5:
		sprintf(whole_time, "%s/%s/%s %s:%s:%s %s", year, month, day, hour, min, second, "Friday");
	case 6:
		sprintf(whole_time, "%s/%s/%s %s:%s:%s %s", year, month, day, hour, min, second, "Saturday");
	case 7:
		sprintf(whole_time, "%s/%s/%s %s:%s:%s %s", year, month, day, hour, min, second, "Sunday");
		break;
	}
	strcpy(s, whole_time);
		//cout << s;
	return s;

}
int main()
{
	//The sample. Remember to do this as the pointer format
	char* tmp;	
	tmp =  time_ret();
	printf("%s", tmp);
	system("pause");

	return 0;
}