//
//  main.cpp
//  24_Expressions_lValue_rValue
//
//  Created by Sathya Babu on 24/04/23.
//


#include <iostream>
#include<string>
#include <vector>
#include <map>
#include <utility>
#include <memory>

#include <ranges>

using namespace std;

int foo() { return  10 ;}

int& getValue() {
    static int value = 123 ;
    return value ;
}




class Widget{
public:
    // change doWork() to doWork1() and check
    void doWork1() & {
        std::cout << "Doing work on lvalue object" << std::endl;
    }
    
    void doWork() && {
        std::cout << "Doing work on rvalue object" << std::endl;
    }
};


// Phase II  Widget_vec
class Widget_vec   {
public:
    using DataType = std::vector<double>;

    // Constructor
    Widget_vec() {
        values = {1.10, 2.20, 3.30, 4.40};
    }

    // lvalue reference qualifier
    DataType& data() & {
        return values;
    }

    // rvalue reference qualifier
    DataType data() && {
        return std::move(values);
    }

private:
    DataType values;
};


void setValue(  int val ){}
void setValue(  const int& val ){}  //  lvalue / rvalue
void setValue(  int& val ){}  //  lvalue
void setValue(  int&& val ){}  //   rvalue
    
std::string makeCat() { return "Percian Cat "; }

// initilizer list -> uniform initilize
//int i = 10 ;
//int ii{10};
//A(1,2)
//B{1,2,3,4,5,67,.....}

// range based for loop AT THE END...

//****************

auto range(int start, int end) {
    return std::views::iota(start, end);

}
//****************

class MyVector{
    
    public :
              // Constructor
        MyVector( int i ) : size( i ) {
            std::cout << " -> Landed in regular constructor ...." << std::endl ;
            elements = new int[ i ] ;
            
            for( int j = 0 ; j < i ; j++){
                elements[ j ] = j ;
            }
       
        }
    
    ~MyVector() {
        std::cout << " -> Landed destructor ...." << std::endl ;
                delete [] elements ;
    }
    // lValue constructor  Copy constructor
    MyVector( const MyVector& other ) : size( other.size)
    {
                std::cout << " -> Landed in copy  constructor ...." << std::endl ;
                elements = new int[ other.size] ;

                for( int i = 0 ; i <= other.size ; ++i){
                    elements[ i ] = other.elements[ i ];
                }
    }
    
   
    // rValue constructor
    MyVector( MyVector&& other) : size(0) , elements( nullptr )
    {
        std::cout << " -> Landed in *** rValue constructor ....  *** " << std::endl ;
        
        // Phase I
//        elements = other.elements ;
//        size =      other.size ;
//
//        // cleaning up job
//
//        other.elements = nullptr ;
//        other.size     = 0 ;
        
        
//   Phase II
        // Lets swap instead..
        swap( other );
        
        
    }
    
    void swap( MyVector& other){
        
        
                               //                MyVector temp( other );
                                //                other = *this ;
                                //                *this = temp ;
        
        //          nullptr is replaced withwith data
        std::swap( elements,other.elements);
        std::swap( size,other.size);
        //          0 is replaced with size
    }
    
    int getSize() { return size ;}
    
    int& operator [] ( int index ){
        cout << " ---> operator[](int index ) [] " ;
                return  elements[ index ];
    }
    
    
    
    
    public :
        
        int *elements ;
         int size ;
    
    
};

// this is a part of the iterator
int* begin( MyVector& v ){
    cout << " begin() " << endl;
    // return v.getSize()!=0 ? &v[ 0] : nullptr;
    return v.elements ;
}

int* end( MyVector& v ){
    cout << " end() " << endl;
     return v.getSize()!=0 ? &v[ 0] + v.getSize() : nullptr;
    
   // return v.elements + v.size ;
}



void printFunc (int x) {
                std:: cout << " from printFunc for_each  : "<< x << std:: endl;
            }



// *****************       Phase II move constructor  rValue


class MyClass {
public:
    int data;
    
    
//     *****  Next phase   ******
//    MyClass(int& value) {  // without int& value creates conflict
//        data = value;
//      //  data = new int(std::move(value));
//        std::cout << "lValue  constructor called\n";
//    }


    MyClass(int&& value) {
        data = value;
      //  data = new int(std::move(value)); // for this line destructor required
        std::cout << "Move constructor called rValue Move \n";
    }

    // not necessary
    ~MyClass() {
       // delete data; //Thread 1: signal SIGABRT
    }
};

int myFunction(){
    return 123 ;
}
MyClass createObject() {
    std::cout << "Creating Object" << std::endl;
    MyClass obj(5);  // Move constructor called
   // obj.printData();
    return obj;
}

