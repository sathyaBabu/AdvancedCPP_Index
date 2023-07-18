//
//  main.cpp
//  Vector_find
//
//  Created by Sathya Babu on 27/10/21.
//
//
//  main.cpp
//  Sort
//
//  Created by Sathya Babu on 27/10/21.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;


int main()
{
    // Warning this type of initialization requires a C++11 Compiler
    vector<int> intVec = {56, 32, 993, 23, 12, 93, 132, 77, 754};
    
    std::vector<int>::iterator it = std::find(intVec.begin(),intVec.end(),77);
    
    if( it == intVec.end()){
        cout << " Not found " << endl;
    } else {
                 // Get index from iterator, by calculating its
                // distance from start of vector
                int index =  std::distance(intVec.begin(), it);
                std::cout<<"Found at Index Position is : " << index <<std::endl;
          
        cout << "Found " << " " << endl;
    }
    return 0;
}
