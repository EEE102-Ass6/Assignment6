//source file (function setails in linkage.h):

//header filed:
#include "(Linkage)_header.h"

int sizeof_driver_file = 0;
int sizeof_vehicle_file = 0;

char* Random_Number(void) {
	//generate the license, randomly.
	static char dri_num[11]; //11
	for (int i = 0; i < 10; i++) {	//10
		if (i < 2)
			dri_num[i] = rand() % 26 + 97;
		else
			dri_num[i] = rand() % 10 + 48;
	}
	dri_num[10] = '\0';	//10
	return dri_num;
}

char* Random_License(void) {
	//generate the license, randomly.
	static char License[7];
	for (int i = 0; i < 6; i++) {
		if (i < 2)
			License[i] = rand() % 26 + 97;
		else
			License[i] = rand() % 10 + 48;
	}
	License[6] = '\0';
	return License;
}