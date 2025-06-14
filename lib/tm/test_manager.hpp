#ifndef _TEST_MANAGER_
#define _TEST_MANAGER_

/*!
 * @file test_manager.h
 * @brief Definition of the TestManager class.
 * @date November 15th, 2019
 * @author Selan R. dos Santos
 *
 * Updated on January 27th, 2021: improved macro definition and unified
 * divergent versions.
 */

#include <cstdint>
#include <iostream> // cout, endl
using std::cout;
using std::endl;
#include <iomanip> // setw
using std::setw;
#include <algorithm> // shuffle, copy
using std::copy;
using std::shuffle;
#include <string>
using std::string;
#include <unordered_map>
#include <utility>
using std::unordered_map;
#include <string_view>
using std::string_view;

/// Implements a simple test manager.
class TestManager
{
private:
  /// Defines a single entry in our database.
  struct Entry
  {
    /// List of possible test results.
    enum class result_t : std::uint8_t
    {
      SUCCESS,
      FAILED,
      UNDEFINED
    };
    string_view m_desc; //!< The test text description.
    // This help us print the test in order the client registers them.
    size_t m_seq;      //!< The test sequence number.
    result_t m_result; //!< The test result.
    int m_line;        //!< The test line number.
    bool m_enabled;    //!< Indicates if the test is enabled (default) or not.
    /// Default Ctro
    Entry(string_view desc = "no_name", size_t seq = 0,
          result_t result = result_t::UNDEFINED, int line = 0,
          bool enabled = true)
        : m_desc{desc}, m_seq{seq}, m_result{result}, m_line{line},
          m_enabled{enabled} { /* empty */ }
  };
  /// Records the tests results. Key is the test name; data is an `Entry`.
  std::unordered_map<string_view, Entry> tests_record;
  /// The test suite name.
  std::string test_suite_name;
  /// Number of tests registred.
  size_t n_tests{0};

  /// Prints out the overall result of a single test.
  static void print_test_result(string_view test_name, const Entry &entry)
  {
    std::cout << "[ "
              << "\33[1;34mRUN\33[0m"
              << "       ] " << test_name << "-> " << entry.m_desc << '\n';
    if (not entry.m_enabled)
    {
      std::cout << "[  "
                << "\33[1;36mDISABLED\33[0m"
                << " ]\n";
      return;
    }
    if (entry.m_result == Entry::result_t::SUCCESS)
    {
      std::cout << "[        "
                << "\33[1;32mOK\33[0m"
                << " ]\n";
    }
    else if (entry.m_result == Entry::result_t::FAILED)
    {
      std::cout << "[      "
                << "\33[1;31mFAIL\33[0m"
                << " ] at line " << entry.m_line << ".\n";
    }
    else if (entry.m_result == Entry::result_t::UNDEFINED)
    {
      std::cout << "[ "
                << "\33[1;35mUNDEFINED\33[0m"
                << " ] at line " << entry.m_line << ".\n";
    }
  }

  //=== Public interface.
public:
  /// Default constructor that may take the test suite name.
  explicit TestManager(string_view suite_name = "Default")
      : test_suite_name{suite_name} { /* empty */ }

  /// Registers a test with this suite
  void record(string_view key_name, string_view msg)
  {
    // Store the entry in the data base.
    tests_record[key_name] = Entry{msg, n_tests++};
  }

  /// Enables/Disable a test for running, based on `value`.
  void enable(string_view key_name, bool value = true)
  {
    // First, let us see if the key is recorded (test has been registered)
    if (tests_record.count(key_name) == 0)
    {
      return;
    }
    // Ok, test present. Just set the disabled status accordingly.
    tests_record[key_name].m_enabled = value;
  }

  /// Updates the test result.
  void result(string_view key, bool value, int line);

  /// Shows the test suite results.
  void summary() const;
};

//== MACRO definitions.
#define BEGIN_TEST(tm, key, msg)  \
  std::string_view _test_id{key}; \
  TestManager &_tm = tm;          \
  _tm.record(key, msg)
#endif
// #define RESULT(tm, key, res) tm.result( key, res, __LINE__ )
#define RESULT(key, res) _tm.result(key, res, __LINE__)
// #define REGISTER(tm, key, msg) tm.record( key, msg )
#define REGISTER(key, msg) _tm.record(key, msg)
#define EXPECT_TRUE(value) _tm.result(_test_id, (value) == true, __LINE__)
#define EXPECT_FALSE(value) _tm.result(_test_id, (value) == false, __LINE__)
#define EXPECT_EQ(value1, value2) \
  _tm.result(_test_id, (value1) == (value2), __LINE__)
#define EXPECT_NE(value1, value2) \
  _tm.result(_test_id, (value1) != (value2), __LINE__)
#define EXPECT_GT(value1, value2) \
  _tm.result(_test_id, (value1) > (value2), __LINE__)
#define EXPECT_GE(value1, value2) \
  _tm.result(_test_id, (value1) >= (value2), __LINE__)
#define EXPECT_LT(value1, value2) \
  _tm.result(_test_id, (value1) < (value2), __LINE__)
#define EXPECT_LE(value1, value2) \
  _tm.result(_test_id, (value1) <= (value2), __LINE__)
#define DISABLE() _tm.enable(_test_id, false);
