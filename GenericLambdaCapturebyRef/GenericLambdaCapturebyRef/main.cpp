//
//  main.cpp
//  GenericLambdaCapturebyRef
//
//  Created by Sathya Babu on 09/10/21.
//

#include <iostream>
int main()

{

    int x = 100, y = 200;

    auto print = [&] { // Capturing object by reference

        std::cout << __PRETTY_FUNCTION__ << " : " << x << " , " << y << std::endl;
        std::cout << " : " << x << " , " << y << std::endl;

    };

    print();

    return 0;

}

/*
In the above example, I have mentioned & in the capture list. This captures variable x and y as a reference. Similarly, = denotes captured by value, which will create data member of the same type within the closure and copy assignment will take place.

Note that the parameter list is optional; you can omit the empty parentheses if you do not pass arguments to the lambda expression.
*/
