//
//  main.cpp
//  LambdaClassFun_2
//
//  Created by Sathya Babu on 10/10/21.
//

#include <iostream>
using namespace std;

class Foo
{
public:
    Foo () : _x( 007 ) {}
    void func ()
    {
        // a very silly, but illustrative way of printing out the value of _x
        [this] () { cout <<  _x << " James Bond... .. .  "<<endl ; } ();
    }

private:
        int _x;
};

int main()
{
    Foo f;
    f.func();
}
