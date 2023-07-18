
//  Parallel Algorithms

// execute the same with the on line compiler
// https://www.programiz.com/cpp-programming/online-compiler/
// 17_Parallel_Algorithms_for_each
/*
 
 Let’s discuss the execution policies in detail:
 • Sequential execution with seq
 means that as with the non-parallel algorithms the current thread of execution sequentially executes the necessary operations element by element. Using this policy should behave like using the non-parallel way to call algorithms not passing any execution policy at all. However, with the parallel algorithms taking this argument additional constraints might apply, such as for_each() not returning any value or that all iterators have to be at least forward iterators.
 This policy is provided to be able to request sequential execution by just passing a different argument instead of using a different signature. Note however that parallel algorithms with this policy might behave slightly different than corresponding non-parallel algorithms.
 • Parallel sequenced execution with par
 means that multiple thread might sequentially execute the necessary operations for the ele-
 ments. When an algorithm starts with the execution of the necessary operations, it finishes this execution before it deals with other elements.
 In contrast to par_unseq this enables to ensure that no problems or deadlocks occur because after processing a step for one element require the call of another step for this element before the same thread performs the first step with another element.
 • Parallel unsequenced execution with par_unseq
 means that multiple thread might execute the necessary operations for multiple elements with-
 out the guarantee that one thread executes all steps for the element without switching to other elements. This especially enables vectorized execution where a thread might first perform the first step of an execution for multiple elements before it executes the next step.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include<execution>
int numElems = 1000;

int main() {
    std::vector<int> nums = {5, 2, 4, 1, 3};
    for (int i=0; i<numElems; ++i) {
      nums.emplace_back( i * 10 );
    }

    // Start the timer
    auto startTime = std::chrono::high_resolution_clock::now();

    // Perform the for_each algorithm in parallel
    // (std::execution::seq  12 ms
    // (std::execution::par  9 ms
    std::for_each(std::execution::seq, nums.begin(), nums.end(), [](int& num) {
        num *= 2; // Perform some operation on each element
    });

    // Stop the timer
    auto endTime = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    // Print the modified vector
    std::cout << "Modified vector: ";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Print the execution time
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
/*
 
 execution:seq
 Execution time: 18 microseconds
 Modified vector: 10 4 8 2 6 0 20 40 60 80 100 120 140 160 180 200 220 240 260 280 300 320 340 360 380 400 420 440 460 480 500 520 540 560 580 600 620 640 660 680 700 720 740 760 780 800 820 840 860 880 900 920 940 960 980 1000 1020 1040 1060 1080 1100 1120 1140 1160 1180 1200 1220 1240 1260 1280 1300 1320 1340 1360 1380 1400 1420 1440 1460 1480 1500 1520 1540 1560 1580 1600 1620 1640 1660 1680 1700 1720 1740 1760 1780 1800 1820 1840 1860 1880 1900 1920 1940 1960 1980 2000 2020 2040 2060 2080 2100 2120 2140 2160 2180 2200 2220 2240 2260 2280 2300 2320 2340 2360 2380 2400 2420 2440 2460 2480 2500 2520 2540 2560 2580 2600 2620 2640 2660 2680 2700 2720 2740 2760 2780 2800 2820 2840 2860 2880 2900 2920 2940 2960 2980 3000 3020 3040 3060 3080 3100 3120 3140 3160 3180 3200 3220 3240 3260 3280 3300 3320 3340 3360 3380 3400 3420 3440 3460 3480 3500 3520 3540 3560 3580 3600 3620 3640 3660 3680 3700 3720 3740 3760 3780 3800 3820 3840 3860 3880 3900 3920 3940 3960 3980 4000 4020 4040 4060 4080 4100 4120 4140 4160 4180 4200 4220 4240 4260 4280 4300 4320 4340 4360 4380 4400 4420 4440 4460 4480 4500 4520 4540 4560 4580 4600 4620 4640 4660 4680 4700 4720 4740 4760 4780 4800 4820 4840 4860 4880 4900 4920 4940 4960 4980 5000 5020 5040 5060 5080 5100 5120 5140 5160 5180 5200 5220
 Execution time: 18 microseconds
*/
