//
//  main.cpp
//  17_InvokeVSfnptr_1
//
//  Created by Sathya Babu on 28/03/23.
//

#include <functional>
#include <iostream>

struct foo
{
    void echo(){std::cout << "foo" << std::endl;};
};

int main()
{
    ////
    // Vanilla version of invoking .echo()
//    foo(f);
    // or
    foo  f ;
    f.echo();

    ////
    // Pointer to *class* member function version
    void (foo::* pf)() =  &foo::echo;
    foo obj;
    
    (obj.*pf)();    // ugly
    // instead do ...
    std::invoke(pf, obj);

    // obj->echo(); <-- does not compile

    return 0;
}
/*
 foo
 foo
 foo
 Program ended with exit code: 0
 */
