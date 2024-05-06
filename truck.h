#pragma once
#include "vehicle.h"
using namespace std;

class Truck : public Vehicle {
    private:
      int numSeats;
      int cargoSpace;
    public:
      Truck() : Vehicle(){};
      Truck(int year, string make, string model, string type, int ID) : Vehicle(year, make, model, type, ID){
        numSeats = 5;
        cargoSpace = 4;
      }

      void printAvailable();
        //prints cars that are checked in
      void printCheckedOut();

};