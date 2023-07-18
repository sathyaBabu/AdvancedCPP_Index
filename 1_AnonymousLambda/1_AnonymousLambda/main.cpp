//
//  main.cpp
//  1_AnonymousLambda
//
//  Created by Sathya Babu on 12/07/23.
//

// auto sum = [] (int a, int b) { return a + b; };
constexpr auto sum = [](const auto &a, const auto &b) { return a + b; };

constexpr int answer = sum(10, 10);

///////////////////////////////

#include<iostream>
using namespace std;

class Anonymous
{
    public :
    
    template <class T1, class T2>
    constexpr auto operator()(T1 a, T2 b)
        {
        return a + b;
        }
};


int main()
{
     Anonymous an;
     auto res =  an(10,20);
    
    cout << " res : "<< res << endl;
    cout<<"Sum of two integers VIA lambda :"<< sum(5, 6) << endl;
   
  return 0;

}
