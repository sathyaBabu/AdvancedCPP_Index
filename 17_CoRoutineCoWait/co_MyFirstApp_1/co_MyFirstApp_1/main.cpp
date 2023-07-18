//
//  main.cpp
//  co_MyFirstApp_1
//
//  Created by Sathya Babu on 29/11/21.
/*
 
    prerequsite : C++  : Modern C++
 
    Goals :  Container class( Vctor Map list array --> Algo.. o(n)/ o(1)  1 2 3 4 5... 10
          Bubble sort :  int sort[5][5] // nested for loop  o(n2)
 
     depreciated :
      variables!!!!   expressions..
      if
       for
       NULL
       const
       new delete
       int array[]
         constructors
         inheritance
         return
         threads..
 
 
    //
 
 
 
    //                        Wrapper API  modern c++
    /////// ------------------- Hidden -----------------------
    C++ ( Legacy )
    C
    assembly language
 
   Day 1 :
        var   :  int i = 90 ; ? Was : and what is is ? alignment
        NULL vs nullptr
        const vs constexpr
        casting (char) i ;  constCasting static casting... any
        auto deducing..
 
        unique ptr
        shared ptr
        weak ref
 
        Range based for loops  / for each..
 
 
        Expressions :   lValue rvalue , gvalue prvalue xvalue
        copy constructors.. move sematics..
        forwarding..
 
 
 */

#include <iostream>
#include<cstdint>  // for fixed-width integers..
using namespace std;

int main(int argc, const char * argv[]) {
    
      //  int i = 233453455 ;
    
//         cout << " hello C++" << endl ;
    
        std::cout << "least 8:  " << sizeof(std::int_least8_t) * 8 << " bits\n";
        std::cout << "least 16: " << sizeof(std::int_least16_t) * 8 << " bits\n";
        std::cout << "least 32: " << sizeof(std::int_least32_t) * 8 << " bits\n";
        std::cout << '\n';
         // alignment!!!!
         // typedef :  using
       std::cout << "fast 8:  " << sizeof(std::int_fast8_t) * 8 << " bits\n";       // check for the use case
        std::cout << "fast 16: " << sizeof(std::int_fast16_t) * 8 << " bits\n";
        std::cout << "fast 32: " << sizeof(std::int_fast32_t) * 8 << " bits\n";
   
    // faster secured and aligned..
    
    //  A peek at the word alignment
    // query is_safe   is_int
        long ptr_ok = reinterpret_cast< int>(nullptr);
        // OK Cast from pointer to smaller type 'int' loses information
    
        std::int16_t ii{5};  // means High order : interpreter_list and so on
        std::cout << ii;
    
    // core : seg over wrap concept..
       std::uint_fast16_t sometype { 0 };   // fast_32_t : 4294967295
       --sometype; // intentionally overflow to invoke wraparound behavior

       std::cout << sometype; // 65556
       std::cout << " size of fast16_t "<< sizeof(uint_fast16_t ) << " sometype = " << sometype; //  size of fast16_t 2 : 65535   sometype = 65556
        
   // U_key = long long values
    
    /*
     bp = 0
     ---------
     |        |
     |        |
     |        |
     ----------( sp 65556 )  // 64k seg..
     
     
     */
    // 65535 size of fast16_t 2 sometype = 65535Program ended with exit code: 0

    return 0;
}


/*

       Given a pointer ptr to a buffer of size space, returns a pointer aligned by the specified alignment
       for size number of bytes and decreases space argument by the number of bytes used for alignment.
       The first aligned address is returned.

        The function modifies the pointer only if it would be possible to fit the wanted number of bytes
        aligned by the given alignment into the buffer. If the buffer is too small,
        the function does nothing and returns nullptr.

       void* align( std::size_t alignment,
             std::size_t size,
             void*& ptr,
             std::size_t& space );

    (since C++11)





*/
inline void*
align(size_t __align, size_t __size, void*& __ptr, size_t& __space) noexcept
{
  if (__space < __size)
    return nullptr;
  const auto __intptr = reinterpret_cast<uintptr_t>(__ptr);
  const auto __aligned = (__intptr - 1u + __align) & -__align;
  const auto __diff = __aligned - __intptr;
  if (__diff > (__space - __size))
    return nullptr;
  else
    {
      __space -= __diff;
      return __ptr = reinterpret_cast<void*>(__aligned);
    }
}

/*
 
 least 8:  8 bits
 least 16: 16 bits
 least 32: 32 bits

 fast 8:  8 bits
 fast 16: 16 bits
 fast 32: 32 bits
 5
 
 65535 size of fast16_t 2 sometype = 65535Program ended with exit code: 0
 */