// *****************       Phase II move constructor  rValue ENDS here

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "lValue rValue std::Move \n";
    
    
    
    int *arr ; int *p; int x ; int y ;
    
    
    // lValue
    
    int i = 10 ;
    x ;
    *p;
    arr[ 0 ];
    
    // rValue
    
    12 ;
    
    x + y ;
    foo();
    
    
    int&  lValue = x ;
//    int&  lValue_x = 30 ;  // error
    
    
    int&&  rValue = 30 ;
    
   const  int& l_r_value = 23 ;  // meaning less
    
    
    //null xyz ;  // unknown type null ( void*) 0   non litral data type
    nullptr_t  myVar ; //    prvalue
    
    int xy ;
    
    
    int retValue = getValue();  // rValue
    getValue() = 111 ;
    
    
    // or  Work as expected !!  **********************************************************
      Widget widget1;  // lvalue object
      widget1.doWork1();  // Calls doWork() for lvalue objects
      
      Widget().doWork();  // rvalue object, temporary object created

  /*
   Doing work on lvalue object
   Doing work on rvalue object
   Program ended with exit code: 0
   */
    
    
    //********************************************
    
    // Phase II Widget_vec
    Widget_vec widget;

       // Accessing data() for lvalue object
       std::cout << "Data for lvalue object: ";
       for (const auto& value : widget.data()) {
           std::cout << value << " ";
       }
       std::cout << std::endl;

       // Accessing data() for rvalue object
       std::cout << "Data for rvalue object: ";
       for (const auto& value : Widget_vec().data() ) {
           std::cout << value << " ";
       }
       std::cout << std::endl;
    //*********************************************
    std::string s("Cat");  // constructor gets called
    std::string s2( s ) ;  // copy constructor
    std::string s3 ( makeCat() ); // r Value
    
    
    // Will not work..
    std::string s33 ( makeCat() ); // r Value
    
    std::string s34 ( std::move( makeCat() ) ); // r Value
    // std::move is an insane guy he is  in for a disauster!!!!!!!!
    // since he converts any given express to rValue
    
   // x = fun();  // xValue ( go out of scope )
    
    // Its our time now
    
    MyVector v1( 10 );
   // MyVector v7(  static_cast< MyVector&& >( v1 )  );  // x -> forwarding.. lVaue or rValue
    
    MyVector v11( 10 );
    MyVector v2 ( v1 );
    MyVector v3( MyVector(2) );
    MyVector v4 = v3 ;   // copy const
////
    
