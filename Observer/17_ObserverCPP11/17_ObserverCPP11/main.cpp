//
//  main.cpp
//  17_ObserverCPP11
//
//  Created by Sathya Babu on 22/06/22.
//// Observers A Better aproach

#include <iostream>
#include <functional>
#include <vector>

class Observable {
    using Callback = std::function<void(void)>;
    std::vector< Callback > notifications;
public:
    void attach(Callback c) { notifications.push_back(c); }
    void notify() { for (auto& c : notifications) c(); }
};

struct GetToWork{
    void drive() { std::cout << "Let's drive to work \n"; }
    
};

struct Coffee {
    void sipp() { std::cout << "Let's have some coffee \n"; }
};

struct Morning : public Observable {
    void wakeUp() {
        std::cout << "Good Morning.. Wake up \n";
        notify();
        
    }
};

int main() {
   Morning goodMorning ;
   
    Coffee  coffee ;
    
    GetToWork getToWork ;

    // lambda
    goodMorning.attach([ &getToWork ] {getToWork.drive();});
    goodMorning.attach([ &coffee ] {coffee.sipp();});
    goodMorning.wakeUp();
  //  goodMorning.notify();
}
/*
 Good Morning.. Wake up
 Let's drive to work
 Let's have some coffee
 Program ended with exit code: 0
 */
