//
//  main.cpp
//  17_initializer_list_vector
//
//  Created by Sathya Babu on 19/02/23.
//

#include <iostream>
#include <vector>

class MyNumber
{
public:
    MyNumber(const std::initializer_list<int> &v) {
//        for (auto itm : v) {
//            mVec.push_back(itm);
//        }
        // or
        mVec.insert(mVec.end(), v.begin(), v.end());
    }
    MyNumber(int a, int b) {
        std::cout <<"\n  Normal constructor " << a << "  , "<< b << std::endl;
    }
    void print() {
    for (auto itm : mVec) {
        std::cout << itm << " ";
    }
    }
private:
    std::vector<int> mVec;
};

int main()
{
    MyNumber m { 1, 2, 3, 4 };
    MyNumber myNum(10,20);
    m.print();  // 1 2 3 4

    
    return 0;
}
// 1 2 3 4 Program ended with exit code: 0
