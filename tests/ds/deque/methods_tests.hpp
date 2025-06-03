#ifndef DEQUE_METHODS_TESTS_HPP
#define DEQUE_METHODS_TESTS_HPP

#include <array>   // std::array
#include <cstddef> // std::size_t

#include "ds/deque.hpp"     // ds::Deque
#include "test_manager.hpp" // TestManager

// ==========================================
// [*] Test Configuration Flags
// Use YES or NO to enable/disable each test.
// ==========================================
#define YES 1
#define NO 0

#define DEFAULT_CTRO NO       // [!] Test the construction of an empty Deque.
#define FILL_CTRO NO          // [!] Test the construction of a Deque with `n` elements.
#define RANGE_CTRO NO         // [!] Test the construction of a Deque from a given interval.
#define COPY_CTRO NO          // [!] Test the construction of a Deque from another Deque.
#define INIT_LIST_CTRO NO     // [!] Test the construction of a Deque from an initializer list.
#define ASSIGN_OP NO          // [!] Test the assignment of a Deque.
#define SIZE YES              // [!] Test the size of a Deque.
#define RESIZE NO             // [!] Test the resizing of a Deque.
#define CAPACITY YES          // [!] Test the capacity of a Deque.
#define EMPTY YES             // [!] Test the empty state of a Deque.
#define SHRINK_TO_FIT YES     // [!] Test the reduction of a Deque's capacity.
#define FRONT YES             // [!] Test the access to the first element of a Deque.
#define FRONT_CONST YES       // [!] Test the access to the first element of a const Deque.
#define BACK YES              // [!] Test the access to the last element of a Deque.
#define BACK_CONST YES        // [!] Test the access to the last element of a const Deque.
#define ASSIGN YES            // [!] Test the assignment of a Deque using the assign() method.
#define ASSIGN_INIT_LIST YES  // [!] Test the assignment of a Deque from an initializer list using assign().
#define ASSIGN_RANGE YES      // [!] Test the assignment of a Deque from a range using assign().
#define PUSH_FRONT YES        // [!] Test inserting an element at the front of a Deque.
#define PUSH_BACK YES         // [!] Test inserting an element at the back of a Deque.
#define POP_FRONT YES         // [!] Test removing the first element of a Deque.
#define POP_BACK YES          // [!] Test removing the last element of a Deque.
#define INSERT YES            // [!] Test inserting an element at a specific position in a Deque.
#define INSERT_FILL YES       // [!] Test inserting multiple copies of an element at a position in a Deque.
#define INSERT_INIT_LIST YES  // [!] Test inserting elements from an initializer list into a Deque.
#define INSERT_RANGE YES      // [!] Test inserting a range of elements into a Deque.
#define ERASE YES             // [!] Test erasing an element at a specific position in a Deque.
#define ERASE_CONST YES       // [!] Test erasing an element at a specific position in a const Deque.
#define ERASE_RANGE YES       // [!] Test erasing a range of elements from a Deque.
#define ERASE_RANGE_CONST YES // [!] Test erasing a range of elements from a const Deque.
#define CLEAR YES             // [!] Test clearing all elements from a Deque.

