//
//  main.cpp
//  17_CoVariant_3
//
//  Created by Sathya Babu on 31/10/22.
//
// 2. Covariant result version of the base example, static type checking.
// same but much in a simpler way always treat the following as a send example
// https://www.geeksforgeeks.org/advanced-c-virtual-constructor/

class Top
{
public:
    virtual Top* clone() const = 0;
    virtual ~Top() = default;       // Necessary for `delete` via Top*.
};

class D : public Top
{
public:
    /* ← Covariant return */
    D*  clone() const override
    { return new D( *this ); }
};

class DD : public D
{
private:
    int answer_ = 42;

public:
    int answer() const
    { return answer_;}
    /* ← Covariant return */
    DD* clone() const override
    { return new DD( *this ); }
    // we are passing the base class TOP this here that in turn will assert the current derived type MEANING the base class will call the right child for noew its DD clone
};

#include <iostream>
using namespace std;

int main()
{
    DD* p1 = new DD();
    DD* p2 = p1->clone();
    // Correct dynamic type DD for *p2 is guaranteed by the static type checking.

    cout << p2->answer() << endl;          // "42"
    delete p2;
    delete p1;
}
