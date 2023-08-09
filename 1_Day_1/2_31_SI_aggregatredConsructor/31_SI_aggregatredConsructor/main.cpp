//
//  main.cpp
//  31_SI_aggregatredConsructor
//
//  Created by Sathya Babu on 31/07/23.
//

#include <iostream>
using namespace std ;

struct Point{
    
    int x ;
    int y ;
    
    
};

struct Data_1 {
    
    // move constructor.. expressions... lValue , rValue
    std::string name ;
    
    // flyweight factory design pattern..  pool of objects..
    std::string_view names ;
    
    double age ;
};

struct PData :Data_1 {
    
    bool flag ;
    
    // Phase I
  //  PData( const std::string& s , double d ,bool b ) : Data_1{ s, d } , flag{ b }{}
    
    
    void print() const { cout << " Name " << name << " Pin  " << age << " Flag << " << flag << endl ; }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Point pt ;
    pt.x = 10 ;
    pt.y = 20 ;
    
    cout << " \n pt  Point : pt.x " << pt.x << " pt.y " << pt.y << endl ;
    
    
    // aggregatredConsructor
    Point p2{ 110 ,210 };
    cout << " \n p2  Point : pt.x " << pt.x << " pt.y " << pt.y << endl ;
    
    
    Point p{  .x = 100 , .y = 200  };
    cout << " \n p  Point : pt.x " << pt.x << " pt.y " << pt.y << endl ;
    
    
    // Phase I
//    PData pd( "Bangalore ", 560043 , true);
//    pd.print();
    
    
    // Phase II
    
    PData data_via_aggregate{"Vishal ",23.44,true};
    data_via_aggregate.print();
    //  Name Vishal  Pin  23.44 Flag << 1
    
    PData data_via_aggregate2{ { "Suman  ",93.44 },true};
    data_via_aggregate2.print();
    
    return 0;
}
/*
 Hello, World!
  
  pt  Point : pt.x 10 pt.y 20
  
  p2  Point : pt.x 10 pt.y 20
  
  p  Point : pt.x 10 pt.y 20
  Name Vishal  Pin  23.44 Flag << 1
  Name Suman   Pin  93.44 Flag << 1
 Program ended with exit code: 0
 */
