#pragma once
#include "queue.h"


class Vehicle {
    private:
      int year; //Car Year
      string make; //Car Brand
      string model; //Car Model from Brand
      string type; //Car Type
      int ID; //Car ID
      bool CheckedIn; //Is Checked In
    public:

      //Constructors
      Vehicle() { year = 0; make = ""; model = ""; type = ""; ID = 0; CheckedIn = true;};
      Vehicle(int year, string make, string model, string type, int ID) {
      this->year = year;
      this->make = make;
      this->model = model;
      this->type = type;
      this->ID = ID;
      this->CheckedIn = true; //Means that car is in the lot
      };

      //Getters
      int getYear() { return year; };
      string getMake() { return make; };
      string getModel() { return model; };
      string getType() { return type; };
      int getID() { return ID; };
      bool getCheckedIn() { return CheckedIn;};

      //Setters
      void setYear(int year) { this->year = year; };
      void setMake(string make) { this->make = make; }; 
      void setModel(string model){ this->model = model;};
      void setType(string type) { this->type = type; };
      void setID(int ID) { this->ID = ID; };
      void setCheckedIn(bool CheckedIn) { this->CheckedIn = CheckedIn;};

};

//Struct for Reservation.txt info
struct ReservationInfo {
    string name;
    string rentType;
    string time;
};


//Struct for cars that are currenlty rented
struct RentedCars {
    Vehicle* rentedCar;
    ReservationInfo reservationInfo;
};

void Menu(); //Prints a menu

//Reads EnterpriseFleet.txt and creates class objects from the data and puts in a Queue
void readVehicleData(istream& in, Queue<Vehicle*>& RentQueue, ostream& outErr);

//Reads Reservations.txt and adds data to a Queue<ReservationInfo>
void readReservationData(istream& in, Queue<ReservationInfo>& Reservations);

//Confirms the reservations and adds it to a Queue while getting rid of the current Inventory;
void RentCars(Queue<ReservationInfo>& reservations, Queue<Vehicle*> &RentQueue, Queue<RentedCars> &rentedCarInfo);

//Prints Report of the Cars rented with the customer and vehicle information
void PrintEODReport(Queue<RentedCars> &rentedCarInfo, ostream& outFile);

//Returns a car, by adding it back to RentQueue
void ReturnCar(Queue<Vehicle*> &RentQueue, Queue<RentedCars> &rentedCarInfo, ostream &outFile, ostream &outErr);

//Prints the current inventory of RentQueue
void PrintInventory(Queue<Vehicle*> &RentQueue, ostream& outFile);

//Finds a customer's reservation info.
void FindReservation(Queue<RentedCars> &rentedCarInfo, ostream& outErr, ostream &outFile);
