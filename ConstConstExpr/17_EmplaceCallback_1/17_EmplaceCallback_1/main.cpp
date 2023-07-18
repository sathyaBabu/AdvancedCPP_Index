//
//  main.cpp
//  17_EmplaceCallback_1
//
//  Created by Sathya Babu on 20/06/22.
//
// C++ program to demonstrate the
// push_back() method
//  https://www.geeksforgeeks.org/push_back-vs-emplace_back-in-cpp-stl-vectors/

#include <iostream>
#include <vector>

using namespace std;

// Class
class MyVector {

public:
    int x;

    // Parameterized Constructor
    MyVector(int x)
        : x(x)
    {
        cout << "Constructor => "
            << "x:" << x << endl;
    }

    // Copy Constructor
    MyVector(const MyVector& MyVector)
        : x(MyVector.x)
    {
        cout << "Copied => "
            << "x:" << x << endl;
    }

    ~MyVector()
    {
        cout << "destructor=>"
            << "x:" << x << endl;
    }
};

// Driver Code
int main()
{
    // Vector of object of MyVector class
    // is created
    vector<MyVector> myvector;
    
    // Phase II
    
   // vector<int> myvector;
    cout << "length of myvector: " << myvector.size()
        << endl;

    // Inserting elements in the object
    // created using push_back() method
    cout << endl;
//   myvector.reserve(3);
//    // Custom input entries
//    myvector.push_back(MyVector(1));
//    cout << " ...."<< endl;
//
//    myvector.push_back(MyVector(11));
//    cout << " ...."<< endl;
//
//    myvector.push_back(MyVector(21));
//    cout << " ...."<< endl;
/*
 
 v.reserve(3)
 length of myvector: 0

 Constructor => x:11
  ....
 Constructor => x:22
  ....
 Constructor => x:33

 3destructor=>x:33
 destructor=>x:22
 destructor=>x:11
 Program ended with exit code: 0
 
 
 emplace_back without reverse
 
 
 //////////////////
 /////////
 Constructor => x:1
 Copied => x:1
 destructor=>x:1
  ....
 Constructor => x:11
 Copied => x:11
 Copied => x:1
 destructor=>x:1
 destructor=>x:11
  ....
 Constructor => x:21
 Copied => x:21
 Copied => x:11
 Copied => x:1
 destructor=>x:11
 destructor=>x:1
 destructor=>x:21
  ....
 */
    
    //  // Phase II
    //  myvector.reserve(3);
    myvector.emplace_back(11);
    cout << " ...."<< endl;

    myvector.emplace_back(22);
    cout << " ...."<< endl;
//
    myvector.emplace_back(33);
    cout << endl << myvector.size();

    return 0;
}
/*
 myvector:0

 Constructor=>x:1
 Copied=>x:1
 destructor=>x:1

 Constructor=>x:11
 Copied=>x:11
 Copied=>x:1
 destructor=>x:1
 destructor=>x:11

 Constructor=>x:21
 Copied=>x:21
 Copied=>x:11
 Copied=>x:1
 destructor=>x:11
 destructor=>x:1
 destructor=>x:21

 destructor=>x:21
 destructor=>x:11
 destructor=>x:1
 Program ended with exit code: 0
 
 // emplace
 
 length of myvector: 0

 Constructor => x:11
  ....
 Constructor => x:22
 Copied => x:11
 destructor=>x:11
  ....
 Constructor => x:33
 Copied => x:22
 Copied => x:11
 destructor=>x:22
 destructor=>x:11

 3destructor=>x:33
 destructor=>x:22
 destructor=>x:11
 Program ended with exit code: 0
 
 
 --------  >  emplace with  myvector.reserve(3);
 
 length of myvector:0

 Constructor=>x:11

 Constructor=>x:22

 Constructor=>x:33

 3destructor=>x:33
 destructor=>x:22
 destructor=>x:11
 Program ended with exit code:
 */
