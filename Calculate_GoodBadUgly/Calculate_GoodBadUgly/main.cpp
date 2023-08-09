//
//  main.cpp
//  Calculate_GoodBadUgly
//
//  Created by Sathya Babu on 07/08/23.
//

#include <iostream>
#include <vector>
#include <numeric>
#include <execution>

#include <algorithm>
#include <chrono>
#include <thread>
using namespace  std;;
//******************************* swap
// Ugly
template<typename T>
void swap_old(T& a, T& b)
{
    // Copy construction
    T t = a;
    // Copy
    a = b;
    // Copy
    b = t;
}

// BAd
template<typename T>
void swap_new(T& a, T& b)
{
    // Move construction
    T t(std::move(a));
    // Move
    a = std::move(b);
    // Move
    b = std::move(t);
}

//  Good
//template<typename T>
//std::swap(T a , T b );

//***************************************

double CalculateSumForEach(const std::vector<double>& vector) noexcept
{
    double sum = 0.0;
    std::for_each(vector.cbegin(), vector.cend(),
             [&sum](const auto& element)
             {
                sum += element;
             });
    return sum;
}


double CalculateSumAccumulate(const std::vector<double>& vector) noexcept
{
    return std::accumulate(vector.cbegin(), vector.cend(), 0.0);
}


double CalculateSumForEachParallel(const std::vector<double>& vector) noexcept
{
    double sum = 0.0;
    // std::for_each(std::execution::par, vector.cbegin(), vector.cend(),
    std::for_each( vector.cbegin(), vector.cend(),
             [&sum](const auto& element)
             {
                sum += element;
             });

    return sum;
}

double CalculateSumClassic(const std::vector<double>& vector) noexcept
{
    double sum = 0.0;
    for (std::size_t i = 0; i < vector.size(); ++i)
    {
        sum += vector[i];
    }
    return sum;
}

// Bad examples with four common mistakes
double CalculateSumClassicWrong(const std::vector<double>& vector)
{
    double sum = 0.0;
    double i;
    for (i = 0; i < vector.size(); i++)
    // for (auto i = 0; i < vector.size(); i++)
    {
        sum += vector.at(i);
    }
    return sum;
}

template< typename T> void benchmark(const std::vector<double>& values, T function, const std::string& name)
{
    // Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now();
    
    // Execute the function
    auto sum = function(values);

    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now();
    
    // Calculate time and output result
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    
    
    cout << "\n name  " << name  << endl ;
    cout << "\n sum " << sum << endl ;
    cout << "\n count " << duration.count() << endl ;
    
    //IC(name, sum, duration.count());
}

double CalculateSumIterator(const std::vector<double>& vector) noexcept
{
    double sum = 0.0;
    for (auto it = vector.cbegin(); it < vector.cend(); ++it)
    {
        sum += *it;
    }
    return sum;
}

// Bad examples with two common mistakes
double CalculateSumIterator2(const std::vector<double>& vector) noexcept
{
    double sum = 0.0;
    for (auto it = vector.begin(); it < vector.end(); it++)
    {
        sum += *it;
    }
    return sum;
}
double CalculateSumRange(const std::vector<double>& vector) noexcept
{
    double sum = 0;
    for (const auto& element : vector)
    {
        sum += element;
    }
    return sum;
}

// Bad examples with one common mistake
double CalculateSumRange2(const std::vector<double>& vector) noexcept
{
    double sum = 0;
    for (auto& element : vector)
    {
        sum += element;
    }
    return sum;
}

int main()
{
    std::vector<double> values(10000000);
    // Generate Random values
    auto f = []() -> double { return rand() / 10000.0; };
    // Fill up the vector
    std::generate(values.begin(), values.end(), f);
    
    benchmark(values, CalculateSumClassicWrong,"CalculateSumClassicWrong");
    benchmark(values, CalculateSumClassic,"CalculateSumClassic");
    benchmark(values, CalculateSumIterator,"CalculateSumIterator");
    benchmark(values, CalculateSumRange,"CalculateSumRange");
    benchmark(values, CalculateSumForEach,"CalculateSumForEach");
    benchmark(values, CalculateSumAccumulate,"CalculateSumAccumulate");
    benchmark(values, CalculateSumForEachParallel,"CalculateSumForEachParallel");
    
    return 0;
}