////
    MyVector v5( std::move( v4 ) );  // similar MyVector v7(  static_cast<MyVector&&>( v1 )  );  //
    
    
     //remember v4 memory is cleaned up
    // MyVector v6 = v4 ;// Thread 1: EXC_BAD_ACCESS (code=1, address=0x0)

            std::vector< MyVector > vec ;
            vec.push_back( MyVector(23 ));  // Landed in *** rValue constructor  ***  ....
    vec.emplace_back( MyVector(3)); //  Landed in *** rValue constructor ....  ***
     
  
    // *********** Phase II calling move constructor
    
    int value = 123;
    MyClass obj(value + 1 ); // pass int&& rvalue directly   value + 1 is raValue
    std::cout << "obj.data = " << obj.data << "\n";
    
    MyClass obj2( myFunction() ); // Move constructor called
    // Create object using move constructor with function return
        MyClass obj6 = createObject();
    
    //  Next phase
    // now declare  MyClass(int& value) { ** on top  **  Phase II
    int a = 10 ;
   // MyClass lval( a ); // error without creation of lValue constructor
    MyClass lval2( 10 ); // rValue exp val so calls move constructor



    // *********** Phase II calling move constructor Ends here
    
    
        std::vector<int> numbers = {1, 2, 3, 4, 5};
        std::for_each(numbers.begin(), numbers.end(), printFunc);

    
    // Invalid range expression of type 'MyVector'; no viable 'begin' function available
    // this is a diffrent iterator
    
    for( const auto& x : v1){
        cout << endl << " display from range.. "<< x << endl ;
    }

    int array[] = {10,20,30,40,50};
        for( const auto& x : array){
            cout << endl << " display from range array .. "<< x << "  " ;
        }

    for( const auto& x : numbers){
            cout << endl << " display from range vector .. "<< x << endl ;
        }

    for( const auto& x : v1){
            cout << endl << " display from range vector .. "<< x << endl ;
        }

      // ***********
    
    int array1[] = {100,200,300,400,500};
       for( auto i = begin( array1); i!= end( array1); ++i)
       {
           cout << " array1 begin( array1 ) end( array1 ) " << *i << endl ;
       }


       std::vector<int> vect{100,200,300,400,500};
       for( vector<int>:: const_iterator itr1 = vect.begin(); itr1 != vect.end(); ++itr1)
       {
           cout << *itr1 << " ";
       }
       

       MyVector v(10);
       for( const auto& x : v){
           cout << x << endl ;
       }
    
     //  int i = 10 ;

       
       // reffering to the initilizer list
       for(auto i : { 100,200,300,400 } )
       {
           cout << " ??? " << i << endl ;
       }
       
       //int meaningLessVar{12,13,14,15};
       
       int xyz[ 8 ] = { 11,12,13,14};

           // ***********  how swap works


           int aa=1, bb=1;
       
          // int& lVal = 10 ; // Non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'
           int& refA = aa;
           int& refB = bb;
       
           std::swap(refA,refB);
           cout <<" A " << aa << " B " << bb << endl;

           //*****************************************
    
    // creates a range with begin() and end()
    
    for (int i : std::ranges::iota_view{1, 10})
           std::cout << i << ' ';
    
       std::cout << '\n';
    
       for (int i : std::views::iota(1, 10))
           std::cout << i << ' ';
    
       std::cout << '\n';
   
    for (int n : range(0, 10)) {
        std::cout << n << std::endl;
    }
    

    //**************
    
    
    // c++ 11 range and map
    vector<string>  strings = { " Veg rolls "," Chicken"," Burger "};
    for( const auto& s: strings){ // deducing the type here
        cout << s << endl;
    }
    
    // map
    map<int,string>  phonebook = { make_pair(1,"Anand"),  make_pair(2,"Sri ram"), make_pair(3,"Sathya"),
                                     make_pair(4,"Samrath"), make_pair(5,"Kushi") };
  //  for( const pair<int,string>& p:phonebook ){ // deducing the type here
      for( const auto& p:phonebook ){ // deducing the type here
        cout << p.first << " , " << p.second << endl;
    }
    
 

    return 0;
}
/*
 lValue rValue std::Move
 Doing work on lvalue object
 Doing work on rvalue object
 Data for lvalue object: 1.1 2.2 3.3 4.4
 Data for rvalue object: 1.1 2.2 3.3 4.4
  -> Landed in regular constructor ....
  -> Landed in regular constructor ....
  -> Landed in copy  constructor ....
  -> Landed in regular constructor ....
  -> Landed in copy  constructor ....
  -> Landed in *** rValue constructor ....  ***
  -> Landed in regular constructor ....
  -> Landed in *** rValue constructor ....  ***
  -> Landed destructor ....
  -> Landed in regular constructor ....
  -> Landed in *** rValue constructor ....  ***
  -> Landed in copy  constructor ....
  -> Landed destructor ....
  -> Landed destructor ....
 Move constructor called rValue Move
 obj.data = 124
 Move constructor called rValue Move
 Creating Object
 Move constructor called rValue Move
 Move constructor called rValue Move
  from printFunc for_each  : 1
  from printFunc for_each  : 2
  from printFunc for_each  : 3
  from printFunc for_each  : 4
  from printFunc for_each  : 5
  begin()
  end()
  ---> operator[](int index ) []
  display from range.. 0

  display from range.. 1

  display from range.. 2

  display from range.. 3

  display from range.. 4

  display from range.. 5

  display from range.. 6

  display from range.. 7

  display from range.. 8

  display from range.. 9

  display from range array .. 10
  display from range array .. 20
  display from range array .. 30
  display from range array .. 40
  display from range array .. 50
  display from range vector .. 1

  display from range vector .. 2

  display from range vector .. 3

  display from range vector .. 4

  display from range vector .. 5
  begin()
  end()
  ---> operator[](int index ) []
  display from range vector .. 0

  display from range vector .. 1

  display from range vector .. 2

  display from range vector .. 3

  display from range vector .. 4

  display from range vector .. 5

  display from range vector .. 6

  display from range vector .. 7

  display from range vector .. 8

  display from range vector .. 9
  array1 begin( array1 ) end( array1 ) 100
  array1 begin( array1 ) end( array1 ) 200
  array1 begin( array1 ) end( array1 ) 300
  array1 begin( array1 ) end( array1 ) 400
  array1 begin( array1 ) end( array1 ) 500
 100 200 300 400 500  -> Landed in regular constructor ....
  begin()
  end()
  ---> operator[](int index ) [] 0
 1
 2
 3
 4
 5
 6
 7
 8
 9
  ??? 100
  ??? 200
  ??? 300
  ??? 400
  A 1 B 1
  Veg rolls
  Chicken
  Burger
 1 , Anand
 2 , Sri ram
 3 , Sathya
 4 , Samrath
 5 , Kushi
  -> Landed destructor ....
  -> Landed destructor ....
  -> Landed destructor ....
  -> Landed destructor ....
  -> Landed destructor ....
  -> Landed destructor ....
  -> Landed destructor ....
  -> Landed destructor ....
  -> Landed destructor ....
 Program ended with exit code: 0
 */
