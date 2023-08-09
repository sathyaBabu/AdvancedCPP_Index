//
//  main.cpp
//  13_1_SI_Singleton_3_call_once
//
//  Created by Sathya Babu on 01/08/23.
//
#include <mutex>
#include<iostream>
using namespace std ;

//Singleton* init() { instance_ = new Singleton() ;}

class Singleton {
public:
     static
    Singleton& getInstance() {
        
        // lazy obj or functions..
        
        std::call_once(flag_, []() { instance_ = new Singleton(); } );
        
        return* instance_ ;
        
        
    }
     
private:
    Singleton() {}

    static Singleton* instance_;
    static std::once_flag flag_;
    
    };


Singleton* Singleton::instance_ = nullptr;
std::once_flag Singleton::flag_;


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << " call_once \n ";
    
    
    Singleton& s1 = s1.getInstance();
    Singleton& s2 = s2.getInstance();

    if (&s1 == &s2) {
        std::cout << "Singleton works!" << std::endl;
    }
    
    return 0;
}
