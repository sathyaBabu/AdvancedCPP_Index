//
//  main.cpp
//  2_22_tuple
//
//  Created by Sathya Babu on 02/08/23.
//


#include <iostream>
#include <functional>
#include <vector>
#include <tuple>
using namespace std;

tuple<int, string,double> f()
{
    int i{ 109 };
    std::string s{"Some data"};
    double d{ 23.33};
    
    return  { i, s, d };
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Tuple!\n";
    
    auto[ x, y  ,z ] = f();
    
    cout << x << ' ' << y << ' ' << z << endl ;
    
    typedef tuple< int, char ,float > tp ;
    
    tp t1( 100,'A', 100.111) ;
    tp t2( 200,'B', 200.111) ;
    tp t3 = make_tuple( 300,'C', 300.111) ;
    
    
    cout << " tuple size " << tuple_size< tp >::value << endl ;
    
    
    
    cout << get<0>( t2 ) << endl ;
    cout << get<1>( t2 ) << endl ;
    cout << get<2>( t2 ) << endl ;
    
    int i = get<0>( t3 );
    cout << " Data 0 from t3 " << i << endl ;
    
    int first ;
    char second ;
    float third ;
    
    tie( first, second, third ) = t2 ;
    cout << " Displaying 2nd set t2 " << first << endl ;
    cout << " Displaying 2nd set t2" << second << endl ;
    cout << " Displaying 2nd set t2 " << third  << endl ;
    
    auto [ aa ,bb , cc ] = t3 ;
    cout << " Displaying 2nd set t3 " << aa << endl ;
    cout << " Displaying 2nd set t3 " << bb << endl ;
    cout << " Displaying 2nd set t3 " << cc  << endl ;
    
    
    
    typedef tuple< int, std::function< int(int) > > tp_fun;
    tp_fun tfun( 101, []( int val ) -> int {cout << " Lambda called "  << val <<  endl ; return 0 ; });
    
    get< 1 >( tfun )(107);
    
    
    return 0;
}
/*
 Tuple!
 109 Some data 23.33
  tuple size 3
 200
 B
 200.111
  Data 0 from t3 300
  Displaying 2nd set t2 200
  Displaying 2nd set t2B
  Displaying 2nd set t2 200.111
  Displaying 2nd set t3 300
  Displaying 2nd set t3 C
  Displaying 2nd set t3 300.111
  Lambda called 107
 
 */
