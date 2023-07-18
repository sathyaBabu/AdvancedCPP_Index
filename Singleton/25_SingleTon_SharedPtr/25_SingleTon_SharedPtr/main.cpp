//
//  main.cpp
//  25_SingleTon_SharedPtr
//
//  Created by Sathya Babu on 25/04/23.
//
#include <iostream>
#include <functional>
#include <memory>
#include <string>
using namespace std;

class Singleton
{
public:
    Singleton(Singleton const&)             = delete;
    Singleton& operator = (Singleton const&) = delete;

static std::shared_ptr<Singleton> instance()
{
    static std::shared_ptr<Singleton> s{ new Singleton };
    cout << " the number of share objects " << s.use_count() << endl ;
    return s;
}

    ~Singleton() { std::cout << "calling destructor  "<< std::endl;}
private:
    Singleton() {}
};

int main()
{
    std::cout << "Cleaner way of creating SingleTon "<< std::endl;
     std::shared_ptr<Singleton> obj1 = Singleton::instance();
     std::shared_ptr<Singleton> obj2 = Singleton::instance();
  
     return 0;
}
/*
 Cleaner way of creating SingleTon
  the number of share objects 1
  the number of share objects 2
 Program ended with exit code: 0
 */

