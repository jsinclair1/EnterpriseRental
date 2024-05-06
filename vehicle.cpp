#include "vehicle.h"
#include "sedan.h"
#include "truck.h"
#include "van.h"
#include "suv.h"


//Prints Out the Menu
void Menu(){
  cout << "Please select from the following options:" << endl;
  cout << "I - Inventory" << endl;
  cout << "R - Return Vehicle" << endl;
  cout << "F - Find Reservation" << endl;
  cout << "E - Exit" << endl;
}

//Reads Enterprise.txt and puts in into a Queue<Vehicle*> object
void readVehicleData(istream& in, Queue<Vehicle*>& RentQueue, ostream& outErr){  
  vector<string> row;
  string inRec, tempString;

  getline(in, inRec); //read record from file
  while (in.good()) {
    try{
      
      stringstream inSS(inRec); //Creats string stream
      row.clear();
      while (getline(inSS, tempString, ',')) { //Separte string stream on ,
        row.push_back(tempString); //Push each string onto a vector
      }

      //Variables for classes
      int year = stoi(row[0]);
      string make = row[1];
      string model = row[2];
      string type = row[3];
      int ID = stoi(row[4]);

      if (year < 2020){ //Checks if the car year is below 2020
        string error = "Unable to process: " + to_string(year) + " " + make + " , Car Year must be 2020 or higher!";
        throw runtime_error(error); //Throws runtime_error
      }

      Vehicle* VehiclePtr; //Creates a Vehicle pointer
      
      if (type == "Sedan"){ //Checks if type is a Sedan  
        VehiclePtr = new Sedan(year, make, model, type, ID); //Creats Sedan Object
        RentQueue.enQueue(VehiclePtr); //Adds it to a Vehicle* Queue
      }
      else if (type == "Truck"){ //Chekcs if type is a Truck
        VehiclePtr = new Truck(year, make, model, type, ID); //Creates Truck object
        RentQueue.enQueue(VehiclePtr); //Adds it to a Vehicle* Queue
      }
      else if (type == "Van"){
        VehiclePtr = new Van(year, make, model, type, ID); //Creates Van object
        RentQueue.enQueue(VehiclePtr); //Adds it to a Vehicle* Queue
      }
      else if (type == "SUV"){
        VehiclePtr = new SUV(year, make, model, type, ID); //Creates SUV object
        RentQueue.enQueue(VehiclePtr); //Adds it to a Vehicle* Queue
      }
      else{ //If there is not a type that mathces
        throw runtime_error("ERROR: Invalid Vehicle Type-> '" + type + "'");
      }
      getline(in, inRec); //get next input record
    }
    catch (const invalid_argument& e){
      outErr << "ERROR: Unable to process due to invalid stoi argument for car year" << endl << endl;
      getline(in, inRec); //get next input record
    }
    catch (const runtime_error& e){
      outErr << e.what() << endl <<endl;
      getline(in, inRec); //get next input record
    }
  }
}

//Reads the Reservation data and adds it to a Queue<ReservationInfo> data type
void readReservationData(istream& in, Queue<ReservationInfo>& Reservations) {
  
  vector<string> row;
  string inRec, tempString;
  
  getline(in, inRec); //read record from file
  while (in.good()) {
    stringstream inSS(inRec); //Creats string stream
    row.clear();
    while (getline(inSS, tempString, ',')) { //Separte string stream on ,
      row.push_back(tempString); //Push each string onto a vector
    }
    
    string name = row[0]; //Name
    string type = row[1]; //Car type
    string time = row[2]; //Car time

    ReservationInfo reservation; //Creates ReservationInfo struct
    reservation.name = name; //Adds name to struct
    reservation.rentType = type; //Adds type to struct
    reservation.time = time; //Adds time to struct
    
    Reservations.enQueue(reservation);//Adds struct to Queue
    getline(in, inRec);//get next input record
  }
}

//Rents out the cars to the customer and adds it to Queue<RentedCars>
//RentedCars is a struct that takes in a struct and Vehicle*
void RentCars(Queue<ReservationInfo> &reservations, Queue<Vehicle*> &RentQueue, Queue<RentedCars> &rentedCarInfo){

  while (!reservations.isEmpty()){ //While the reservations queue is not empty
    
    ReservationInfo obj = reservations.peek(); //Creates a ReservationInfo struct of the first item in queue
    
    while (!RentQueue.isEmpty()){ //While the rent queue is not empty
      
      Vehicle* vehicle = RentQueue.deQueue(); //Creates a Vehicle* struct of the first item in queue
      if (vehicle->getType() == obj.rentType){ //Checks if the vehicle type matches the reservation type
        
        RentedCars tempStorage; //Creates a RentedCars struct
        vehicle->setCheckedIn(false);//Sets vehicle to checked out
        tempStorage.rentedCar = vehicle;//Adds vehicle* to RentedCars struct
        tempStorage.reservationInfo = obj;//Adds reservation info to RentedCars struct
        rentedCarInfo.enQueue(tempStorage);//Adds RentedCars struct to Queue
        reservations.deQueue();//Removes reservation from queue
        break; //Breaks out of while loop and reuslts in going to the next reservation
        
      }
      else{ //If the vehicle type does not match the reservation type
        
        RentQueue.enQueue(vehicle);//Adds vehicle* to the end of the Queue
      
      }  
    }
  }
}

