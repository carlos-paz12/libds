#ifndef DEQUE_METHODS_TESTS_HPP
#define DEQUE_METHODS_TESTS_HPP

#include <array>   // std::array
#include <cstddef> // std::size_t
#include <iterator>

#include "ds/deque.hpp"     // ds::Deque
#include "test_manager.hpp" // TestManager

// ==========================================
// [*] Test Configuration Flags
// Use YES or NO to enable/disable each test.
// ==========================================
#define YES 1
#define NO 0

// [!] Test the construction of an empty Deque.
#define DEFAULT_CTRO YES
// [!] Test the construction of a Deque with `n` elements.
#define FILL_CTRO YES
// [!] Test the construction of a Deque from a given interval.
#define RANGE_CTRO YES
// [!] Test the construction of a Deque from another Deque.
#define COPY_CTRO YES
// [!] Test the construction of a Deque from an initializer list.
#define INIT_LIST_CTRO YES
// [!] Test the assignment of a Deque.
#define ASSIGN_OP YES
// [!] Test the size of a Deque.
#define SIZE YES
// [!] Test the resizing of a Deque.
#define RESIZE YES
// [!] Test the capacity of a Deque.
#define CAPACITY YES
// [!] Test the empty state of a Deque.
#define EMPTY YES
// [!] Test the reduction of a Deque's capacity.
#define SHRINK_TO_FIT YES
// [!] Test the access to the first element of a Deque.
#define FRONT YES
// [!] Test the access to the first element of a const Deque.
#define FRONT_CONST YES
// [!] Test the access to the last element of a Deque.
#define BACK YES
// [!] Test the access to the last element of a const Deque.
#define BACK_CONST YES
// [!] Test the assignment of a Deque using the assign() method.
#define ASSIGN_COUNT YES
// [!] Test the assignment of a Deque from an initializer list using assign().
#define ASSIGN_INIT_LIST YES
// [!] Test the assignment of a Deque from a range using assign().
#define ASSIGN_RANGE YES
// [!] Test inserting an element at the front of a Deque.
#define PUSH_FRONT YES
// [!] Test inserting an element at the back of a Deque.
#define PUSH_BACK YES
// [!] Test removing the first element of a Deque.
#define POP_FRONT YES
// [!] Test removing the last element of a Deque.
#define POP_BACK YES
// [!] Test inserting an element at a specific position in a Deque.
#define INSERT YES
// [!] Test inserting multiple copies of an element at a position in a Deque.
#define INSERT_FILL YES
// [!] Test inserting elements from an initializer list into a Deque.
#define INSERT_INIT_LIST YES
// [!] Test inserting a range of elements into a Deque.
#define INSERT_RANGE YES
// [!] Test erasing an element at a specific position in a Deque.
#define ERASE YES
// [!] Test erasing an element at a specific position in a const Deque.
#define ERASE_CONST YES
// [!] Test erasing a range of elements from a Deque.
#define ERASE_RANGE YES
// [!] Test erasing a range of elements from a const Deque.
#define ERASE_RANGE_CONST YES
// [!] Test clearing all elements from a Deque.
#define CLEAR YES

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
    // {
    //   ds::Deque<T> deque1(size, src[0]);

    //   EXPECT_EQ(deque1.size(), size);
    //   EXPECT_FALSE(deque1.empty());

    //   const std::size_t expected_blocks1{ (size + 2) / 3 };
    //   EXPECT_GE(deque1.capacity(), expected_blocks1 * 3);

    //   for (std::size_t i{ 0 }; i < size; ++i) {
    //     EXPECT_EQ(deque1[i], src[0]);
    //   }
    // }
    // {
    //   ds::Deque<T, 3, 3> deque2(size, src[1]);

    //   EXPECT_EQ(deque2.size(), size);
    //   EXPECT_FALSE(deque2.empty());

    //   const std::size_t expected_blocks2{ std::max((size + 2) / 3, std::size_t{ 3 }) };
    //   EXPECT_GE(deque2.capacity(), expected_blocks2 * 3);

    //   for (std::size_t i{ 0 }; i < size; ++i) {
    //     EXPECT_EQ(deque2[i], src[1]);
    //   }
    // }
    // {
    //   ds::Deque<T> deque3(0, src[2]);

    //   EXPECT_EQ(deque3.size(), 0);
    //   EXPECT_TRUE(deque3.empty());
    //   EXPECT_GE(deque3.capacity(), 3);
    // }
    // {
    //   ds::Deque<T, 5, 2> deque4(5, src[2]);

    //   EXPECT_EQ(deque4.size(), 5);
    //   EXPECT_FALSE(deque4.empty());
    //   EXPECT_GE(deque4.capacity(), 5);

    //   for (std::size_t i = 0; i < 5; ++i) {
    //     EXPECT_EQ(deque4[i], src[2]);
    //   }
    // }
    {
      ds::Deque<T, 4, 1> deque5(8, src[3]);

      EXPECT_EQ(deque5.size(), 8);
      EXPECT_FALSE(deque5.empty());
      EXPECT_GE(deque5.capacity(), 8);

      for (std::size_t i = 0; i < 8; ++i) {
        EXPECT_EQ(deque5[i], src[3]);
      }
    }
  }
