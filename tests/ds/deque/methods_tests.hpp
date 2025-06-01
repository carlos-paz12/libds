#ifndef DEQUE_METHODS_TESTS_HPP
#define DEQUE_METHODS_TESTS_HPP

#include <array>
#include <cstddef>
#include <deque>

#include "ds/deque.hpp"
#include "test_manager.hpp"

#define YES 1
#define NO 0

#define DEFAULT_CTRO YES
#define FILL_CTRO YES
#define RANGE_CTRO YES
#define COPY_CTRO YES
#define INIT_LIST_CTRO YES
#define ASSIGNMENT_COPY_OP YES

template<typename T, std::size_t size>
void run_regular_deque_tests(const std::array<T, size>& values, const std::array<T, size>& source) {
  TestManager tm{ "Methods testing" };

#if DEFAULT_CTRO
  {
    BEGIN_TEST(tm, "Default constructor", "ds::Deque<T> dq;");

    ds::Deque<T> dq;

    EXPECT_EQ(dq.size(), 0);
    EXPECT_TRUE(dq.empty());
  }
#endif

#if FILL_CTRO
  {
    BEGIN_TEST(tm, "Fill constructor", "ds::Deque<T> dq(S, val);");

    ds::Deque<T> dq(size, 42);

    EXPECT_EQ(dq.size(), size);
    EXPECT_FALSE(dq.empty());

    for (std::size_t i{ 0 }; i < size; ++i) {
      EXPECT_EQ(dq[i], 42);
    }
  }
#endif

#if RANGE_CTRO
  {
    BEGIN_TEST(tm, "Range constructor", "ds::Deque<T> dq(source.begin(), source.end());");

    ds::Deque<T> dq(source.begin(), source.end());

    EXPECT_EQ(dq.size(), source.size());
    EXPECT_FALSE(dq.empty());

    for (std::size_t i{ 0 }; i < size; ++i) {
      EXPECT_EQ(dq[i], source[i]);
    }
  }
#endif

#if COPY_CTRO
  {
    BEGIN_TEST(tm, "Copy constructor", "ds::Deque<T> dq2(dq1);");

    ds::Deque<T> dq1(source.begin(), source.end());
    ds::Deque<T> dq2(dq1);

    EXPECT_EQ(dq2.size(), dq1.size());
    EXPECT_EQ(dq2.capacity(), dq1.capacity());
    EXPECT_FALSE(dq2.empty());

    for (std::size_t i{ 0 }; i < dq1.size(); ++i) {
      EXPECT_EQ(dq2[i], dq1[i]);
    }

    dq1[0] = 99;

    EXPECT_NE(dq2[0], dq1[0]);
  }
#endif

#if INIT_LIST_CTRO
  {
    BEGIN_TEST(tm, "Initializer list", "ds::Deque<T> dq{source[0], source[1], source[2], source[3], source[4]};");

    ds::Deque<T> dq{ source[0], source[1], source[2], source[3], source[4] };

    EXPECT_EQ(dq.size(), 5);
    EXPECT_FALSE(dq.empty());

    for (std::size_t i{ 0 }; i < size; ++i) {
      EXPECT_EQ(dq[i], source[i]);
    }
  }
#endif

#if ASSIGNMENT_COPY_OP
  {
    BEGIN_TEST(tm, "Copy assignment", "dq2 = dq1;");

    ds::Deque<T> dq1{ source[0], source[1], source[2], source[3], source[4] };
    ds::Deque<T> dq2;

    dq2 = dq1;

    EXPECT_EQ(dq2.size(), dq1.size());
    EXPECT_EQ(dq2.capacity(), dq1.capacity());
    EXPECT_FALSE(dq2.empty());

    dq2[1] = 100;

    EXPECT_NE(dq2[1], dq1[1]);
  }
#endif

  tm.summary();
}

#endif //!< DEQUE_METHODS_TESTS_HPP
