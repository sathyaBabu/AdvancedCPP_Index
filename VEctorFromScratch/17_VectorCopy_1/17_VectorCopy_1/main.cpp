//
//  main.cpp
//  17_VectorCopy_1
//
//  Created by Sathya Babu on 19/03/23.
//

#include<algorithm> // for copy
#include<vector>
#include<iostream>

using namespace std;

int main()
{
              std::vector<int> input{ 10, 20, 30 ,40,50};
              std::vector<int> output;
            //  output.resize(input.size());

//              std::copy(input.begin(),input.end(), back_inserter(output) ) ;
    std::copy(input.begin(),input.end(), back_inserter(output) ) ;
              // Now output has a complete copy of input.

    // for( int i = 0 ; i < output.size();i++){
    //           cout << output[i] << ", ";
    //}
                for(auto i: output) {
                      cout << i << ", ";
                   }
              assert(input == output);
//
       
}
// 10, 20, 30, 40, 50, Program ended with exit code: 0
