//
//  main.cpp
//  FunctionVariousReturnType_1
//
//  Created by Sathya Babu on 11/07/23.
//
/*
 
 we have defined two functions: add which adds two integers, and printValue which prints an integer value. The call function is used to invoke these functions with arguments.

When calling call(printValue, 42), the return type is void, so the code inside the if statement is executed. It calls the printValue function with the argument 42 and prints "Value: 42".

When calling call(add, 10, 20), the return type is int, so the code inside the else statement is executed. It calls the add function with the arguments 10 and 20, and assigns the return value to the result variable. It then prints "Result: 30".

This code demonstrates how the call function can handle different return types and perform actions based on the type of the return value.
 //--------------------------------
 The std::invoke_result_t is a type trait provided by the C++ standard library. It is used to extract the return type of a callable (such as a function, function pointer, or member function pointer) when invoked with specific arguments.

 The std::invoke_result_t takes two template arguments: the callable type and the argument types. It evaluates to the type that would be returned if the callable is invoked with the given argument types.

 For example, given a callable Callable and a set of argument types Args, std::invoke_result_t<Callable, Args...> evaluates to the return type of calling Callable with arguments of types Args....

 In the context of the call function in your example code, std::invoke_result_t<Callable, Args...> is used to determine the return type of the op callable when invoked with the provided arguments Args.... It is then used to conditionally handle different behavior based on whether the return type is void or not.

 By using std::invoke_result_t, you can write more generic code that adapts to the return type of the callable, allowing for flexibility and compile-time type checking.
 */
#include <iostream>
#include <functional>
#include <type_traits>

template<typename Callable, typename... Args>
decltype(auto) call(Callable op, Args&&... args)
{
    if constexpr(std::is_void_v<std::invoke_result_t<Callable, Args...>>) {
        // Return type is void
        op(std::forward<Args>(args)...);
        std::cout << "Returned void" << std::endl;
    }
    else {
        // Return type is not void
        decltype(auto) ret{op(std::forward<Args>(args)...)};
        std::cout << "Returned: " << ret << std::endl;
        return ret;
    }
}

int add(int a, int b)
{
    return a + b;
}

void printValue(int value)
{
    std::cout << "Value: " << value << std::endl;
}

int main()
{
    call(printValue, 42);
    int result = call(add, 10, 20);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
/*
 Value: 42
 Returned void
 Returned: 30
 Result: 30
 Program ended with exit code: 0
 */
