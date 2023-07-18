//
//  main.cpp
//  17_VectorHowItWorks
//
//  Created by Sathya Babu on 02/05/22.
//
//////////////////////// end  of  Range based for loop///////////


//////////////////////// How it works
//////////////////////// Create a header file  : MyVector.h

//
//  MyVector.h
//  17_VectorHowItWrks
//
//  Created by Sathya Babu on 12/11/21.
//


#include <iostream>

using namespace std;

#ifndef MyVector_h
#define MyVector_h


#endif /* MyVector_h */

class MyVector{
    
public:
    
    MyVector(int i ) : size( i )
    {
        
        elements = new int[ i ]();
        
        for( int j = 0 ;j < i ; j++){
            elements[ j ] = j ;
        }
       
    }
    ~MyVector() {
        delete [] elements ;
    }
    
    
    
    int& operator[](int index ){
        
        if( index <0 || index > 10 ){
            std::cout << " -> Array out of bound!!!" ;//<< std::endl;
            return elements[ index ];
        }
       // std::cout << " -> operator[]( " <<  index  << " ) [] " ;//<< std::endl;
        
        return elements[ index ];
    }
    
    int getSize() {
        
        return size ;
    }
    
    //******** To over come the error in v : for( const auto& x : v) {
    // Minimize the intiference in the class pull this methods out of the class
    // s follows :
//            int* begin() {
//                std::cout << " begin() : ";
//                return  elements;  // NOT A GOOD IDEA while handling type
//            }
//            int* end(){
//                std::cout << " end() : ";
//                return elements + size ; // will not iterate for just with this line : return elements ;
//            }
    
    //******** To over come the error in v : for( const auto& x : v) {
    
   private :
    
    int* elements;
    int size ;
};

//**********   MyVector class ends here
//**********   Add Begin and end to over come error in PHASE II works if u remove the comments
//
//
//        int* begin(MyVector& v ) {
//
//            std::cout << " begin() : ";
//            //   return elements;
//            return  v.getSize() != 0 ? &v[0] : nullptr ;
//        }
//
//        int* end(MyVector& v ){
//            std::cout << " end() : ";
//
//           // return elements + size ; // will not iterate for just with this line : return elements ;
//
//            return  v.getSize() != 0 ? &v[0] + v.getSize()  : nullptr ;
//        }

/////////////////////////////// Main

//
//  main.cpp
//  17_VectorHowItWrks
//
//  Created by Sathya Babu on 12/11/21.
//


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    MyVector v( 10 );  // Lets take care of the storage limits using [] overload
    
    for( int i = 0 ; i < v.getSize(); ++i) {
        cout << v[ i ] << endl;
    }
    
    
    // ERROR : Invalid range expression of type 'MyVector'; no viable 'begin' function available COMPILER Looks for begin() end functions in vector()!!
    /* Let us add that to MyVector now
     
     //******** To over come the error in v : for( const auto& x : v) {
     int* begin() {
         return elements;
     }
     int* end(){
         return elements + size ;
     }
     
     //******** To over come the error in v : for( const auto& x : v) {
     */
    

      // before we fix the vector lets try array iteration  next block of the code
      // Invalid range expression of type 'MyVector'; no viable 'begin' function available
    
        for( const auto& x : v) { // add the above begin() end() to vector
            cout << endl << x << endl;
        }
    
    // Lets check the same on array
    // array has a built in begin() and end() functions
    
            int arr[] = {10,20,30,40,50};
            for( const auto& x : arr) {
                cout << " arr : "<< x << endl;
            }
            
                    // This is how it internally works!!!
                    // add #include <utility>
                    
                    int arr2[] = {10,20,30,40,50};
                    for( auto i = begin(arr2); i != end( arr2 );++i) {
                        cout << " arr  begin(arr2) end(arr2) : "<< *i << endl;
                    }
    

    return 0;
}