//Prints the rented cars to the output file
void PrintEODReport(Queue<RentedCars> &rentedCarInfo, ostream& outFile){
  
  outFile << "CAR RENTAL REPORT FOR TODAY: \n\n" << endl;
  RentedCars temp = rentedCarInfo.peek(); //Creates a RentedCars struct of the first item in queue
  Queue<RentedCars> tempCopyQueue; //Creates a queue for storage
  
  while (!rentedCarInfo.isEmpty()){
    
    temp = rentedCarInfo.deQueue(); //Removes the first item in queue while retaining the data

    //Writes informationfrom reservationInfo struct
    outFile << "Customer: " << temp.reservationInfo.name << endl;
    outFile << "Car Type: " << temp.reservationInfo.rentType << endl;
    outFile << "Time: " << temp.reservationInfo.time << endl;

    //Writes information from rentedCar Vehicle*
    outFile << "Vehicle Given: " << temp.rentedCar->getYear() << ", " << temp.rentedCar->getMake() << " " << temp.rentedCar->getModel() << ", TYPE: " << temp.rentedCar->getType() << ", ID: " << temp.rentedCar->getID() << endl << endl;
    tempCopyQueue.enQueue(temp);//Adds RentedCars struct to the end of the Queue
    
  }


  //Following code adds the orginal data back into rentedCarInfo<RentedCars> Queue
  while (!tempCopyQueue.isEmpty()){
    
    temp = tempCopyQueue.deQueue();
    rentedCarInfo.enQueue(temp);
  }
  
  outFile << "\n" << endl;
}

//Prints the rented cars to the output file
void ReturnCar(Queue<Vehicle*> &RentQueue, Queue<RentedCars> &rentedCarInfo, ostream &outFile, ostream &outErr){
  
  outFile << "RETURNED CARS\n" << endl;

  //Will be used to figure out the size of the Queue
  int i = 0;
  int x = 1;

  Queue<RentedCars> tempQueue;//Creates a queue for storage

  //Follwoing code will get the size of the Queue
  while (!rentedCarInfo.isEmpty()){//While the rentedCarInfo Queue is not empty
    
    i++;//Adds 1 to i
    RentedCars tempCar = rentedCarInfo.deQueue();//Removes the first item in queue while retaining the data
    tempQueue.enQueue(tempCar);//Adds RentedCars Queue to the end of the tempoary Queue
  
  }
  
  while (!tempQueue.isEmpty()){ //While the temporary Queue is not empty
    
    RentedCars tempCar = tempQueue.deQueue();//Removes the first item in queue while retaining the data
    rentedCarInfo.enQueue(tempCar);//Adds back to the orgianl queue
  
  }

  cout << "\nPlease enter the 6-Digit Vehcile ID of the car you want to return:" << endl;
  
  string strVehicleID;
  getline(cin, strVehicleID); //Gets the vehicle ID from user
  int vehicleID;

  while (!rentedCarInfo.isEmpty()){//While the rentedCarInfo Queue is not empty
  
    try{
    
      vehicleID = stoi(strVehicleID);//Converts string to int
      RentedCars temp = rentedCarInfo.deQueue();//Removes the first item in queue while retaining the data
      Vehicle* vehicle = temp.rentedCar;//Creates a Vehicle* of the rentedCars struct
      
      if (vehicle->getID() == vehicleID){//If the vehicleID matches the vehicleID of the input entered
      
        vehicle->setCheckedIn(true); //ChekecedIn is not true

        //Prints out a thank to the customer
        cout << "\nThank you " << temp.reservationInfo.name << " for returning your car." << endl;
        cout << "Check Report File for more details.\n" << endl;

        //Writes to the report file the info
        outFile << "Returned: " << vehicle->getYear() << " " << vehicle->getMake() << " " << vehicle->getModel() << " " << vehicle->getType() << ", ID: " << vehicle->getID() << " from " << temp.reservationInfo.name << endl << endl;
        
        RentQueue.enQueue(vehicle); //Adds the vehicle back to the rentedCars Queue
        return;//Exits function
      
      }
      
      rentedCarInfo.enQueue(temp);//Adds back to the end of the Queue if not found
      x++;//Adds 1 to x
      if (x == i+1){//If x is equal to the size of the Queue

        //Prints out an error message
        cout << "\nVehicle ID not found. Please try again.\n" << endl;
        
        //Throws runtime error
        throw runtime_error("ERROR: Vehicle ID: " + to_string(vehicleID) + " was not found");
      
      }
    }
    catch (const invalid_argument& e){//If the input is not an int

      //Prints out an error message
      cout << "\nOpps, somehting went wrong!\n" << endl;
      //Writes the error to error report file
      outErr << "ERROR: Unable to process due to invalid stoi argument" << endl << endl;
      return;//Exits function
    
    }
    catch (const runtime_error& e){//If the input is not found in the Queue
      
      outErr << e.what() << endl;//Writes to the error file
      return;//Exits function
    
    }
  }
}

