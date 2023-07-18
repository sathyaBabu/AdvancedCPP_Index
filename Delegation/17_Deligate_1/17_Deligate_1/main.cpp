//
//  main.cpp
//  17_Deligate_1
//
//  Created by Sathya Babu on 10/10/22.
//
/*
 A delegate is a class that wraps a pointer or reference to an object instance, a member method of that object's class to be called on that object instance, and provides a method to trigger that call.
 */

#include <iostream>
template <class T>
class CCallback
{
public:
    typedef void (T::*fn)( int anArg );

    CCallback(T& trg, fn op)
        : m_rTarget(trg)
        , m_Operation(op)
    {
    }

    void Execute( int in )
    {
        (m_rTarget.*m_Operation)( in );
    }

private:

    CCallback();
    CCallback( const CCallback& );

    T& m_rTarget;
    fn m_Operation;

};
// not a good presentation
// lets use A on class B C d and deligate
class A
{
public:
    virtual void Fn( int i )
    {
        std::cout << "Hello from A::Fn " << i << std::endl;
    }
};


int main(  )
{
    A a;
    CCallback<A> cbk( a, &A::Fn );
    cbk.Execute( 3 );
    return 0 ;
}
