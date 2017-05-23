#include <iostream>
#include "systemController.h"

//using namespace std;

int main() {
	std::cout << "hello, test" << std::endl;
	systemController *sc = new systemController;
	//sc->noteHistory("hola");
  
  //Driver *dri = new Driver;
  //sc->punishment(dri);
  sc->reward();
  //sc->show_money();
//	sc->addDriver();
	//sc->DeleteAllDriver();
	//system("PAUSE");
	//sc->driverListAll();
	//std::system("PAUSE");
	//sc->driverListAll();
	//char teleNum[20];

	
	//std::string str;
	//std::cin.getline(str, 5);
	//std::cin >> str;
//	std::cout << sizeof(str) << std::endl; 
	//std::cout << (str == "helo") << '\n';
	//std::cout << str << std::endl;

	//std::cin.getline(str, 5);
	//std::cout << str << std::endl;
	system("PAUSE");
	return 0;
}