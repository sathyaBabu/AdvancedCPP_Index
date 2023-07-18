//
//  main.cpp
//  25_SingleTon_1
//
//  Created by Sathya Babu on 25/04/23.
//

#include <iostream>
using namespace std ;

class Singleton{
    
    static Singleton *instance ;
    static int refpointer ;
    int data ;
 
    Singleton(){
        cout << " At Single ton constructor " << endl ;
        data = 0 ;
    }
    
public:
    
    static Singleton* getInstance(){
        
        if( !instance ){
            
            instance = new Singleton ;
            refpointer++;
            cout << " Holding ref to User " << refpointer << " log." << endl ;
            
            return instance;
        }
                   refpointer++;
                   cout << " Holding ref to User " << refpointer << " log." << endl ;
                   
                  return instance;
        
        
    }
    
    int getData() {
          return this -> data;
       }

       void setData(int data) {
          this -> data = data;
       }
    
        int getrefPointer() {
            return refpointer;
        }
        int clearRefPointer() {
            cout << " User logged out " << refpointer <<  endl ;
            return refpointer--;
        }
        
        ~Singleton (){
            cout << " NO one is using the object( Idel ) " << refpointer <<  endl ;
    //        if( refpointer == 0)   // we should not delete the object..
    //             delete instance;
        }
    
};


//Initialize pointer to zero so that it can be initialized in first call to getInstance
Singleton *Singleton::instance = NULL;
      int Singleton::refpointer = 0;


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Singleton *s = Singleton::getInstance();
    Singleton *ss = Singleton::getInstance();
    
    Singleton *sss = Singleton::getInstance();
    
    
//    SingleTon *s2 = new SingleTon;
//    SingleTon *s3 = new SingleTon;
    
    
    cout << s->getData() << endl;
    s->setData(100);
    cout << s->getData() << endl;
     
     cout << ss->getrefPointer() << endl;
     s->clearRefPointer();
     cout << ss->getrefPointer() << endl;
     s->clearRefPointer();
     cout << ss->getrefPointer() << endl;
   

     s->getrefPointer();
     
     // People started moving out on some condition in your code
     
     ss->clearRefPointer();  // clear justr a log
     ss->clearRefPointer();  // clear justr a log
     ss->clearRefPointer();  // clear justr a log
     ss->clearRefPointer();  // clear justr a log
     
     s->getrefPointer();
    
    
    return 0;
}
/*
 Hello, World!
  At Single ton constructor
  Holding ref to User 1 log.
  Holding ref to User 2 log.
  Holding ref to User 3 log.
 0
 100
 3
  User logged out 3
 2
  User logged out 2
 1
  User logged out 1
  User logged out 0
  User logged out -1
  User logged out -2
 Program ended with exit code: 0
 */
