#pragma once
#include "vehicle.h"
using namespace std;

class Sedan : public Vehicle {
    private:
      int numSeats;
      int cargoSpace;
    public:
      Sedan() : Vehicle(){};
      Sedan(int year, string make, string model, string type, int ID) : Vehicle(year, make, model, type, ID){
      numSeats = 5;
      cargoSpace = 2;
      };
      int getSeats() { return numSeats;};
      void printAvailable();
        //prints cars that are checked in
      void printCheckedOut();
      
};