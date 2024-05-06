#pragma once
#include "vehicle.h"
using namespace std;

class Van : public Vehicle {
    private:
      int numSeats;
      int cargoSpace;
    public:
      Van() : Vehicle(){};
      Van(int year, string make, string model, string type, int ID) : Vehicle(year, make, model, type, ID){
        numSeats = 7;
        cargoSpace = 5;
      }

      void printAvailable();
        //prints cars that are checked in
      void printCheckedOut();

};