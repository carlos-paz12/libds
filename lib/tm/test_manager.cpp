/*!
 * @file test_manager.cpp
 * @brief Implementation of the TestManager class.
 * @date November 15th, 2019
 * @author Selan R. dos Santos
 */

#include "test_manager.hpp"

#include <vector>

/*!
 * Updates the test result database.
 * @param key The unique test key, which is the test's name.
 * @param value The result of the test, that might either be `true` or `false`.
 * @param line The line number in the source code, where the teste happened.
 */
void TestManager::result(std::string_view key, bool value, int line)
{
  // Get previous result.
  auto old_entry = tests_record[key];
  // We only update if the previous result is TRUE or UNDEFINED.
  // Otherwise, we keep the first failure.
  if (old_entry.m_result == Entry::result_t::SUCCESS or
      old_entry.m_result == Entry::result_t::UNDEFINED)
  {
    tests_record[key].m_result =
        value ? Entry::result_t::SUCCESS
              : Entry::result_t::FAILED; // Update the result.
    tests_record[key].m_line = line;     // Update the line.
  }
}

void TestManager::summary() const
{
  size_t n_successful{0};
  size_t n_failed{0};
  size_t n_disabled{0};
  size_t n_undefined{0};

  // This list helps us to print all the test results in the same order
  // the user specified in his/get client code.
  using hash_item = std::pair<string_view, Entry>;
  std::vector<hash_item> sorted_list;
  // Copy the hash table to a vector, so we can sort the item by sequence.
  std::copy(tests_record.begin(), tests_record.end(),
            std::back_inserter(sorted_list));
  // Sort the vector
  std::sort(sorted_list.begin(), sorted_list.end(),
            [](const hash_item &h1, const hash_item &h2) -> bool
            {
              return h1.second.m_seq < h2.second.m_seq;
            });

  // Print out the tests result from the sorted list.
  std::cout << "[===========] Running " << n_tests << " from the \""
            << test_suite_name << "\" test suite.\n";
  for (const auto &[test_name, entry] : sorted_list)
  {
    print_test_result(test_name, entry);
    if (not entry.m_enabled)
    {
      n_disabled++;
    }
    else if (entry.m_result == TestManager::Entry::result_t::SUCCESS)
    {
      n_successful++;
    }
    else if (entry.m_result == TestManager::Entry::result_t::FAILED)
    {
      n_failed++;
    }
    else if (entry.m_result == TestManager::Entry::result_t::UNDEFINED)
    {
      n_undefined++;
    }
  }
  std::cout << "[===========] " << n_tests << " tests from the \""
            << test_suite_name << "\" test suite ran.\n";

  // Final summary
#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || \
    defined(__WIN32__) || defined(__WINDOWS__)
  if (n_successful != 0)
    std::cout << "[ " << "PASSED" << "    ] " << n_successful << " tests.\n";
  if (n_failed != 0)
    std::cout << "[ " << "FAILED" << "    ] " << n_failed << " tests.\n";
  if (n_disabled != 0)
    std::cout << "[ " << "DISABLED" << "  ] " << n_disabled << " tests.\n";
  if (n_undefined != 0)
    std::cout << "[ " << "UNDEFINED" << " ] " << n_undefined << " tests.\n";
#else
  if (n_successful != 0)
  {
    std::cout << "[ " << "\33[1;32mPASSED\33[0m" << "    ] " << n_successful
              << " tests.\n";
  }
  if (n_failed != 0)
  {
    std::cout << "[ " << "\33[1;31mFAILED\33[0m" << "    ] " << n_failed
              << " tests.\n";
  }
  if (n_disabled != 0)
  {
    std::cout << "[ " << "\33[1;36mDISABLED\33[0m" << "  ] " << n_disabled
              << " tests.\n";
  }
  if (n_undefined != 0)
  {
    std::cout << "[ " << "\33[1;35mUNDEFINED\33[0m" << " ] " << n_undefined
              << " tests.\n";
  }
#endif
}
