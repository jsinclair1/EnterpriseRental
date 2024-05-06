#pragma once
#include "vehicle.h"
using namespace std;

class SUV : public Vehicle {
    private:
      int numSeats;
      int cargoSpace;
    public:
      SUV() : Vehicle() {};
      SUV(int year, string make, string model, string type, int ID) : Vehicle(year, make, model, type, ID) {
        numSeats = 7;
        cargoSpace = 4;
      };
      void printAvailable();
        //prints cars that are checked in
      void printCheckedOut();

};