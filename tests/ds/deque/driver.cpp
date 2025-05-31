#include <array>
#include <cstdlib>
#include <iostream>

#include "ds/deque.hpp"
#include "iterator_tests.hpp"
#include "methods_tests.hpp"

#define YES 1
#define NO 0

int main() {
  constexpr std::array<int, 5> values_i{ 1, 2, 3, 4, 5 };
  constexpr std::array<int, 5> source_i{ 6, 7, 8, 9, 0 };

  std::cout << ">>> Testing out deque with integers.\n";
  run_regular_deque_tests<int, 5>(values_i, source_i);

  // std::array<std::string, 5> values_s{"1", "2", "3", "4", "5"};
  // std::array<std::string, 5> source_s{"6", "7", "8", "9", "10"};
  // std::cout << ">>> Testing out deque with strings.\n";
  // run_regular_deque_tests<std::string, 5>(values_s, source_s);

  std::cout << "\n>>> Testing out iterator operations on deque.\n";
  run_iterator_tests<ds::Deque<int>>();

  return 1;
}
