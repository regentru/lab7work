#include <iostream>
#include <vector>
using namespace std;

class Train {
protected:
    int lowerSeats;
    int upperSeats;
    int lowerSideSeats;
    int upperSideSeats;
    bool hasAdditionalServices;
public:
    virtual double getProfit() = 0;
    int getLowerSeats() {
        return lowerSeats;
    }
    int getUpperSeats() {
        return upperSeats;
    }
    int getUpperSideSeats() {
        return upperSideSeats;
    }
    int getLowerSideSeats() {
        return lowerSideSeats;
    }
};

class Passenger : public Train {
public:
    Passenger(int lower, int upper, int lowerSide, int upperSide, bool services) {
        lowerSeats = lower;
        upperSeats = upper;
        lowerSideSeats = lowerSide;
        upperSideSeats = upperSide;
        hasAdditionalServices = services;
    }
};

class Sitting : public Passenger {
private:
    double lowerPrice = 111.05;
    int upperPrice = 0;
    double lowerSidePrice = 100.05;
    int upperSidePrice = 0;
public:
    Sitting(int lower, int upper, int lowerSide, int upperSide, bool services) :
        Passenger(lower, upper, lowerSide, upperSide, services) {}

    double getProfit() override {
        return lowerPrice * this->getLowerSeats() + lowerSidePrice * this->getLowerSideSeats();
    }
};

class Platzkart : public Passenger {
private:
    double lowerPrice = 111.05;
    int upperPrice = 100.1;
    double lowerSidePrice = 100.05;
    int upperSidePrice = 99.42;
public:
    Platzkart(int lower, int upper, int lowerSide, int upperSide, bool services) :
        Passenger(lower, upper, lowerSide, upperSide, services) {}

    double getProfit() override {
        return lowerPrice * this->getLowerSeats() + lowerSidePrice * this->getLowerSideSeats()
            + upperPrice * this->getUpperSeats() + upperSidePrice * this->getUpperSideSeats();
    }
};

class Coupe : public Passenger {
private:
    double lowerPrice = 151.05;
    int upperPrice = 150.1;
    double lowerSidePrice = 0;
    int upperSidePrice = 0;
public:
    Coupe(int lower, int upper, int lowerSide, int upperSide, bool services) :
        Passenger(lower, upper, lowerSide, upperSide, services) {}

    double getProfit() override {
        return lowerPrice * this->getLowerSeats() + upperPrice * this->getUpperSeats();
    }
};

class SV : public Passenger {
private:
    double lowerPrice = 211.05;
    int upperPrice = 0;
    double lowerSidePrice = 0;
    int upperSidePrice = 0;
public:
    SV(int lower, int upper, int lowerSide, int upperSide, bool services) :
        Passenger(lower, upper, lowerSide, upperSide, services) {}

    double getProfit() override {
        return lowerPrice * this->getLowerSeats();
    }
};

class PassengerTrain {
private:
    vector<Train*> s;
public:
    void add(Train* t) {
        s.push_back(t);
    }

    double getTotalProfit() {
        double total = 0;
        for (Train* t : s) {
            total += t->getProfit();
        }
        return total;
    }
};
