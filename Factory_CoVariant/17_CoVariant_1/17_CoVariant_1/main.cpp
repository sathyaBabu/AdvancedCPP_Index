//
//  main.cpp
//  17_CoVariant_1
//
//  Created by Sathya Babu on 31/10/22.
// https://www.sandordargo.com/blog/2020/08/19/covariant-return-types
// good explination in jave similar code
// https://www.youtube.com/watch?v=f5w4I_NL5cM
// YET ANOTHER AMAZING way of looing at it from basics make sure to change the code
// https://www.geeksforgeeks.org/advanced-c-virtual-constructor/
// return a covariant type. In other words, you can replace the original type with a “narrower” one, i.e. with a more specified data type.

/*
 In object-oriented programming, a covariant return type of a method is one that can be replaced by a "narrower" type when the method is overridden in a subclass. A notable language in which this is a fairly common paradigm is C++.
 - Wikipedia
 
 covariant
 virtual constructors
 Factory
 Abstract factory
 Prototype
 proxy
 flyweight
 
 Composition
 deligation
 
 Dispatcher
 
 */



#include <iostream>
using namespace std;

// FAcTORY provide an interface without eposing  its implimentation
// To achive the following we have to create an abstraction inheritance latyer on top

class Car {
public:
 virtual ~Car() = default;
};

class SUV : public Car { public : SUV() { cout << "SUV produced " << endl;  } };
class CarSports : public Car { public : CarSports () { cout << "Sports Car   produced " << endl;  } };



// covariant takes care of three diffrent kind of return type in SUV* produce()/Car* produce()/CarSports* produce()
// To achive the following we have to create an abstraction inheritance latyer on top

class CarFactoryLine {
public:
    virtual Car* produce() {
        return new Car{};
    }
};

class SUVFactoryLine : public CarFactoryLine {
public:
    virtual SUV* produce() override {
        return new SUV{};
    }
};

class CarSportsFactoryLine : public CarFactoryLine {
public:
    virtual CarSports* produce() override {
        return new CarSports{};
    }
};


int main () {
    
    /*
     Leads to an error
         SUVFactoryLine sf;
         SUV* c = sf.produce();
     output:
     main.cpp: In function 'int main()':
     main.cpp:27:20: error: invalid conversion from 'Car*' to 'SUV*' [-fpermissive]
        27 | SUV* c = sf.produce();
           |          ~~~~~~~~~~^~
           |                    |
           |                    Car*
     
     Another aproach
     
        SUVFactoryLine sf;
         Car* car = sf.produce();
         SUV* suv = dynamic_cast<SUV*>(car);
         if (suv) {
             std::cout << "We indeed got a SUV\n";
         } else {
             std::cout << "Car is not a SUV\n";
         }
     
     sake of brevity, I didn’t delete the pointers. It’s already too long.
     
     
     So ideally, SUVFactoryLine::produce should be able to change its return type fixed into SUV* while still keeping the override specifier. Is that possible?

     It is!

     This below example works like a charm:
     
   
     
     */
    SUVFactoryLine sf;
    
    SUV* car = sf.produce();
    
    
   CarFactoryLine cf;
   Car* car1 = cf.produce();
    
    CarSportsFactoryLine sc;
    CarSports* scar = sc.produce();
    
    
}
