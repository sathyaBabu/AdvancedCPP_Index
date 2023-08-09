//
//  main.cpp
//  31_SI_FunctionalComposition
//
//  Created by Sathya Babu on 31/07/23.
//

#include <iostream>
using namespace std ;

const std::string message = " I'm here ";

const std::string& foo() {
    return message ;
}

struct A { double x ; };
const A* a ;

decltype( a -> x ) y ;
decltype( a -> x ) z = y ;

// Phase II

//auto& increment( int& a ) { a++ ; return  a;}
decltype( auto ) increment( int& a ) { a++ ; return  a;}

// Phase III
//
//float  f( float x )
//{
//    return  x + 23.12 ;
//}

// R-LCDECL PASCAL call    C CAll L -> R
// Trailing return type

 constexpr auto  f( float x ) ->  float
{
     return  x + 23.12 ;
     
 }

auto getData() ->  int( & )[ 2 ]
{
    int arr[ ] = { 10,20};
    return  arr;
}

// Phase VI
// helper functions

constexpr auto  add( const int x ,const  int y ) -> int
{
    return  x + y ;
}
int mul( int x , int y )
{
    return  x * y ;
}


// get the hold on function pointers -> Legacy way

//int(*)(int,int);

int (  *myFNPTR )(int x ,int  y ) = add  ;



//  function pointers -> MC++ way

std::function< int(int, int )> func = add ;



// What is functional composition how that should look like..
// Lets createw one from the scratch..

// template for the functional composition

// 0 poaram or N =number of paramater
// template over loaDING CONCEPT( 98 ) ..   LEGACY WAY
// USE VARADIC TEMPLATE INSTEAD


int resultOfCalcvulation( int ( *OP )  (int,int),
                         int x , int y)
{
    
    // get a ASYNC thread here for the parllal execution
    
    return  ( *OP )( x, y );   // *OP is a call back function.. ported to lambda..
}

// SLIGHTLY A BETTER APPROACH
// std::ref();   vs  const FN&

// Boiler plate code... MC++ should have a way to it..

  template< typename FN ,typename  T1 , typename  T2 >
 // template< typename FN ,typename  T1 , typename  T2 ,typename  T3 ,typename  T4  >
   auto resultOfCalcvulation_2(
                               const FN& op ,
                               const T1& x ,
                               const T2 y
                               ) -> decltype( op( x,y ) )
  {
       return op( x , y );
   }



auto main(int argc, const char * argv[]) -> int
{
    // insert code here...
    std::cout << "Hello, World!\n";
    
    const  auto f1 = foo();
    
    decltype( foo() )  f2 = foo();
    
    decltype( auto )  f3 = foo();
    
    cout << f1 << endl ;
    cout << f2 << endl ;
    cout << f3 << endl ;
    
    // Phase II
    
    int x = 100 ;
    int& y = increment( x );
    
    cout << " x " << x << endl ;  // 101
    cout << " y " << y << endl ;   // 101
    
    
    // Phase III
    
    
    cout << " f() " << f( 12.10 ) << endl ;   //  35.22
    
    // Phase VI
    cout << " myFNPTR " << myFNPTR(1,2 ) << endl ;   //  myFNPTR 3
    
    cout << " std::function " << func(11,22 ) << endl ;   //   std::function 33
    
    cout << " functional composition 1.  " << resultOfCalcvulation( add, 100,200 ) << endl ;
    //  functional composition 1.  300
    
    
    cout << " functional composition 2.  " << resultOfCalcvulation( mul, 10,20 ) << endl ;
    //  functional composition 1.  200
    
    
    
    cout << " functional composition 3.  " << resultOfCalcvulation_2( add, 15.12,22.89 ) << endl ;
    //  functional composition 3.  37
    
    
    // MC++
    
    
    // std::bind
    
    // std::bind( &add(123,456 );
    
    using namespace std::placeholders ;
   std::function< int ( int )>  std_fun = std::bind( &add, 123, _1 );
    int summ = std_fun( 12 );
    
    cout << " functional composition 3.  " <<  summ  << endl ;
    
    
    return 0;
}
/*
 Hello, World!
  I'm here
  I'm here
  I'm here
  x 101
  y 101
  f() 35.22
  myFNPTR 3
  std::function 33
  functional composition 1.  300
  functional composition 2.  200
  functional composition 3.  37
  functional composition 3.  135
 Program ended with exit code: 0
 */
