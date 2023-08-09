//
//  main.cpp
//  31_SI_BasicsCostConstexpr
//
//  Created by Sathya Babu on 31/07/23.
//
/*
 
 
    Grady booch..
    GOF DP..  1993 - 1996..
    S O L I D   - clean code..
 
    MC++ 98 / c++11 // 13 17  20 23
 
    
    Object O P s
 
    functional programming.. / parallel programming  ::seq  :: par
    threads... Async threads..
    
    easy on .. testing...
 
    Observer DP.. how to bring in functional programming / lambdas..
 
 
    if
    for -> range , for_each..
    new delete..    unique_ptr shared_ptr  weak_ptr
    Array  use Vector( Algo.. O(n) - O(1) )  Bubble sort O( n*2 ) nested for
    Constructor - initilizer list , agregation extension..
    INheritance..  factory - CRTP - covariants..
    return statements
    NULL vs nullptr_t / nullptr
 
    const and constexpr...
 
    threads...   Coroutines.. C++20
 
 */

#include <iostream>
#include<vector>
using namespace std;


void myConst()
{
    
    
    int var  ;
    const int max = 5 ;
    
    const  int sum = 10 + 20 + 30 ;  // 60
    //  .ro
    
   
    
    cout << " Sum = " << sum ;
    
    for( int i = 0 ; i <= max ; i++ ){
        
        var += i ;
      }
    
    // unfolding for loops...
          
    var += 1;
    var += 2;
    var += 3;
    var += 4;
    var += 5;
    
//
//    // rem dead code..
//    const int i = 0 ;
//    if( !i )
//    {
//        // false
//
//    }
//    else{
//        // true..
//    }
//
    
    
    
    //
    
}

const int ii = 100 ;
int arr[ ii ];


template<typename  T1, typename  T2>
constexpr auto func_constexpr( T1 x , T2 y ){
    
    return  x + y ;
}

int array[ func_constexpr(10, 20 ) ];
//int array2[ func_constexpr(10, rand() ) ];


class Test3
{
    
    public :
    int value ;
    
    constexpr int getValue() const
    {
        return  value ;
        
    }
   constexpr Test3( int value ) : value( value ) {}
    
};


constexpr Test3 x( 100 );
int array4[ x.getValue() ];


//std::ref

template< typename  T >
auto printTypeInfo( const T& t  ){
    
    if constexpr ( std::is_integral< T >::value){
        cout << " Is an Integral value " << endl ;
        return  t + 1 ;
    }else{
        cout << " Is not an  Integral  " << endl ;
        return  t + 1.12 ;
        // 'auto' in return type deduced as 'double' here but deduced as 'int' in earlier return statement
    }
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    // Phase I const
  //  myConst();
    
    // Phase II constexpr
    
    
    const     double PI1 = 3.141592653589793;
    
    constexpr double PI2 = 3.141592653589793;
    
   // constexpr double PI3 = PI1 ;
    
    constexpr double PI3 = PI2 ;
    
    cout << " Int sum : " << printTypeInfo( 10 ) << endl ;
    cout << " Double sum : " << printTypeInfo( 20.123 ) << endl ;
    
    
    // Phase III
    
    const int store{ 10 };
//    int store2{ 10,20,30,40,50};  // not right..
    
    // vector is a const by itself..
    const int a = std::vector< int >{ 1,2,3 }.size();  //  initilizer list or range expr..
    
    constexpr int b = std::vector< int >{ 1,2,3 }.size();  //  initilizer list or range expr..
    // expression must have a constant value
    
    cout << a << endl ;
    cout << a << endl ;
    
    // class MyVector  O(n ) or O( 1 )
    // Algo...
    // huge data.. Search fwd() rev() bidirectional().. tree().. linkList
    // iterator.. DP..
    
    std::vector<int> v { 1,2,3,4,5 };
    
    v.push_back(  230 );
    v.emplace_back( 456 );
    
    
    cout <<" Display the vector contents " << endl ;
    for( int i = 0 ; i< v.size() ; i++){
        cout << v[ i ] << " ";
    }
    
    
    cout <<" Display the vector contents using iterator" << endl ;
    for(  std::vector< int > :: iterator i = v.begin(); i != v.end() ; ++i){
        cout <<  *i << " ";
    }
    

    
    cout <<" Display the vector contents  via range for loop" << endl ;
    
    for( int x : v ){
        cout <<  x << " ";
    }
    
   // const int *ii = 10 ;  // address or the content
    
    
    cout <<" \n Change and Display the vector contents " << endl ;
    
    for( int &x : v ){
        x += 10 ;
        cout <<  x << " ";
    }
    
    
    cout <<" \n  Display the vector contents.....  " << endl ;
    
    for( int x : v ){
      cout <<  x << " ";
    }
    
//    //int *p = 20 ;
//   const   int  *address ;
//
    
    cout << " Element at index 0 " << v.at(0) << endl ;
    cout << " Element at index 2 " << v.at(2) << endl ;
    cout << " Element at index 4 " << v.at(4) << endl ;
    
    v.at(0) = 987 ;
    v.at(4) = 1234 ;
    
    cout <<" \n  Display the vector contents.....  " << endl ;
    for( int x : v ){
      cout <<  x << " ";
    
    }
    cout <<" \n  Range for loop for FUN....  " << endl ;
    
    for( auto varr : {100,200,300,400,500 } ){  //  initilizer list
        cout <<  varr << " ";
    }
    
    return 0;
}
/*
 
 Hello, World!
  Int sum :  Is an Integral value
 11
  Double sum :  Is not an  Integral
 21.243
 3
 3
  Display the vector contents
 1 2 3 4 5 230 456  Display the vector contents using iterator
 1 2 3 4 5 230 456  Display the vector contents  via range for loop
 1 2 3 4 5 230 456
  Change and Display the vector contents
 11 12 13 14 15 240 466
   Display the vector contents.....
 11 12 13 14 15 240 466  Element at index 0 11
  Element at index 2 13
  Element at index 4 15
  
   Display the vector contents.....
 987 12 13 14 1234 240 466
   Range for loop for FUN....
 100 200 300 400 500 Program ended with exit code: 0
 
 */
