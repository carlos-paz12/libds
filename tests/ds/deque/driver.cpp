#include <array>
#include <cstdlib>
#include <iostream>

#include "ds/deque.hpp"
#include "iterator_tests.hpp"
#include "methods_tests.hpp"

int main() {
  const std::array<int, 5> values_i{ 1, 2, 3, 4, 5 };
  std::cout << ">>> Testing out Deque with integers values.\n";
  run_regular_deque_tests<int, values_i.size()>(values_i);

  //  const std::array<double, 5> values_d{ 1.9, 2.64, 3.14, 4.0, -2 };
  //  std::cout << "\n>>> Testing out Deque with double values.\n";
  //  run_regular_deque_tests<double, values_d.size()>(values_d);

  //  const std::array<std::string, 5> values_s{ "6", "7", "8", "9", "0" };
  //  std::cout << "\n>>> Testing out Deque with strings values.\n";
  //  run_regular_deque_tests<std::string, values_s.size()>(values_s);

  std::cout << "\n>>> Testing out iterator operations on Deque.";
  run_iterator_tests<ds::Deque<int>>();

  return 1;
}
