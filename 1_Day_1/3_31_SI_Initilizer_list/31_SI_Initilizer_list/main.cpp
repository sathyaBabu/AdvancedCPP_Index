//
//  main.cpp
//  31_SI_Initilizer_list
//
//  Created by Sathya Babu on 31/07/23.
//  https://en.cppreference.com/w/cpp/utility/initializer_list

// under git branch production

// touched on 4th Aug 12:50

/*
 
 
 git branch
 Sathyas-MBP-2:1_A_AdvancedCPP_Index malsneha$ git branch production
 Sathyas-MBP-2:1_A_AdvancedCPP_Index malsneha$ git branch
 * (HEAD detached from b5f1f53)
   main
   production

 git checkout production

 M    1_Day_1/1_31_SI_BasicsCostConstexpr/31_SI_BasicsCostConstexpr.xcodeproj/project.xcworkspace/xcuserdata/malsneha.xcuserdatad/UserInterfaceState.xcuserstate
 M    1_Day_1/2_31_SI_aggregatredConsructor/31_SI_aggregatredConsructor.xcodeproj/project.xcworkspace/xcuserdata/malsneha.xcuserdatad/UserInterfaceState.xcuserstate
 M    1_Day_1/3_31_SI_Initilizer_list/31_SI_Initilizer_list.xcodeproj/project.xcworkspace/xcuserdata/malsneha.xcuserdatad/UserInterfaceState.xcuserstate
 M    ConstConstExpr/17_IfConstExpr
 M    ConstConstExpr/17_nullptrVS_NULL

 git checkout -b sathya/initilizerToWork
 Switched to a new branch 'sathya/initilizerToWork'

 
 */

#include <iostream>
#include<vector>
using namespace std ;

class MyNumber{
    
    public :
    
    MyNumber( const std::initializer_list< int > &v ){
        
        myVec.insert( myVec.end(),v.begin(), v.end() );
    }
    
    MyNumber( int a , int b ){
        cout << " Normal constructor " << a << " " << b << endl ;
        
    }
//    MyNumber( int a , int b , int c ){
//        cout << " Normal constructor " << a << " " << b   << " " << c << endl ;
//
//    }
    void print(){
        for(auto itm :  myVec){
            cout << itm << " " ;
            
        }
    }
    
    private :
    
    std::vector< int > myVec ;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
//   depricated way of coding..
    
    
//    MyNumber myNum(10,20);
//    myNum.print();
    
    
    // var number of arguments..
    MyNumber myInit_list_Num{12,13,14,15,16,16,17,18,19,20,21 };
    myInit_list_Num.print();
    
    return 0;
}
/*
 
 Hello, World!
 12 13 14 15 16 16 17 18 19 20 21 Program ended with exit code: 0
 
 */
