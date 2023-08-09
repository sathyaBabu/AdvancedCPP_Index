//
//  main.cpp
//  2_1_SI_Expression
//
//  Created by Sathya Babu on 01/08/23.
//

#include <iostream>
using namespace std;

int foo() { return 10 ; }

class Widget
{
    public :
    
    void doWork() &
    {
        cout << "working on lValue " << endl ;
    }
    void doWork() &&
    {
        cout << "working on rValue " << endl ;
    }
    
};

class Widget_vec {
    
    public :
    using DataType = std::vector< double >;
    
    Widget_vec(){
        values =  { 1.10,2.20,3.30,4.40,5.50};
    }
    
    DataType& data() &
    {
        return  values;
    }
    
    DataType data() &&
    {
        return std::move( values );
    }
    private :
    
    DataType values ;
    
};


void setValue( int val ) {}
void setValue( const int& val ) {}  // not right but it can hold lValue rValue
void setValue( int& val ) {}  // lVal
void setValue( int&& val ) {}  // rVal


// ASYNC thread..
std::string makeCat() {
    // run  blocking thread
    // Ok let me think of Async thread..
//
//    for(int i =0 ; i <= 30000; i++ ){
//        for(int ii =0 ; ii <= 30000; ii++ ){
//    }
    return  " Percian Cat. ";
        // we are not using asy.wait();
}

//*****************************************

class MyVector {
    public :
    // constructor
    MyVector(  int i ) : size( i )
    {
        cout << " --> Landed in regular constructor... " << endl ;
        elements = new int[ i ];
        
        for( int j = 0 ; j < i ; j++){
            elements[ j ] = j ;
        }
        
        
    }
    MyVector( MyVector&& rValOther, int dummy=0 ) : size( rValOther.size )
    {
        
        cout << " --> Landed in Move Constructor... " << endl ;
        std::swap( elements,rValOther.elements);
        std::swap( size,rValOther.size);
        
    }
    
    ~MyVector() {
        cout << " --> Landed in Destructor ... " << endl ;
        delete [] elements ;
    }
    
    // copy constructor -> Good Bye...
    MyVector( const MyVector& other  ) : size( other.size )
    {
        cout << " --> Landed in copy constructor. ... " << endl ;
        
        elements = new int[ other.size];
        
        for( int i = 0 ; i < other.size ; ++i){
            elements[ i ] = other.elements[ i  ];
        }
    }
    
    // Move or tValue constructor
    
    MyVector( MyVector&& other ) : size( 0 ) , elements( nullptr )
    {
        
        cout << " **** --> Landed in rValue  constructor. ... ***" << endl ;
        
        // Phase I
//
                elements = other.elements ;
                size     = other.size ;

                // lets clean up the other

                other.elements = nullptr ;
                other.size     = 0 ;
        
        // Phase II
       // swap( other );
        
        
    }
    void swap( MyVector& other){
        
        
        std::swap( elements,other.elements);
        std::swap( size,other.size);
        
    }
    int getSize() { return  size ;}
    
    int& operator [] ( int index )
    {
        cout << " --> operator[]( int index )[] " ;
        return  elements[ index ];
    }
    
    
    
    
    public :
    
    int* elements ;
    int size ;
};

int* begin( MyVector& v ){
    cout << " begin() " << endl;
    return  v.elements;
}

int* end( MyVector& v ){
    cout << " end() " << endl;
    return  v.getSize() != 0 ? &v[ 0 ] + v.getSize() : nullptr ;
}


//*****************************************


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    typedef float f ;
    f ff= 12.22 ;
    
    using flt = float ;
    flt f1 = 12.22 ;
    
    
    
    int i = foo() ;
    
    
//    NULL   ( void* ) 0   ; Non litrel type
    
   // NULL i = 0 ;
//    nullptr_t
    
//    nullptr ptr ;
    
    int *arr ; int *p ; int x ; int y ;
    
    // lValue
    
    x ;
    *p ;
    arr[ 0 ] ;
    
    
    // rValue
    
    12 ;
    
    x  + y ;
    
    foo();
    
    // lValue can take only lValues...
    
    int&  lValue = x ;
   // int&  lValue = 90 ; // error
    
    
    // DO NOT CODE this way..
    const int& l_r_Value = 23 ;  // meaning less code..
    
    // rValue
    
    int&& rValue = 80 ;
    
    Widget wedget1 ;
    wedget1.doWork();  // lValue function
    Widget().doWork(); // rValue
    
    
    std::string s( "Cat");  // Constructor.. vs       MOveConstructor rValue
    std::string s2( s ) ;   // copy constructor.. vs  MOveConstructor
    
    
//    auto aa = makeCat();
//   // asy.wait();
    
   
    
    std::string s3( std::move( makeCat() ) ); // rValue
                                              // he an insane guy : std::move
                                              // he converts all given value to rValue
    
    
    
    cout << " s3 " << s3 << endl ;  //  s3  Percian Cat.
    
    MyVector v1( 10 );
    MyVector v2( v1 );  // copy const gets called
    
  //  MyVector v3( static_cast< MyVector&&>( v1 ) );  // rValue
                                                    // Move constructor gets called
    
   // MyVector v4( std::move( v2 ) );  // Move constructor gets called
    
    MyVector&& rValueVector = { 3 , 0  } ;  //BY  NAVEENA..
    MyVector v5(  rValueVector ) ;   // Move constructor gets called
    
    // Phase III
    
    Widget_vec  widget ;
    
    cout << " get the data for lValue object ";
    for( const auto& value : widget.data())
    {
        cout << value << " " ;
        
    }
    cout << " get the data for rValue object ";
    for( const auto& value : Widget_vec().data())
    {
        cout << value << " " ;
        
    }
    
    
    cout << " get the data from Myector ";
    MyVector v( 10 );
    
    for( const auto& x : v )
    {
        cout << x << " ";
    }
    
    return 0;
}
