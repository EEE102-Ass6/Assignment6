//source file (function setails in linkage.h):

//header filed:
#include "(Linkage)_header.h"

int sizeof_driver_file = 0;
int sizeof_vehicle_file = 0;

char* Random_License(void) {
	//generate the license, randomly.
	static char vip_num[7];
	for (int i = 0; i < 6; i++) {
		if (i < 2)
			vip_num[i] = rand() % 26 + 97;
		else
			vip_num[i] = rand() % 10 + 48;
	}
	vip_num[6] = '\0';
	return vip_num;
}