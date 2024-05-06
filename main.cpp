#include "vehicle.h"
#include "sedan.h"
#include "truck.h"
#include "van.h"
#include "suv.h"

int main() {

  //Opens files
  ifstream inFile;
  inFile.open("VJCWheels.txt");
  
  ifstream reservFile;
  reservFile.open("Reservations.txt");

  ofstream outFile;
  outFile.open("Report.txt");

  ofstream outErr;
  outErr.open("ErrorFileReport.txt");

  //Checks if files opened
  if (!inFile.is_open()){
    cout << "The VJCWheels.txt did not open" << endl;
    return -1;
  }

  if (!reservFile.is_open()){
    cout << "The Reservations.txt did not open" << endl;
    return -1;
  }
  if (!outFile.is_open()){
    cout << "The Report.txt did not open" << endl;
    return -1;
  }
  if (!outErr.is_open()){
    cout << "The Error File did not open" << endl;
    return -1;
  }

  //Queues to be used
  Queue<Vehicle*> RentQueue;
  Queue<ReservationInfo> Reservations;
  Queue<RentedCars> rentedCarsInfo;

  
  cout << "Welcome to Rental Car Fleet Management System" << endl;

  readVehicleData(inFile,RentQueue, outErr); //Reads VJCWheels Data
  outFile << "VJCWheels Data Loaded" << endl;
  readReservationData(reservFile,Reservations); //Reads Reservations Data
  outFile << "Reservations Data Loaded" << endl;
  RentCars(Reservations,RentQueue, rentedCarsInfo); //Rents out to the reservations in place
  outFile << "Cars Rented have been rented out" << endl;
  PrintEODReport(rentedCarsInfo, outFile); //Writes to the report file the vehicles that have been rented and the customers assoicated with those vehicles
  

  string choice; 
  Menu(); //Function that prints out the menu
  getline(cin,choice); //input for the menu

  while (choice != "E"){
    if (choice == "I"){
      
      PrintInventory(RentQueue, outFile); //Writes the current remaning invenotry to report file
      Menu();
      getline(cin,choice);
    }
    else if (choice == "R"){
      ReturnCar(RentQueue,rentedCarsInfo, outFile, outErr); //Will return the car when given proper input and write the car returned in report file
      Menu();
      getline(cin,choice);
    }
    else if (choice == "F"){
      cin.clear();
      FindReservation(rentedCarsInfo, outErr, outFile); //Will find cusomter reservations when given proper input and write the reservations to report file
      Menu();
      getline(cin,choice);
    }
    else{ //When the choice is invalid
      cout << "Invalid Choice, please try again!\n" << endl;
      Menu();
      getline(cin,choice);
    }
    cout << endl;
  }
  
  cout << "Thank you for using the Rental Car Fleet Management System" << endl;

  //Closes Files
  inFile.close();
  reservFile.close();
  outFile.close();
  return 0;
}
