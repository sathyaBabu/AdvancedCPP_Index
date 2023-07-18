//
//  main.cpp
//  TrialingReturnType
//
//  Created by Sathya Babu on 12/07/23.
//

#include <iostream>
#include <tuple>
using namespace std;

auto testSpeedString = [](int speed) -> std:: string { if (speed > 100 )
return "you're a super fast" ; return "you're a regular" ;
};

int main() {
    auto str = testSpeedString(100 );
    str += " driver" ; // works fine
    cout << " returned : " << str <<  endl ;
}

// returned : you're a regular driver