#endif

#if RANGE_CTRO
  {
    BEGIN_TEST(tmanager, "Range constructor", "ds::Deque<T> deque(src.begin(), src.end());");
    {
      ds::Deque<T> deque1(src.begin(), src.end());

      EXPECT_EQ(deque1.size(), src.size());
      EXPECT_FALSE(deque1.empty());

      const std::size_t expected_blocks1{ (src.size() + 2) / 3 };
      EXPECT_GE(deque1.capacity(), expected_blocks1 * 3);

      for (std::size_t i{ 0 }; i < src.size(); ++i) {
        EXPECT_EQ(deque1[i], src[i]);
      }
    }
    {
      ds::Deque<T, 3, 3> deque2(src.begin(), src.end());

      EXPECT_EQ(deque2.size(), src.size());
      EXPECT_FALSE(deque2.empty());

      const std::size_t expected_blocks2{ std::max((src.size() + 2) / 3, std::size_t{ 3 }) };
      EXPECT_GE(deque2.capacity(), expected_blocks2 * 3);

      for (std::size_t i{ 0 }; i < src.size(); ++i) {
        EXPECT_EQ(deque2[i], src[i]);
      }
    }
    {
      ds::Deque<T> deque3(src.begin(), src.begin());

      EXPECT_EQ(deque3.size(), 0);
      EXPECT_TRUE(deque3.empty());
      EXPECT_GE(deque3.capacity(), 3);
    }
    {
      ds::Deque<T, 5, 2> deque4(src.begin(), src.end());

      EXPECT_EQ(deque4.size(), src.size());
      EXPECT_FALSE(deque4.empty());
      EXPECT_GE(deque4.capacity(), ((src.size() + 4) / 5) * 5);

      for (std::size_t i = 0; i < src.size(); ++i) {
        EXPECT_EQ(deque4[i], src[i]);
      }
    }
    {
      ds::Deque<T, 4, 1> deque5(src.begin(), src.end());

      EXPECT_EQ(deque5.size(), src.size());
      EXPECT_FALSE(deque5.empty());
      EXPECT_GE(deque5.capacity(), ((src.size() + 3) / 4) * 4);

      for (std::size_t i = 0; i < src.size(); ++i) {
        EXPECT_EQ(deque5[i], src[i]);
      }
    }
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

    ds::Deque<T> deque;

    for (std::size_t i = 0; i < size; ++i) {
      deque.push_front(src[i]);
    }

    deque.resize(3);
    EXPECT_EQ(deque.size(), 3);
    EXPECT_EQ(deque[0], src[size - 1]);
    EXPECT_EQ(deque[1], src[size - 2]);
    EXPECT_EQ(deque[2], src[size - 3]);

    deque.resize(6);
    EXPECT_EQ(deque.size(), 6);
    EXPECT_EQ(deque[3], T());
    EXPECT_EQ(deque[4], T());
    EXPECT_EQ(deque[5], T());

    auto old_size = deque.size();
    deque.resize(old_size);
    EXPECT_EQ(deque.size(), old_size);

    deque.resize(0);
    EXPECT_EQ(deque.size(), 0);
    EXPECT_TRUE(deque.empty());

    deque.resize(2);
    EXPECT_EQ(deque.size(), 2);
    EXPECT_EQ(deque[0], T());
    EXPECT_EQ(deque[1], T());
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
  {
    BEGIN_TEST(tmanager, "Shrink to fit", "deque.shrink_to_fit();");

    {
      ds::Deque<T, 3, 3> deque;
      deque.push_back(src[0]);
      deque.push_back(src[1]);

      const auto old_size{ deque.size() };
      const auto old_front{ deque.front() };
      const auto old_back{ deque.back() };
      const auto old_capacity{ deque.capacity() };

      deque.shrink_to_fit();

      EXPECT_EQ(deque.size(), old_size);
      EXPECT_EQ(deque.front(), old_front);
      EXPECT_EQ(deque.back(), old_back);
      EXPECT_LE(deque.capacity(), old_capacity);
    }

    {
      ds::Deque<T, 3, 2> deque;

      for (std::size_t i = 0; i < 2 * size; ++i) {
        deque.push_back(src[i % size]);
      }

      const auto old_size{ deque.size() };
      const auto old_capacity{ deque.capacity() };
      const auto old_elements = [&]() {
        std::vector<T> elements;
        for (const auto& el : deque) elements.push_back(el);
        return elements;
      }();

      deque.shrink_to_fit();

      EXPECT_EQ(deque.size(), old_size);
      EXPECT_LE(deque.capacity(), old_capacity);

      for (std::size_t i = 0; i < old_size; ++i) {
        EXPECT_EQ(deque[i], old_elements[i]);
      }

      deque.push_back(src[0]);
      EXPECT_EQ(deque.back(), src[0]);
      deque.push_front(src[1]);
      EXPECT_EQ(deque.front(), src[1]);
    }

    {
      ds::Deque<T, 3, 3> deque;
      const auto old_capacity{ deque.capacity() };

      deque.shrink_to_fit();

      EXPECT_EQ(deque.size(), 0);
      EXPECT_LE(deque.capacity(), old_capacity);
      EXPECT_TRUE(deque.empty());
    }
  }
#endif

#if FRONT
  {
    BEGIN_TEST(tmanager, "Front", "deque.front();");

    ds::Deque<T, 3, 3> deque;

    for (std::size_t i = 0; i < size; ++i) {
      deque.push_back(src[i]);
    }

    EXPECT_EQ(deque.front(), src[0]);

    deque.front() = deque.back();
    EXPECT_NE(deque.front(), src[0]);
  }
#endif

#if FRONT_CONST
  {
    BEGIN_TEST(tmanager, "Front const", "const_deque.front();");

    ds::Deque<T, 3, 3> deque;

    for (std::size_t i = 0; i < size; ++i) {
      deque.push_back(src[i]);
    }

    const ds::Deque<T, 3, 3>& const_deque = deque;
    EXPECT_EQ(const_deque.front(), src[0]);
  }
#endif

#if BACK
  {
    BEGIN_TEST(tmanager, "Back", "deque.back();");

    ds::Deque<T, 3, 3> deque;

    for (std::size_t i = 0; i < size; ++i) {
      deque.push_back(src[i]);
    }

    EXPECT_EQ(deque.back(), src.back());

    deque.back() = deque.front();
    EXPECT_NE(deque.back(), src.back());
  }
#endif

#if BACK_CONST
  {
    BEGIN_TEST(tmanager, "Back const", "const_deque.back();");

    ds::Deque<T, 3, 3> deque;

    for (std::size_t i = 0; i < size; ++i) {
      deque.push_back(src[i]);
    }

    const ds::Deque<T, 3, 3>& const_deque = deque;
    EXPECT_EQ(const_deque.back(), src.back());
  }
#endif

#if ASSIGN_COUNT
  {
    BEGIN_TEST(tmanager, "Assign count", "deque.assign(count, value);");

    ds::Deque<T> deque;
    deque.assign(size, src[0]);

    EXPECT_EQ(deque.size(), src.size());
    for (std::size_t i = 0; i < deque.size(); ++i) {
      EXPECT_EQ(deque[i], src[0]);
    }

    deque.assign(size, src[1]);

    EXPECT_EQ(deque.size(), src.size());
    for (std::size_t i = 0; i < deque.size(); ++i) {
      EXPECT_NE(deque[i], src[0]);
      EXPECT_EQ(deque[i], src[1]);
    }
  }
#endif

#if ASSIGN_INIT_LIST
  {
    BEGIN_TEST(tmanager, "Assign initializer list", "deque.assign({src[0], src[1], src[2], src[3], src[4]});");

    ds::Deque<T> deque;

    deque.assign({ src[0], src[1], src[2], src[3], src[4] });

    EXPECT_EQ(deque.size(), 5);
    for (std::size_t i = 0; i < 5; ++i) {
      EXPECT_EQ(deque[i], src[i]);
    }

    deque.assign({ src[4], src[3], src[2], src[1], src[0] });

    EXPECT_EQ(deque.size(), 5);
    for (std::size_t i = 0; i < 5; ++i) {
      EXPECT_EQ(deque[i], src[4 - i]);
    }
  }
#endif

#if ASSIGN_RANGE
  {
    BEGIN_TEST(tmanager, "Assign range", "deque.assign(src.begin(), src.end());");

    ds::Deque<T> deque;

    deque.assign(src.begin(), src.end());

    EXPECT_EQ(deque.size(), src.size());
    for (std::size_t i = 0; i < src.size(); ++i) {
      EXPECT_EQ(deque[i], src[i]);
    }

    deque.assign(src.rbegin(), src.rend());

    EXPECT_EQ(deque.size(), src.size());
    for (std::size_t i = 0; i < src.size(); ++i) {
      EXPECT_EQ(deque[i], src[src.size() - i - 1]);
    }
  }
#endif

#if PUSH_FRONT
  {
    BEGIN_TEST(tmanager, "Push front", "deque.push_front(value);");

    ds::Deque<T, 3, 3> deque;

    for (std::size_t i = 0; i < size; ++i) {
      deque.push_front(src[i]);
      EXPECT_EQ(deque.front(), src[i]);
    }

    EXPECT_EQ(deque.size(), src.size());

    for (std::size_t i = 0; i < size; ++i) {
      EXPECT_EQ(deque[i], src[size - i - 1]);
    }
  }
#endif

#if PUSH_BACK
  {
    BEGIN_TEST(tmanager, "Push back", "deque.push_back(value);");

    ds::Deque<T, 3, 3> deque;

    for (std::size_t i = 0; i < size; ++i) {
      deque.push_back(src[i]);
      EXPECT_EQ(deque.back(), src[i]);
    }

    EXPECT_EQ(deque.size(), src.size());

    for (std::size_t i = 0; i < size; ++i) {
      EXPECT_EQ(deque[i], src[i]);
    }
  }
#endif

#if POP_FRONT
  {
    BEGIN_TEST(tmanager, "Pop front", "deque.pop_front();");

    ds::Deque<T, 3, 3> deque;

    for (std::size_t i = 0; i < size; ++i) {
      deque.push_back(src[i]);
    }

    EXPECT_EQ(deque.size(), src.size());

    T first_val = deque.front();
    deque.pop_front();
    EXPECT_NE(deque.front(), first_val);
    EXPECT_EQ(deque.size(), src.size() - 1);

    while (!deque.empty()) {
      deque.pop_front();
    }

    EXPECT_TRUE(deque.empty());

    deque.pop_front();
    EXPECT_TRUE(deque.empty());
  }
#endif

#if POP_BACK
  {
    BEGIN_TEST(tmanager, "Pop back", "deque.pop_back();");

    ds::Deque<T, 3, 3> deque;

    for (std::size_t i = 0; i < size; ++i) {
      deque.push_back(src[i]);
    }

    EXPECT_EQ(deque.size(), src.size());

    T last_val = deque.back();
    deque.pop_back();
    EXPECT_NE(deque.back(), last_val);
    EXPECT_EQ(deque.size(), src.size() - 1);

    while (not deque.empty()) {
      deque.pop_back();
    }

    EXPECT_TRUE(deque.empty());

    deque.pop_back();
    EXPECT_TRUE(deque.empty());
  }
#endif

#if INSERT
  {
    BEGIN_TEST(tmanager, "Insert", "deque.insert(cpos, val);");

    ds::Deque<T, 3, 3> deque1;

    deque1.insert(deque1.cbegin(), src[0]);
    EXPECT_EQ(deque1[0], src[0]);
    EXPECT_EQ(deque1.size(), 1);

    deque1.insert(deque1.cbegin(), src[1]);
    EXPECT_EQ(deque1[0], src[1]);
    EXPECT_EQ(deque1.size(), 2);

    deque1.insert(deque1.cbegin(), src[2]);
    EXPECT_EQ(deque1[0], src[2]);
    EXPECT_EQ(deque1.size(), 3);

    deque1.insert(deque1.cend(), src[3]);
    EXPECT_EQ(deque1[3], src[3]);
    EXPECT_EQ(deque1.size(), 4);

    deque1.insert(deque1.cend(), src[4]);
    EXPECT_EQ(deque1[4], src[4]);
    EXPECT_EQ(deque1.size(), 5);

    deque1.insert(deque1.cend(), src[2]);
    EXPECT_EQ(deque1[5], src[2]);
    EXPECT_EQ(deque1.size(), 6);

    deque1.insert(deque1.cend(), src[3]);
    EXPECT_EQ(deque1[6], src[3]);
    EXPECT_EQ(deque1.size(), 7);
  }
#endif

#if INSERT_FILL
  {
    BEGIN_TEST(tmanager, "Insert fill", "deque.insert(cpos, count, value);");

    ds::Deque<T, 3, 3> deque1;

    deque1.insert(deque1.cbegin(), 3, src[0]);
    EXPECT_EQ(deque1.size(), 3);
    EXPECT_EQ(deque1[0], src[0]);
    EXPECT_EQ(deque1[1], src[0]);
    EXPECT_EQ(deque1[2], src[0]);

    deque1.insert(deque1.cend(), 2, src[1]);
    EXPECT_EQ(deque1.size(), 5);
    EXPECT_EQ(deque1[3], src[1]);
    EXPECT_EQ(deque1[4], src[1]);
  }
#endif

#if INSERT_INIT_LIST
  {
    BEGIN_TEST(tmanager, "Insert initializer list", "deque.insert(cpos, {1, 2, 3});");

    ds::Deque<T, 3, 3> deque1;

    deque1.insert(deque1.cbegin(), { src[0], src[1], src[2] });
    EXPECT_EQ(deque1.size(), 3);
    EXPECT_EQ(deque1[0], src[0]);
    EXPECT_EQ(deque1[1], src[1]);
    EXPECT_EQ(deque1[2], src[2]);

    deque1.insert(deque1.cend(), { src[3], src[4] });
    EXPECT_EQ(deque1.size(), 5);
    EXPECT_EQ(deque1[3], src[3]);
    EXPECT_EQ(deque1[4], src[4]);
  }
#endif

#if INSERT_RANGE
  {
    BEGIN_TEST(tmanager, "Insert range", "deque.insert(cpos, src.begin(), src.end());");

    ds::Deque<T, 3, 3> values = { src[0], src[1], src[2], src[3], src[4] };
    ds::Deque<T, 3, 3> deque1;

    deque1.insert(deque1.cbegin(), values.begin(), values.end());
    EXPECT_EQ(deque1.size(), values.size());
    EXPECT_EQ(deque1[0], src[0]);
    EXPECT_EQ(deque1[1], src[1]);
    EXPECT_EQ(deque1[2], src[2]);
    EXPECT_EQ(deque1[3], src[3]);
    EXPECT_EQ(deque1[4], src[4]);

    deque1.insert(deque1.cend(), values.begin(), values.end());
    EXPECT_EQ(deque1.size(), values.size() * 2);
    EXPECT_EQ(deque1[5], src[0]);
    EXPECT_EQ(deque1[6], src[1]);
    EXPECT_EQ(deque1[7], src[2]);
    EXPECT_EQ(deque1[8], src[3]);
    EXPECT_EQ(deque1[9], src[4]);
  }
#endif

#if ERASE
  {
    BEGIN_TEST(tmanager, "Erase", "deque.erase(iterator);");

    ds::Deque<T, 3, 3> deque1;

    for (std::size_t i{ 0 }; i < size; ++i) {
      deque1.insert(deque1.cbegin(), src[i]);
    }

    EXPECT_EQ(deque1.size(), src.size());

    T old_front = deque1[0];
    deque1.erase(deque1.begin());
    EXPECT_NE(deque1[0], old_front);
    EXPECT_EQ(deque1.size(), src.size() - 1);

    T old_back = deque1[deque1.size() - 1];
    auto it_back = deque1.erase(deque1.end() - 1);
    EXPECT_EQ(it_back, deque1.end());
    EXPECT_NE(deque1[deque1.size() - 1], old_back);
    EXPECT_EQ(deque1.size(), src.size() - 2);

    auto middle_it = deque1.begin() + (deque1.size() / 2);
    T middle_val = *middle_it;
    deque1.erase(middle_it);
    EXPECT_NE(deque1[deque1.size() / 2], middle_val);
    EXPECT_EQ(deque1.size(), src.size() - 3);

    ds::Deque<T, 3, 3> deque_single;
    deque_single.push_back(src[0]);
    EXPECT_EQ(deque_single.size(), 1);
    auto it_single = deque_single.erase(deque_single.begin());
    EXPECT_EQ(deque_single.size(), 0);
    EXPECT_EQ(it_single, deque_single.end());

    ds::Deque<T, 3, 3> deque2;
    auto it2 = deque2.erase(deque2.end());
    EXPECT_EQ(it2, deque2.end());
  }
#endif

#if ERASE_CONST
  {
    BEGIN_TEST(tmanager, "Erase const", "deque.erase(const_iterator);");

    ds::Deque<T, 3, 3> deque1;

    for (std::size_t i{ 0 }; i < size; ++i) {
      deque1.insert(deque1.cbegin(), src[i]);
    }

    EXPECT_EQ(deque1.size(), src.size());

    T old_front = deque1[0];
    deque1.erase(deque1.cbegin());
    EXPECT_NE(deque1[0], old_front);
    EXPECT_EQ(deque1.size(), src.size() - 1);

    T old_back = deque1[deque1.size() - 1];
    auto it_back = deque1.erase(deque1.cend() - 1);
    EXPECT_EQ(it_back, deque1.end());
    EXPECT_NE(deque1[deque1.size() - 1], old_back);
    EXPECT_EQ(deque1.size(), src.size() - 2);

    auto middle_it = deque1.cbegin() + (deque1.size() / 2);
    T middle_val = *middle_it;
    deque1.erase(middle_it);
    EXPECT_NE(deque1[deque1.size() / 2], middle_val);
    EXPECT_EQ(deque1.size(), src.size() - 3);

    ds::Deque<T, 3, 3> deque_single;
    deque_single.push_back(src[0]);
    EXPECT_EQ(deque_single.size(), 1);
    auto it_single = deque_single.erase(deque_single.cbegin());
    EXPECT_EQ(deque_single.size(), 0);
    EXPECT_EQ(it_single, deque_single.end());

    ds::Deque<T, 3, 3> deque2;
    auto it2 = deque2.erase(deque2.cend());
    EXPECT_EQ(it2, deque2.end());
  }
#endif

#if ERASE_RANGE
  {
    BEGIN_TEST(tmanager, "Erase range", "deque.erase(iterator, iterator);");

    ds::Deque<T, 3, 3> deque1;

    auto it = deque1.erase(deque1.begin(), deque1.begin());
    EXPECT_EQ(it, deque1.begin());

    for (std::size_t i{ 0 }; i < size; ++i) {
      deque1.push_back(src[i]);
    }

    deque1.erase(deque1.begin(), deque1.begin() + 2);
    EXPECT_TRUE(deque1.size() < src.size());
    EXPECT_EQ(deque1.size(), src.size() - 2);
    EXPECT_EQ(deque1[0], src[2]);
  }
#endif

#if ERASE_RANGE_CONST
  {
    BEGIN_TEST(tmanager, "Erase range const", "deque.erase(const_iterator, const_iterator);");

    ds::Deque<T, 3, 3> deque1;

    auto it = deque1.erase(deque1.begin(), deque1.begin());
    EXPECT_EQ(it, deque1.begin());

    for (std::size_t i{ 0 }; i < size; ++i) {
      deque1.push_back(src[i]);
    }

    deque1.erase(deque1.cbegin(), deque1.cbegin() + 2);
    EXPECT_EQ(deque1.size(), src.size() - 2);
    EXPECT_EQ(deque1[0], src[2]);
  }
#endif

#if CLEAR
  {
    BEGIN_TEST(tmanager, "Clear", "deque.clear();");

    ds::Deque<T, 3, 3> deque;

    for (std::size_t i{ 0 }; i < size; ++i) {
      deque.push_back(src[i]);
    }

    auto old_capacity{ deque.capacity() };
    deque.clear();

    EXPECT_EQ(deque.size(), 0);
    EXPECT_EQ(deque.capacity(), old_capacity);
    EXPECT_EQ(deque.begin(), deque.end());
  }
#endif

  tmanager.summary();
}

#endif // DEQUE_METHODS_TESTS_HPP
