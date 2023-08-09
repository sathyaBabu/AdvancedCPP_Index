//
//  main.cpp
//  31_SI_VectorFunCompositon
//
//  Created by Sathya Babu on 31/07/23.
//

#include <iostream>
#include <vector>
#include<ranges>
using namespace std;


void join_vectors(){
    
    std::vector< std::vector< int > > outer { {1,2}, {3,4},{5,6}};
    
    auto joined = outer | std::views::join ;
    cout << " Join " << endl ;
    
    for( int m : joined)
    {
        cout << m << ' ';
    }
    cout << endl ;
    // 1 2 3 4 5 6
    
   // O( n*2)
    
    for( const auto& inner : outer){
        cout << " [ " ;
        for( const auto& val : inner)
        {
            cout << val << ' ' ;
        }
        cout << "  ] " << endl  ;
    }
    
    
    
}
int is_even( int n ){ return n % 2 == 0 ; }
void   reverse(){
    
    // A Bad way
    
    const std::vector numbers = { 1,2,3,4,5,6,7,8,9,10};
    
    std::vector<int> temp ;
    
    std::copy_if( begin( numbers ), end( numbers), std::back_inserter( temp ),is_even );
    
    // drop the first number // 2 even number
    std::vector<int> temp2( begin (temp ) + 1 , end( temp) );  // drop the first number 2
    
    // lets reverse the data
                           
    cout << "\n   A Bad way " << endl ;
    for( auto iter = rbegin( temp2 ); iter != rend( temp2 ); ++iter )
    {
        cout << *iter << ' ' ;
    }
  
    
    // Better way
    cout << "\n   A Better  way " << endl ;
    
    // std::views will not hold on to any references....
    // int temp while we at swap..( a, b )
    // raw variables in which compiler will not allocate memory to it..
    // void*
    
    auto rv = std::views::reverse( std::views::drop(std::views::filter( numbers,is_even), 1 ));
    
    // compose( reverse,( drop,1 ), filter );
    
    for( auto& i : rv  )
    {
        cout << i << ' ';
    }
    // 10 8 6 4
    
    // prefered way of coding...
    namespace rv2= std::ranges::views ;
    
    std::vector< int > n { 1,1,2,3,5,8,13,21,34,55,89};
    
    // create a functional pipeline to transform a vector of integers
    
    auto v = n | rv2::filter( is_even )
               | rv2::reverse
               | rv2::take( 2 ) ; // drop 1
    
    
    cout << "\n   A Prefered  way " << endl ;
    for( auto& i : v  )
    {
        cout << i << ' ';
    }
    // 34 8
    
    
    const std::vector numbers2 = { 1,2,3,4,5};
    cout << "\n  take( 3 )  from numbers2 vector " << endl ;
    for( int x : numbers2 | std::views::take( 3 ) )
    {
        cout << x << ' ';
    }
    // 1 2 3
    
    
    
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << " Vectror functional composition..!\n";
    //reverse();
    join_vectors();
    
    return 0;
}
/*
 Vectror functional composition..!

   A Bad way
10 8 6 4
   A Better  way
10 8 6 4
   A Prefered  way
34 8 Program ended with exit code: 0
 
 // join_vectors()
 
 Vectror functional composition..!
 Join
1 2 3 4 5 6
 [ 1 2   ]
 [ 3 4   ]
 [ 5 6   ]
Program ended with exit code: 0
 */
