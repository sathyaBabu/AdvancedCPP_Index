//
//  main.cpp
//  17_IteratorBasic_1
//
//  Created by Sathya Babu on 28/09/22.
//

///////////////////// Stack iterator simple one

//
//  main.cpp
//  StackIteratorSimple
//
//  Created by Sathya Babu on 21/07/22.
//

#include <iostream>
#include<string>

using namespace std;

// pre declaration
class StackIter;
class StackArrayImpl ; // new



#define MAX 10

class IStack
{
public:
    virtual void push(int iNum) = 0;
    virtual int pop()  = 0;
    virtual int top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
};

class StackArrayImpl : public IStack
{
private:
   
  //  int items[10];
   
public:
    int _top;
    int _Array[MAX];
    StackArrayImpl() { _top = -1; }


    int top() const
    {
        return _top;
    }

    void push(int iNum)
    {
        if (!isFull())
            _Array[++_top] = iNum;
    }

    int pop()
    {
        int topInt = -1;
        if (!isEmpty())
        {
            topInt = _Array[_top--];
            
        }
        else
        {
            cout << "\nStack EMPTY";
        }

        return topInt;
    }
    bool isFull() const
    {
        return (_top == MAX);
    }

    bool isEmpty() const
    {
        return (0 == _top);
    }
    StackIter *createIterator();  // 2. Add a createIterator() member
    
//    int getSize(){
//        return 0 ;
//    }
//    int getEnd(){
//       return  _top;
//    }

};

class StackIter
{
    // 1. Design an "iterator" class
    const StackArrayImpl  *stk;   // this pointer of StackArrayImpl is stored here
    int index;
  public:
    StackIter(const StackArrayImpl  *s )
    {
        stk = s;
    }
    void first()
    {
        index = 0;
    }
    void next()
    {
        index++;
    }
    bool isDone()
    {
        return index == stk-> _top + 1;
    }
    int currentItem()
    {
        return stk -> _Array[ index ] ;
    }
};
// iterator provider
StackIter *StackArrayImpl :: createIterator()
{
    // change this yo unique_ptr make_unique
  return new StackIter( this );
}
//


int main(int argc, const char * argv[]) {
    
    StackArrayImpl s1;

    for (int i = 1; i < 5; i++)
            s1.push(i);
    ////
    // prints 1 2 3 4

    StackIter *itl = s1.createIterator();
    for (itl->first(); !itl->isDone(); itl->next())
    {
        cout << " got from iterator "<< itl->currentItem() << endl ;
    }
    ////
    ///
//    ///int arr[] = {10,20,30,40,50};
//    for( const auto& x : *itl) {  // Invalid range expression of type 'StackIter'; no viable 'begin' function available
//        cout << " arr : "<< x << endl;
//    }
    

}
/*
 got from iterator 1
 got from iterator 2
 got from iterator 3
 got from iterator 4
Program ended with exit code: 0
 
 */
