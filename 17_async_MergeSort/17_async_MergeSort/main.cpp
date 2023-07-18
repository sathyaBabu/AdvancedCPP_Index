//
//  main.cpp
//  17_async_MergeSort
//
//  Created by Sathya Babu on 29/05/23.
// https://devtut.github.io/cpp/futures-and-promises.html#std-future-and-std-async
// This file is comm
//ited in git
#include <algorithm>
#include <future>
#include <iostream>
#include <mutex>
#include <numeric>
#include <string>
#include <vector>

using namespace std;
/*
 
 Note: In the example std::async is launched with policy std::launch_deferred. This is to avoid a new thread being created in every call. In the case of our example, the calls to std::async are made out of order, the they synchronize at the calls for std::future::get().

 std::launch_async forces a new thread to be created in every call.

 The default policy is std::launch::deferred| std::launch::async, meaning the implementation determines the policy for creating new threads.

 
 */
void merge(int low, int mid, int high, vector<int>& num)
{
    vector<int> copy(num.size());
    int h, i, j, k;
    h = low;
    i = low;
    j = mid + 1;

    while ((h <= mid) && (j <= high))
    {
        if (num[h] <= num[j])
        {
            copy[i] = num[h];
            h++;
        }
        else
        {
            copy[i] = num[j];
            j++;
        }
        i++;
    }
    if (h > mid)
    {
        for (k = j; k <= high; k++)
        {
            copy[i] = num[k];
            i++;
        }
    }
    else
    {
        for (k = h; k <= mid; k++)
        {
            copy[i] = num[k];
            i++;
        }
    }
    for (k = low; k <= high; k++)
        swap(num[k], copy[k]);
}

void merge_sort(int low, int high, vector<int>& num)
{
    int mid;
    if (low < high)
    {
        mid = low + (high - low) / 2;
        auto future1 = std::async(std::launch::async, [&]() // std::launch::deferred
        {
            merge_sort(low, mid, num);
        });
        auto future2 = std::async(std::launch::async, [&]()
        {
            merge_sort(mid + 1, high, num);
        });

        future1.wait();
        future2.wait();
        merge(low, mid, high, num);
    }
}

int main()
{
    vector<int> numbers = { 9, 3, 7, 1, 5, 4, 8, 2, 6 };

    cout << "Before sorting: ";
    for (const auto& num : numbers)
        cout << num << " ";
    cout << endl;

    merge_sort(0, numbers.size() - 1, numbers);

    cout << "After sorting: ";
    for (const auto& num : numbers)
        cout << num << " ";
    cout << endl;

    return 0;
}
/*
 output : 
 Before sorting: 9 3 7 1 5 4 8 2 6
 After sorting: 1 2 3 4 5 6 7 8 9
 Program ended with exit code: 0
 */