template<typename T, std::size_t size>
void run_regular_deque_tests(const std::array<T, size>& src) {
  TestManager tmanager{ "Methods testing" };

#if DEFAULT_CTRO
  {
    BEGIN_TEST(tmanager, "Default constructor", "ds::Deque<T> deque;");

    ds::Deque<T> deque;

    EXPECT_EQ(deque.size(), 0);
    EXPECT_TRUE(deque.empty());
  }
#endif

#if FILL_CTRO
  {
    BEGIN_TEST(tmanager, "Fill constructor", "ds::Deque<T> deque(size, val);");

    ds::Deque<T> deque(size, 42);

    EXPECT_EQ(deque.size(), size);
    EXPECT_FALSE(deque.empty());

    for (std::size_t i{ 0 }; i < size; ++i) EXPECT_EQ(deque[i], 42);
  }
#endif

#if RANGE_CTRO
  {
    BEGIN_TEST(tmanager, "Range constructor", "ds::Deque<T> deque(src.begin(), src.end());");

    ds::Deque<T> deque(src.begin(), src.end());

    EXPECT_EQ(deque.size(), src.size());
    EXPECT_FALSE(deque.empty());

    for (std::size_t i{ 0 }; i < size; ++i) EXPECT_EQ(deque[i], src[i]);

    deque[0] = 100;
    EXPECT_NE(deque[0], src[0]);
  }
#endif

#if COPY_CTRO
  {
    BEGIN_TEST(tmanager, "Copy constructor", "ds::Deque<T> deque2(deque1);");

    ds::Deque<T> deque1(src.begin(), src.end());
    ds::Deque<T> deque2(deque1);

    EXPECT_EQ(deque2.size(), deque1.size());
    EXPECT_EQ(deque2.capacity(), deque1.capacity());
    EXPECT_FALSE(deque2.empty());

    for (std::size_t i{ 0 }; i < deque1.size(); ++i) EXPECT_EQ(deque2[i], deque1[i]);

    deque1[0] = 99;
    EXPECT_NE(deque2[0], deque1[0]);
  }
#endif

#if INIT_LIST_CTRO
  {
    BEGIN_TEST(tmanager, "Initializer list", "ds::Deque<T> deque({src[0], src[1], src[2], src[3], src[4]});");

    ds::Deque<T> deque({ src[0], src[1], src[2], src[3], src[4] });

    EXPECT_EQ(deque.size(), 5);
    EXPECT_FALSE(deque.empty());

    for (std::size_t i{ 0 }; i < size; ++i) EXPECT_EQ(deque[i], src[i]);

    deque[0] = 100;
    EXPECT_NE(deque[0], src[0]);
  }
#endif

#if ASSIGN_OP
  {
    BEGIN_TEST(tmanager, "Copy assignment", "deque2 = deque1;");

    ds::Deque<T> deque1({ src[0], src[1], src[2], src[3], src[4] });
    ds::Deque<T> deque2;

    deque2 = deque1;

    EXPECT_EQ(deque2.size(), deque1.size());
    EXPECT_EQ(deque2.capacity(), deque1.capacity());
    EXPECT_FALSE(deque2.empty());

    deque2[1] = 100;
    EXPECT_NE(deque2[1], deque1[1]);
  }
#endif

#if SIZE
  {
    BEGIN_TEST(tmanager, "Size", "deque.size();");

    ds::Deque<T> deque;
    EXPECT_EQ(deque.size(), 0);

    ds::Deque<T> deque2(src.begin(), src.end());
    EXPECT_EQ(deque2.size(), src.size());
  }
#endif

#if RESIZE
  {
    BEGIN_TEST(tmanager, "Resize", "deque.resize(new_size);");

    ds::Deque<T> deque({ src[0], src[1], src[2], src[3], src[4] });

    deque.resize(3);
    EXPECT_EQ(deque.size(), 3);
    EXPECT_EQ(deque[0], src[0]);
    EXPECT_EQ(deque[1], src[1]);
    EXPECT_EQ(deque[2], src[2]);

    deque.resize(6);
    EXPECT_EQ(deque.size(), 6);

    EXPECT_EQ(deque[0], src[0]);
    EXPECT_EQ(deque[1], src[1]);
    EXPECT_EQ(deque[2], src[2]);
    EXPECT_EQ(deque[3], T());
    EXPECT_EQ(deque[4], T());
    EXPECT_EQ(deque[5], T());

    auto old_size{ deque.size() };
    deque.resize(deque.size());
    EXPECT_EQ(deque.size(), old_size);
  }
#endif

#if CAPACITY
  {
    BEGIN_TEST(tmanager, "Capacity", "deque.capacity();");

    ds::Deque<T> deque1;
    EXPECT_EQ(deque1.capacity(), 3);

    ds::Deque<T, 4, 2> deque2;
    EXPECT_EQ(deque2.capacity(), 8);
  }
#endif

#if EMPTY
  {
    BEGIN_TEST(tmanager, "Empty", "deque.empty();");

    ds::Deque<T> deque;
    EXPECT_TRUE(deque.empty());

    ds::Deque<T> deque2(src.begin(), src.end());
    EXPECT_FALSE(deque2.empty());
  }
#endif

#if SHRINK_TO_FIT
#endif

#if FRONT
#endif

#if FRONT_CONST
#endif

#if BACK
#endif

#if BACK_CONST
#endif

#if ASSIGN
#endif

#if ASSIGN_INIT_LIST
#endif

#if ASSIGN_RANGE
#endif

#if PUSH_FRONT
#endif

#if PUSH_BACK
#endif

#if POP_FRONT
#endif

#if POP_BACK
#endif

#if INSERT
  {
    BEGIN_TEST(tmanager, "Insert", "deque.insert(cpos, val);");

    ds::Deque<T> deque;

    deque.insert(deque.begin(), 10);
    EXPECT_EQ(deque[0], 10);
    EXPECT_EQ(deque.size(), 1);

    deque.insert(deque.begin(), 20);
    EXPECT_EQ(deque[0], 20);
    EXPECT_EQ(deque[1], 10);
    EXPECT_EQ(deque.size(), 2);

    deque.insert(deque.end(), 30);
    EXPECT_EQ(deque[0], 20);
    EXPECT_EQ(deque[1], 10);
    EXPECT_EQ(deque[2], 30);
    EXPECT_EQ(deque.size(), 3);

    deque.insert(deque.begin() + 1, 40);
    EXPECT_EQ(deque[0], 20);
    EXPECT_EQ(deque[1], 40);
    EXPECT_EQ(deque[2], 10);
    EXPECT_EQ(deque[3], 30);
    EXPECT_EQ(deque.size(), 4);
  }
#endif

#if INSERT_FILL
#endif

#if INSERT_INIT_LIST
#endif

#if INSERT_RANGE
#endif

#if ERASE
#endif

#if ERASE_CONST
#endif

#if ERASE_RANGE
#endif

#if ERASE_RANGE_CONST
#endif

#if CLEAR
#endif

  tmanager.summary();
}

#endif // DEQUE_METHODS_TESTS_HPP
