//
//  main.cpp
//  ptr_SharedPtr
//
//  Created by Sathya Babu on 10/10/21.
//
// C++ program to demonstrate shared_ptr
#include <iostream>
#include <memory>
using namespace std;
  
class A {
public:
    void show()
    {
        cout << "A::show()" << endl;
    }
};
  
int main()
{
    shared_ptr<A> p1(new A);
    cout << p1.get() << endl;
    p1->show();
    shared_ptr<A> p2(p1);
    p2->show();
    cout << " p2 : Address   " << p1.get() << endl;
    cout <<  " p2 : Address  " << p2.get() << endl;
  
    // Returns the number of shared_ptr objects
    // referring to the same managed object.
    cout << " p1 : Returns the number of shared_ptr objects "<< p1.use_count() << endl;
    cout << " p2 : Returns the number of shared_ptr objects "<<p2.use_count() << endl;
  
    //   of p1 on the object
    // and pointer becomes NULL
    p1.reset();
    cout << " p1 : AfterRelinquishes ownership "<< p1.get() << endl;
    cout << " p2 : Display count  "<< p2.use_count() << endl;
    cout << " p2 : Address   "<< p2.get() << endl;
  
    return 0;
}
/*
 Output :
 0x1005c3d10
 A::show()
 A::show()
  p2 : Address   0x1005c3d10
  p2 : Address  0x1005c3d10
  p1 : Returns the number of shared_ptr objects 2
  p2 : Returns the number of shared_ptr objects 2
  p1 : AfterRelinquishes ownership 0x0
  p2 : Display count  1
  p2 : Address   0x1005c3d10
 Program ended with exit code: 0
 */
