
#include <memory>
#include <iostream>
#include <utility>

template <class T> void run(T&& runnable)
{
  runnable(); // while executing finds *results is already implicitly-deleted
};

int main()
{
  std::unique_ptr<int> result(new int{42});
  run([ &result ](){std::cout << *result << std::endl;});// Error :

   // Call to implicitly-deleted copy constructor of 'std::unique_ptr<int>'
}
