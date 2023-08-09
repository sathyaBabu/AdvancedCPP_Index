//
//  main.cpp
//  2_2_SI_FunctionObjectVSLambda
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
using namespace std;


// lambda
auto sum = [ ]( const auto& a , const auto& b  ) {  return a + b;  };

typedef int ( *fun_ptr )();
fun_ptr fn = [] ()  -> int { cout << "lambda returns...."; return 123 ; };



//typedef int ( *fun_ptr )();

auto fn2 = [ ] ()  -> int { cout << "lambda returns 2...."; return 123 ; };




// FunctionObject
class Anonymous
{
    
    public :
    
    template< class T1 , class T2>
   constexpr auto operator() ( T1 a , T2 b   )
    {
        return  a + b ;
    }
    
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Anonymous an ;
    auto res = an( 10,20 );
    cout << " Result by Anonymous " << res << endl ;  //  Result by Anonymous 30
    
    cout << " Result by Lambda sum  " << sum( 12,30 ) << endl ;  //   Result by Lambda sum  42
    
    fn2();
    [] { cout << "lambda returns 3....";  } () ;
    
    return 0;
}
/*
 Hello, World!
  Result by Anonymous 30
  Result by Lambda sum  42
 lambda returns 2....lambda returns 3....Program ended with exit code: 0
 */
