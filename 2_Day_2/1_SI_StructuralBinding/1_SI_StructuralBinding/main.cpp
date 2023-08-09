//
//  main.cpp
//  1_SI_StructuralBinding
//
//  Created by Sathya Babu on 01/08/23.
//
/*
 
     structural binding..
 
     Copy constructors -> Good bye
 
     Expressions lValue rValue prValue xValue gValue..
     Perfect forwarding( std::move )
     std::decay
 
     Covered...Functional composition RAW..
     varadic templates
     Fold
     USE CASE :   calc -> POSIX notation   / JSON
     interpreter DP
 
     Good bye to new delete int& ref ;   std::ref( value )
     unique_ptr shared_ptr weak_ptr
 
     Singleton legacy way
     Singleton shared ptr
     Singleton once flag  ( Lazy )
 
     Singleton scot mayer's way
 
 
     any , tuple , optional  ranges( variant with visit -> used in our lambda app's )
 
     
 */

#include <iostream>
#include<map>
using namespace std ;

struct MyStruct
{
    int i = 0 ;
    std::string s ;
    
    
};
MyStruct getStruct(){
    return  MyStruct{ 43," Hello "};
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    cout << " Legacy way of displaying the data " << getStruct().i << endl ;
    cout << " Legacy way of displaying the data " << getStruct().s << endl ;
    
    auto [ id, val  ] = getStruct();
    id += 10 ;
    
    
    cout << " displaying the data " << id << endl ;
    cout << " displaying the data " << val  << endl ;
    
    std::map<int, std::string> myMap ;
    myMap.insert( {1,"One "});
    myMap.insert( {2,"Two  "});
    myMap.insert( {3,"THree  "});
    
    
    for( const auto& pair : myMap)
    {
        int key = pair.first ;
        std::string value = pair.second ;
        cout << " key  " << key << " Value " << value  << endl ;
    }
    
    
    cout << " A better way.. " << val  << endl ;
    
    for( const auto& [ key, value ] : myMap)
    {
       
        cout << " key  " << key << " Value " << value  << endl ;
    }
    
    
    return 0;
}
/*
 
 Hello, World!
  Legacy way of displaying the data 43
  Legacy way of displaying the data  Hello
  displaying the data 53
  displaying the data  Hello
  key  1 Value One
  key  2 Value Two
  key  3 Value THree
  A better way..  Hello
  key  1 Value One
  key  2 Value Two
  key  3 Value THree
 Program ended with exit code: 0
 */