//Function to print out the rented cars
void PrintInventory(Queue<Vehicle*> &RentQueue, ostream& outFile){
  
  Queue<Vehicle*> tempQueue; //Creates a temporary Queue
  outFile <<"CURRENT CARS IN INVENTORY:\n\n" << endl; 

  while(!RentQueue.isEmpty()){//While the rentedCars Queue is not empty
  
    Vehicle* vehicle = RentQueue.deQueue();//Removes the first item in queue while retaining the data
    
    //Writes the Vehicle data to the output file
    outFile << "Year: " << vehicle->getYear() << endl;
    outFile << "Make: " << vehicle->getMake() << endl;
    outFile << "Model: " << vehicle->getModel() << endl;
    outFile << "Type: " << vehicle->getType() << endl;
    outFile << "\n" << endl;
    tempQueue.enQueue(vehicle);//Adds the vehicle back to the end of the Queue
  
  }
  
  while (!tempQueue.isEmpty()){//While the temporary Queue is not empty
    
    Vehicle* vehicle = tempQueue.deQueue();//Removes the first item in queue while retaining the data
    RentQueue.enQueue(vehicle);//Adds the vehicle back to the end of the orignal Queue
  
  }
}

//Function to find customer information
void FindReservation(Queue<RentedCars> &rentedCarInfo, ostream& outErr, ostream &outFile){

  //Will be used to get the size
  int i = 0;
  int x = 1;

  Queue<RentedCars> tempQueue;//Creates a temporary Queue

  //Following code gets the size of the Queue
  while (!rentedCarInfo.isEmpty()){//While the rentedCars Queue is not empty
  
    i++;
    RentedCars tempCar = rentedCarInfo.deQueue();
    tempQueue.enQueue(tempCar);
  
  }
  //Following code adds data back to the orginal queue
  while (!tempQueue.isEmpty()){
  
    RentedCars tempCar = tempQueue.deQueue();
    rentedCarInfo.enQueue(tempCar);
  
  }

  cout << "\nPlease Enter a Name: " << endl;
  
  string name;
  getline(cin, name);//Gets the name of the customer
  
  cout << "\nYou typed: " << name << endl;
  
  while (!rentedCarInfo.isEmpty()){//While the rentedCars Queue is not empty
  
    try{//Trys to get the customer ID
    
      RentedCars temp = rentedCarInfo.deQueue();//Removes the first item in queue while retaining the data
      
      if (temp.reservationInfo.name == name){//If the name is equal to the name found in the Queue

        //Prints info was found
        cout << "Reservation Found: Check Report File for more info \n" << endl;

        //Writes the Vehicle data to the output file with customer information
        outFile << "Reservation Found: " << temp.reservationInfo.name << ", Time Rented: " << temp.reservationInfo.time << ", Car: " << temp.rentedCar->getYear() << " "<< temp.rentedCar->getMake() << " " << temp.rentedCar->getModel() << " " << temp.rentedCar->getType() << ", Vehicle ID: " << temp.rentedCar->getID() << endl << endl;
        
        rentedCarInfo.enQueue(temp);//Adds the vehicle back to the end of the orignal Queue
        return;//Exits function
      
      }
      
      rentedCarInfo.enQueue(temp);//Adds the vehicle back to the end of the orignal Queue
      x++;//Adds to the x value
      
      if (x == i+1){//If the x value is equal to the size of the Queue
        throw runtime_error("ERROR: No reservation with the name '" + name + "' was found!'");
      
      }
    }
    catch (runtime_error& e){//Cathecs if the Customer was not found in the Queue

      //Prints out there was an error
      cout << "ERORR: Check error file for more detail\n" << endl;
      
      //Writes the error to the output file
      outErr << e.what() << endl << endl;
      return;//Exits function
    
    }
  }
}