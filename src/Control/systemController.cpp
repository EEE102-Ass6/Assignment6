#include "systemController.h"
class systemController {
  systemController::systemController ();

  bool systemController::searchKey(char* keys) {
    if (vehicleList->Find(keys) != NULL) {
            Vehicle *veh = vehicleList->Find(keys);
            veh->displayInfo();
            return true;
    }
    else if (driverList->Find(keys)) {
            Driver *dri = driverList->Find(keys);
            dri->displayInfo();
            return true;
    }
    else {
        std::cout << "Object NOT found" << '\n';
        return false;
    }
  }

  bool systemController::addDirver(){
      char *name[20], gender[20], telephoneNumber;
      bool bGender;
      std::cout << "Your Name: " << '\n';
      std::cin >> name;
      std::cout << "Your Gender: " << '\n';
      std::cin >> gender;
      if (gender == 'male' || gender == 'MALE') {
              bGender = true;
      }else{
              bGender = false;
      }
      std::cout << "Your Telephone Number: " << '\n';
      std::cin >> telephoneNumber;

      link = {0,0}
      user_info newDriverObject = {name, telephoneNumber, bGender, link}
      // create a struct to store the infomation
      driverList->addNew(newDriverObject);


      // Add successfully new driver;
      // show list of vehicles waiting for choosing one anh link em up;
      this->vehicleListAvaliable;
      char *oldCarInfo;
      std::cout << "Please enter the plate license of car you want link: " << '\n';
      std::cin >> oldCarInfo;
      Driver *dri = driverList->Find(oldCarInfo);

      dri->link(telephoneNumber);
      vehicleList->modify(oldCarInfo,)





      return true;

  }

  bool systemController::addVehicle(){
      int carNumber;
      std::string licPlate, type;
      std::cout << "Car Number: " << '\n';
      std::cin >> carNumber;
      std::cout << "license Plate: " << '\n';
      std::cin >> licPlate;
      std::cout << "Type of Vehicle" << '\n';
      std::cin >> type;
      vehicle->addNew(carNumber,,licPlate,type);
      return true;
  }

  void systemController::vehicleListAll() {
        vehicle->listAll();
  }

  void systemController::driverListAll(){
          driver->listAll();
  }

  void systemController::vehicleListAvaliable(){
          vehicle->listAvaliable();
  }

  void systemController::driverListAvaliable(){
          driver->listAvaliable();
  }

  bool systemController::modifyVehicle(){
          int indexWho;
          while (true) {
                  std::cout << "Plase located (using Number)at Who: " << '\n';
                  std::cin >> indexWho;
                  if (vehicle->hasItem(keys)) {
                          return true;
                  }else {
                        std::cout << "!!!Object NOT found!!!" << '\n';
                  }
          }
  }

  bool systemController::modifyDriver(){
          int indexWho, indexAtt;
          char *changedInfo[20];
          while (true) {
                  std::cout << "Plase located (using Number)at Who: " << '\n';
                  std::cin >> indexWho;
                  if (driver->hasItem(keys)) {
                          // Find the object
                          std::cout << "What attributes you want to modify?" << '\n';
                          std::cin >> indexAtt;
                          std::cout << "MOdified Infomation: "<< '\n';
                          std::cin >> changedInfo;
                          driver->modifyInfo(indexAtt, changedInfo);
                          return true;
                  }else {
                        std::cout << "!!!Object NOT found!!!" << '\n';
                  }
          }
  }

  bool systemController::modifyVehicle(){
          int indexWho, indexAtt;
          char *changedInfo[20];
          while (true) {
                  std::cout << "Plase located (using Number)at Which vehicle: " << '\n';
                  std::cin >> indexWho;
                  if (file->getDriverItem(keys)) {
                          // Find the object
                          std::cout << "Which attributes you want to modify?" << '\n';
                          std::cin >> indexAtt;
                          std::cout << "Modified Infomation: "<< '\n';
                          std::cin >> changedInfo;
                          file->modifyVehicleInfo(indexAtt, changedInfo);
                          return true;
                  }else {
                        std::cout << "!!!Object NOT found!!!" << '\n';
                  }
          }

  }

  void systemController::showEditingRecords(){
          file->listAllHistoryRecords();
  }

  void systemController::regPayment(){
          file->
  }

  void systemController::regRewards(){
          file->
  }

  void systemController::regPunishment(){
          file->
  }

  bool systemController::driverDelete(){
          int indexWho;
          while (true) {
                  std::cout << "Please located (using Number)at WHO: " << '\n';
                  std::cin >> indexWho;
                  if (file->getDriverItem(keys)) {
                          // Find the object
                          file->deleteDriver(indexWho);
                          return true;
                  }else {
                        std::cout << "!!!Object NOT found!!!" << '\n';
                  }
          }
  }

  bool systemController::vehicleDelete(){
          int indexWho;
          while (true) {
                  std::cout << "Please located (using Number)at WHO: " << '\n';
                  std::cin >> indexWho;
                  if (file->getDriverItem(keys)) {
                          // Find the object
                          file->deleteDriver(indexWho);
                          return true;
                  }else {
                        std::cout << "!!!Object NOT found!!!" << '\n';
                  }
          }
  }

  void systemController::DeleteAllVehicle(){
          vehicle->deleteAll();
          std::cout << "Delete successful!" << '\n';
  }

  void systemController::DeleteAllDriver(){
          driver->deleteAll();
          std::cout << "Delete successful!" << '\n';
  }
// show the historyNote
  void systemController::showEditingRecords(){
          std::ifstream historyNote("editing_history.txt", std::ios::in);
          if (historyNote.is_open()) {
                  std::string line;
                  while (std::getline(historyNote, line)) {
                          std::cout << line << '\n';
                  }
                  historyNote.close();
          }
          else {
                  std::cerr << "Unable to open file\n";
          }
  }

  void systemController::noteHistory(std::string info){
          std::ofstream historyNote("editing_history.txt", std::ios::out);
          if (historyNote.is_open()) {
                  historyNote << info << endl;
                  historyNote.close();
          }
  }

  void systemController::deleteHistory(){
        std::ofstream historyNote("editing_history.txt", std::ios::trunc);
        /*if(!fileout){
        cout << "Create file failure...\n";
}*/
        historyNote.close();
  }

  void systemController::changeSudoPassword(char *psw) {
          std::ofstream clearFile("password.txt", std::ios::trunc);
          std::ofstream passWord("password.txt", std::ios::out);
          if (passWord.is_open()) {
                  passWord << psw << endl;
                  passWord.close();
          }
  }

  char *systemController::getUserPassword(){
          char password[30];
          std::ifstream getPassword("password.txt", std::ios::in);
          if (getPassword.is_open()) {
                try{
                        std::getline(getPassword, password); // set password to the first line of the file.
                }catch{
                        password = NULL;
                }
                  getPassword.close();
                  return password; // maybe wrong...
          }
          else {
                  std::cerr << "Get password error..." << '\n';
                  return NULL;
          }

  }


  virtual ~systemController ();
};
