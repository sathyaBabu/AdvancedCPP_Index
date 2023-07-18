//
//  main.cpp
//  CO4_VisitorPorted
//
//  Created by Sathya Babu on 12/01/22.
//
// Visitor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include <variant>
#include <cstdio>
#include <vector>

using namespace std;


template<class... Ts>
struct overload : Ts...
{ using Ts::operator()...; };

template<class... Ts>
overload(Ts...)->overload<Ts...>;


// Visitor Accept
class Color   /// red  - blue
{
public:
    //virtual void accept() = 0;
};

class Red : public Color
{
public:
    static int count;

    void eye()
    {
        cout << "Red::eye\n";
    }
};

int  Red::count = 0;


class Blu : public Color
{
public:
    static int count;

    void sky()
    {
        cout << "Blu::sky\n";
    }
};

int Blu::count = 0;


auto CallVisitable = overload
{
    [](Red& r) {r.eye(); },
    [](Blu& b) {b.sky(); },
};

auto CountVisitable = overload
{
    [](Red& r) {++r.count; },
    [](Blu& b) {++b.count; },
};

void Report()
{
    cout << "Red Count : " << Red::count << endl;
    cout << "Blue Count : " << Blu::count << endl;
}



int main(int argc, const char * argv[]) {

    std::vector<std::variant<Red, Blu>> varColour = {Red(), Blu(), Red(), Red(), Blu()};


    for (auto v : varColour)
    {
        std::visit(CallVisitable, v);
        std::visit(CountVisitable, v);
    }

    Report();
}
/*
 
 Red::eye
 Red::eye
 Blu::sky
 Red Count : 3
 Blue Count : 2
 Program ended with exit code: 0
 
 */
/*
 
     Double dispatch is a must
     Word
         View
         Sb
         model
   
     VS
 
      Varint and Visit..
 
 
 */
