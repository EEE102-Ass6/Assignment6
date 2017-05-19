#include "systemController.h"
class systemController {
public:
  systemController ();

  void systemController::searchKey(string kesy) {
    if (driver->retrieve(keys)) {
        //show infomation of diver
    }
    else if (vehicle->retrieve(keys)) {
      //show infomation of vehicle.
    }
  }
  bool systemController::addDirver(){
      std::string name, gender, telephoneNumber;
      std::cout << "Your Name: " << '\n';
      std::cin >> name;
      std::cout << "Your Gender: " << '\n';
      std::cin >> gender;
      std::cout << "Your Telephone Number: " << '\n';
      std::cin >> telephoneNumber;
      this->driver = new Driver(name, gender, telephoneNumber);
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

      this->vehicle = new Vehicle(carNumber,,licPlate,type);
      return true;
  }

  void systemController::vehicleListAll() {
      
  }

  virtual ~systemController ();
};
