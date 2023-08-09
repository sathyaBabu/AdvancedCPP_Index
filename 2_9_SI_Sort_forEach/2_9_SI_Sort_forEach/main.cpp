//
//  main.cpp
//  2_9_SI_Sort_forEach
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
using  namespace std ;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    std::array< int, 10> s = { 5,7,4,2,8,1,9,0,3};
    auto print = [ &s ] ( std::string_view const rem ) {
        
        for( auto a : s ){
            cout << a << ' ';
        }
        cout << " : " << rem << endl ;
    };
    
    
    std::sort( s.begin() ,s.end() );
    print( "Sorted with the default operator < ");
   
    
    std::sort( s.begin() ,s.end() , std::greater<int> () );
    print( "Sorted with the std::greater api  ");
   
    struct {
        bool operator() ( int a, int b ) const { return a < b ; }
        
    } customLess ;
    
    
    std::sort( s.begin() ,s.end() , customLess );
    print( "Sorted with the customLess  function object ");
   
    
    
    std::sort( s.begin() ,s.end() ,  []( int a , int b ) { return a > b ; } );
    print( "Sorted with the Lambda expressions ");
   
   
    return 0;
}
/*
 Hello, World!
 0 0 1 2 3 4 5 7 8 9  : Sorted with the default operator <
 9 8 7 5 4 3 2 1 0 0  : Sorted with the std::greater api
 0 0 1 2 3 4 5 7 8 9  : Sorted with the customLess  function object
 9 8 7 5 4 3 2 1 0 0  : Sorted with the Lambda expressions
 Program ended with exit code: 0
 */
