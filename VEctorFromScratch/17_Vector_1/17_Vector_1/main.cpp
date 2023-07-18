//
//  main.cpp
//  17_Vector_1
//
//  Created by Sathya Babu on 13/09/22.
//
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> num {1, 2, 3, 4, 5};

  cout << "Initial Vector: ";

  for (const int& i : num) {
    cout << i << "  ";
  }
  
  // add the integers 6 and 7 to the vector
  num.push_back(6);
  num.push_back(7);

  cout << "\nUpdated Vector: ";

  for (const int& i : num) {
    cout << i << "  ";
  }
    
    // accessing elements via index
    
    cout << "Element at Index 0: " << num.at(0) << endl;
    cout << "Element at Index 2: " << num.at(2) << endl;
    cout << "Element at Index 4: " << num.at(4);
    
    
    // change elements at indexes 1 and 4
     num.at(1) = 9;
     num.at(4) = 7;

     cout << "\nUpdated Vector: ";

     for (const int& i : num) {
       cout << i << "  ";
     }
    
    
    // remove the last element
      num.pop_back();

      // final vector
      cout << "\nUpdated Vector: ";
      for (int i : num) {
        cout << i << " ";
      }
      
    // declare iterator
     vector<int>::iterator iter;

     // use iterator with for loop
     for (iter = num.begin(); iter != num.end(); ++iter) {
       cout << " via iterator " << *iter << "  " ;
     }

  

  return 0;
}
