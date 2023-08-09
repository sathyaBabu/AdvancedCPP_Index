//
//  main.cpp
//  17_PetrolDispence
//
//  Created by Sathya Babu on 25/07/23.
//
#include <iostream>

class PetrolTank {
public:
    virtual void dispensePetrol() = 0;
    virtual double getPetrolLevel() const = 0;

    void displayPetrolAvailability() const {
        std::cout << "Petrol Available: " << getPetrolLevel() << " liters" << std::endl;
    }
};

class Car {
public:
    Car(PetrolTank& tank) : petrolTank(tank) {}

    void move() {
        // Simulate moving the car
        // Reduce petrol level with each move
        petrolTank.dispensePetrol();
        petrolTank.displayPetrolAvailability();
    }

private:
    PetrolTank& petrolTank;
};

class PetrolTankImpl : public PetrolTank {
public:
    PetrolTankImpl(double capacity) : capacity(capacity), petrolLevel(capacity) {}

    void dispensePetrol() override {
        if (petrolLevel > 0) {
            petrolLevel -= 0.5; // Simulate petrol consumption
        }
    }

    double getPetrolLevel() const override {
        return petrolLevel;
    }

private:
    double capacity;
    double petrolLevel;
};

int main() {
    // Create a petrol tank with a capacity of 50 liters
    PetrolTankImpl petrolTank(50.0);

    // Create a car and link it with the petrol tank
    Car car(petrolTank);

    // Simulate car movements and display petrol availability
    car.move();
    car.move();
    car.move();

    return 0;
}
/*
 Petrol Available: 49.5 liters
 Petrol Available: 49 liters
 Petrol Available: 48.5 liters
 Program ended with exit code: 0
 */
