#include <array>
#include <cstdlib>
#include <iostream>

#include "ds/deque/deque.hpp"
#include "iterator_tests.hpp"
#include "methods_tests.hpp"

int main() {
  const std::array<int, 16> values_i{1, 2,  3,  4,  5,  6,  7,  8,
                                     9, 10, 11, 12, 13, 14, 15, 16};
  std::cout << ">>> Testing out Deque with integers values.\n";
  run_regular_deque_tests<int, values_i.size()>(values_i);

  const std::array<double, 16> values_d{0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
                                        0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
  std::cout << "\n>>> Testing out Deque with double values.\n";
  run_regular_deque_tests<double, values_d.size()>(values_d);

  const std::array<std::string, 16> values_s{"0", "1", "2", "3", "4", "5",
                                             "6", "7", "8", "9", "a", "b",
                                             "c", "d", "e", "f"};
  std::cout << "\n>>> Testing out Deque with strings values.\n";
  run_regular_deque_tests<std::string, values_s.size()>(values_s);

  // std::cout << "\n>>> Testing out iterator operations on Deque.";
  // run_iterator_tests<ds::Deque<int>>();

  return 1;
}
