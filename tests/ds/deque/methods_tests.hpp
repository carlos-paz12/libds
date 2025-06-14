#ifndef DEQUE_METHODS_TESTS_HPP
#define DEQUE_METHODS_TESTS_HPP

#include <array>   // std::array
#include <cstddef> // std::size_t
#include <iterator>
#include <ostream>

#include "ds/deque/deque.hpp" // ds::Deque
#include "test_manager.hpp"   // TestManager

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

template <typename T, std::size_t size>
void run_regular_deque_tests(const std::array<T, size> &src) {
  TestManager tmanager{"Methods testing"};

#if DEFAULT_CTRO
  {
    BEGIN_TEST(tmanager, "Default ctro with template default",
               "ds::Deque<T> deque();");

    ds::Deque<T> deque{};

    EXPECT_TRUE(deque.empty());
    EXPECT_EQ(deque.size(), 0);
    EXPECT_EQ(deque.capacity(), 3);
    EXPECT_EQ(deque.begin(), deque.end());
  }
  {
    BEGIN_TEST(tmanager, "Default ctro with template modifiers",
               "ds::Deque<T, BlockSize, MobSize> deque();");

    ds::Deque<T, 3, 3> deque{};

    EXPECT_TRUE(deque.empty());
    EXPECT_EQ(deque.size(), 0);
    EXPECT_EQ(deque.capacity(), 9);
    EXPECT_EQ(deque.begin(), deque.end());
  }
#endif

#if FILL_CTRO
  {
    BEGIN_TEST(tmanager, "Fill ctro with template default",
               "ds::Deque<T> deque(n, value);");

    ds::Deque<T> deque(src.size(), src[0]);

    EXPECT_FALSE(deque.empty());
    EXPECT_EQ(deque.size(), src.size());

    const std::size_t expected_capacity{(src.size() + 3) / 3};
    EXPECT_EQ(deque.capacity(), expected_capacity * 3);

    for (std::size_t i{0}; i < src.size(); ++i) {
      EXPECT_EQ(deque[i], src[0]);
    }

    EXPECT_LT(deque.begin(), deque.end());
  }
  {
    BEGIN_TEST(tmanager, "Fill ctro with template modifiers",
               "ds::Deque<T, BlockSize, MobSize> deque(n, value);");

    ds::Deque<T, 3, 3> deque(src.size(), src[1]);

    EXPECT_FALSE(deque.empty());
    EXPECT_EQ(deque.size(), src.size());

    const std::size_t expected_capacity{
        std::max((src.size() + 3) / 3, std::size_t{3})};
    EXPECT_GE(deque.capacity(), expected_capacity * 3);

    for (std::size_t i{0}; i < src.size(); ++i) {
      EXPECT_EQ(deque[i], src[1]);
    }

    EXPECT_LT(deque.begin(), deque.end());
  }
  {
    BEGIN_TEST(tmanager, "Fill ctro empty", "ds::Deque<T> deque(0, value);");

    ds::Deque<T> deque(0, src[2]);

    EXPECT_TRUE(deque.empty());
    EXPECT_EQ(deque.size(), 0);
    EXPECT_EQ(deque.capacity(), 3);
    EXPECT_EQ(deque.begin(), deque.end());
  }
  {
    BEGIN_TEST(tmanager, "Fill ctro with n < BlockSize",
               "ds::Deque<T, BlockSize, MobSize> deque(n, value);");

    std::size_t small_n{2};
    ds::Deque<T, 3, 3> deque(small_n, src[3]);

    EXPECT_EQ(deque.size(), small_n);

    const std::size_t expected_capacity{
        std::max((small_n + 3) / 3, std::size_t{3})};
    EXPECT_GE(deque.capacity(), expected_capacity * 3);

    for (std::size_t i = 0; i < small_n; ++i) {
      EXPECT_EQ(deque[i], src[3]);
    }
  }
  {
    BEGIN_TEST(tmanager, "Fill ctro without expansion",
               "ds::Deque<T, BlockSize, MobSize> deque(n, value);");

    std::size_t n{10};
    ds::Deque<T, 3, 5> deque(n, src[4]);

    EXPECT_EQ(deque.size(), n);

    const std::size_t expected_capacity{std::max((n + 3) / 3, std::size_t{5})};
    EXPECT_GE(deque.capacity(), expected_capacity * 3);

    for (std::size_t i = 0; i < n; ++i) {
      EXPECT_EQ(deque[i], src[4]);
    }
  }
#endif

#if RANGE_CTRO
  {
    BEGIN_TEST(tmanager, "Range ctro with default template",
               "ds::Deque<T> deque(first, last);");

    ds::Deque<T> deque(src.begin(), src.end());

    EXPECT_FALSE(deque.empty());
    EXPECT_EQ(deque.size(), src.size());

    const std::size_t expected_capacity{(src.size() + 3) / 3};
    EXPECT_EQ(deque.capacity(), expected_capacity * 3);

    for (std::size_t i = 0; i < src.size(); ++i) {
      EXPECT_EQ(deque[i], src[i]);
    }

    EXPECT_LT(deque.begin(), deque.end());
  }
  {
    BEGIN_TEST(tmanager, "Range ctro with template modifiers",
               "ds::Deque<T, BlockSize, MobSize> deque(first,last);");

    ds::Deque<T, 3, 3> deque(src.begin(), src.end());

    EXPECT_FALSE(deque.empty());
    EXPECT_EQ(deque.size(), src.size());

    const std::size_t expected_capacity{
        std::max((src.size() + 3) / 3, std::size_t{3})};
    EXPECT_GE(deque.capacity(), expected_capacity * 3);

    for (std::size_t i = 0; i < src.size(); ++i) {
      EXPECT_EQ(deque[i], src[i]);
    }

    EXPECT_LT(deque.begin(), deque.end());
  }
  {
    BEGIN_TEST(tmanager, "Range ctro empty",
               "ds::Deque<T> deque(first, first);");

    ds::Deque<T> deque(src.begin(), src.begin());

    EXPECT_TRUE(deque.empty());
    EXPECT_EQ(deque.size(), 0);
    EXPECT_EQ(deque.capacity(), 3);
    EXPECT_EQ(deque.begin(), deque.end());
  }
  {
    BEGIN_TEST(tmanager, "Range ctro with n < BlockSize",
               "ds::Deque<T, BlockSize, MobSize> deque(first, last);");

    std::size_t small_n{2};
    ds::Deque<T, 3, 3> deque(src.begin(), src.begin() + small_n);

    EXPECT_EQ(deque.size(), small_n);

    const std::size_t expected_capacity{
        std::max((small_n + 3) / 3, std::size_t{3})};
    EXPECT_GE(deque.capacity(), expected_capacity * 3);

    for (std::size_t i = 0; i < small_n; ++i) {
      EXPECT_EQ(deque[i], src[i]);
    }
  }
  {
    BEGIN_TEST(tmanager, "Range ctro without expansion",
               "ds::Deque<T, BlockSize, MobSize> deque(first, last);");

    std::size_t n{10};
    ds::Deque<T, 3, 5> deque(src.begin(), src.begin() + n);

    EXPECT_EQ(deque.size(), n);

    const std::size_t expected_capacity{std::max((n + 3) / 3, std::size_t{5})};
    EXPECT_GE(deque.capacity(), expected_capacity * 3);

    for (std::size_t i = 0; i < n; ++i) {
      EXPECT_EQ(deque[i], src[i]);
    }
  }
#endif

#if COPY_CTRO
  {
    BEGIN_TEST(tmanager, "Copy constructor with default template",
               "ds::Deque<T> deque(other);");

    ds::Deque<T> other(src.size(), src[0]);
    ds::Deque<T> deque(other);

    EXPECT_FALSE(deque.empty());
    EXPECT_EQ(deque.size(), other.size());
    EXPECT_EQ(deque.capacity(), other.capacity());

    for (std::size_t i = 0; i < src.size(); ++i) {
      EXPECT_EQ(deque[i], src[0]);
    }

    EXPECT_LT(deque.begin(), deque.end());
    EXPECT_EQ(std::distance(deque.begin(), deque.end()),
              static_cast<std::ptrdiff_t>(src.size()));
  }
  {
    BEGIN_TEST(tmanager, "Copy constructor with custom template",
               "ds::Deque<T, BlockSize, MobSize> deque(other);");

    ds::Deque<T, 5, 3> other(src.size(), src[1]);
    ds::Deque<T, 5, 3> deque(other);

    EXPECT_FALSE(deque.empty());
    EXPECT_EQ(deque.size(), other.size());
    EXPECT_EQ(deque.capacity(), other.capacity());

    for (std::size_t i = 0; i < src.size(); ++i) {
      EXPECT_EQ(deque[i], src[1]);
    }
  }
  {
    BEGIN_TEST(tmanager, "Copy constructor with empty deque",
               "ds::Deque<T> deque(empty);");

    ds::Deque<T> other(0, src[0]);
    ds::Deque<T> deque(other);

    EXPECT_TRUE(deque.empty());
    EXPECT_EQ(deque.size(), 0);
    EXPECT_GE(deque.capacity(), 3);
    EXPECT_EQ(deque.begin(), deque.end());
  }
  {
    BEGIN_TEST(tmanager, "Copy constructor iterator validity",
               "Verify iterators after copy");

    ds::Deque<T> other(5, src[2]);
    other.push_front(src[3]);
    other.push_back(src[4]);

    ds::Deque<T> deque(other);

    EXPECT_EQ(deque.front(), other.front());
    EXPECT_EQ(deque.back(), other.back());

    auto other_it{other.begin()};
    auto deque_it{deque.begin()};

    while (other_it != other.end()) {
      EXPECT_EQ(*deque_it, *other_it);
      ++other_it;
      ++deque_it;
    }
  }
  {
    BEGIN_TEST(tmanager, "Copy constructor with partial blocks",
               "Verify partial block copying");

    const std::size_t n = 7;
    ds::Deque<T> original(n, src[3]);

    ds::Deque<T> copy(original);

    EXPECT_EQ(copy.size(), n);
    EXPECT_GE(copy.capacity(), original.capacity());

    // Verify all elements
    for (std::size_t i = 0; i < n; ++i) {
      EXPECT_EQ(copy[i], src[3]);
    }
  }
#endif

#if INIT_LIST_CTRO
  {
    BEGIN_TEST(tmanager, "Initializer list",
               "ds::Deque<T> deque({src[0], src[1], src[2], src[3], src[4]});");

    ds::Deque<T> deque{src[0], src[1], src[2], src[3], src[4]};

    EXPECT_EQ(deque.size(), 5);
    EXPECT_FALSE(deque.empty());

    for (std::size_t i{0}; i < 5; ++i)
      EXPECT_EQ(deque[i], src[i]);

    deque[0] = 100;
    EXPECT_NE(deque[0], src[0]);
  }
#endif

#if ASSIGN_OP
  {
    BEGIN_TEST(tmanager, "Copy assignment", "deque2 = deque1;");

    ds::Deque<T> deque1({src[0], src[1], src[2], src[3], src[4]});
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
    BEGIN_TEST(tmanager, "Size on empty deque with fill constructor",
               "ds::Deque<T> deque(0, value);");

    ds::Deque<T> deque(0, src[0]);

    EXPECT_TRUE(deque.empty());
    EXPECT_EQ(deque.size(), 0);
    EXPECT_EQ(deque.capacity(), 3);
    EXPECT_EQ(deque.begin(), deque.end());
  }
  {
    BEGIN_TEST(tmanager, "Size on filled deque with default template",
               "ds::Deque<T> deque(n, value);");

    ds::Deque<T> deque(src.size(), src[0]);

    EXPECT_FALSE(deque.empty());
    EXPECT_EQ(deque.size(), src.size());

    const std::size_t expected_capacity{(src.size() + 3) / 3};
    EXPECT_EQ(deque.capacity(), expected_capacity * 3);
  }
  {
    BEGIN_TEST(tmanager, "Size on filled deque with template modifiers",
               "ds::Deque<T, BlockSize, MobSize> deque(n, value);");

    ds::Deque<T, 3, 4> deque(src.size(), src[1]);

    EXPECT_FALSE(deque.empty());
    EXPECT_EQ(deque.size(), src.size());

    const std::size_t expected_capacity{
        std::max((src.size() + 3) / 3, std::size_t{4})};
    EXPECT_GE(deque.capacity(), expected_capacity * 3);
  }
#endif

#if RESIZE
  {
    BEGIN_TEST(tmanager, "Resize", "deque.resize(new_size);");

    ds::Deque<T> deque;

    for (std::size_t i = 0; i < src.size(); ++i) {
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
    BEGIN_TEST(tmanager, "Capacity with default template",
               "ds::Deque<T> deque(n, value);");

    ds::Deque<T> deque(5, src[0]);

    const std::size_t expected_capacity{((5 + 3) / 3) * 3};
    EXPECT_EQ(deque.capacity(), expected_capacity);
  }
  {
    BEGIN_TEST(tmanager, "Capacity with template modifiers",
               "ds::Deque<T, BlockSize, MobSize> deque(n, value);");

    std::size_t n = 10;
    ds::Deque<T, 4, 2> deque(n, src[1]);

    const std::size_t expected_capacity{std::max((n + 4) / 4, std::size_t{2}) *
                                        4};
    EXPECT_EQ(deque.capacity(), expected_capacity);
  }
  {
    BEGIN_TEST(tmanager, "Capacity with n == 0",
               "ds::Deque<T> deque(0, value);");

    ds::Deque<T> deque(0, src[2]);

    EXPECT_EQ(deque.capacity(), 3);
  }
#endif

#if EMPTY
  {
    BEGIN_TEST(tmanager, "Empty with n == 0", "ds::Deque<T> deque(0, value);");

    ds::Deque<T> deque(0, src[0]);

    EXPECT_TRUE(deque.empty());
  }
  {
    BEGIN_TEST(tmanager, "Empty with n > 0", "ds::Deque<T> deque(n, value);");

    ds::Deque<T> deque(5, src[1]);

    EXPECT_FALSE(deque.empty());
  }
#endif

#if SHRINK_TO_FIT
  {
    BEGIN_TEST(tmanager, "ShrinkToFit after push_back",
               "deque.shrink_to_fit() after push_back");

    ds::Deque<T, 3, 3> deque;
    deque.push_back(src[0]);
    deque.push_back(src[1]);

    const auto old_size = deque.size();
    const auto old_front = deque.front();
    const auto old_back = deque.back();
    const auto old_capacity = deque.capacity();

    deque.shrink_to_fit();

    EXPECT_EQ(deque.size(), old_size);
    EXPECT_EQ(deque.front(), old_front);
    EXPECT_EQ(deque.back(), old_back);
    EXPECT_LE(deque.capacity(), old_capacity);
  }

  {
    BEGIN_TEST(tmanager, "ShrinkToFit after copy construction",
               "deque.shrink_to_fit() after copy");

    ds::Deque<T, 3, 2> other({src[0], src[1]});
    ds::Deque<T, 3, 2> deque(other);

    const auto other_capacity = other.capacity();
    deque.shrink_to_fit();

    EXPECT_EQ(deque.size(), other.size());
    EXPECT_LE(deque.capacity(), other_capacity);

    for (std::size_t i = 0; i < deque.size(); ++i) {
      EXPECT_EQ(deque[i], other[i]);
    }

    // Test if operations work after shrink
    deque.push_back(src[0]);
    EXPECT_EQ(deque.back(), src[0]);
    deque.push_front(src[1]);
    EXPECT_EQ(deque.front(), src[1]);
  }

  {
    BEGIN_TEST(tmanager, "ShrinkToFit on empty deque",
               "empty_deque.shrink_to_fit()");

    ds::Deque<T, 3, 3> deque;
    const auto old_capacity = deque.capacity();

    deque.shrink_to_fit();

    EXPECT_EQ(deque.size(), 0);
    EXPECT_LE(deque.capacity(), old_capacity);
    EXPECT_TRUE(deque.empty());
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

    const ds::Deque<T, 3, 3> &const_deque = deque;
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

    const ds::Deque<T, 3, 3> &const_deque = deque;
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
    BEGIN_TEST(tmanager, "Assign initializer list",
               "deque.assign({src[0], src[1], src[2], src[3], src[4]});");

    ds::Deque<T> deque;

    deque.assign({src[0], src[1], src[2], src[3], src[4]});

    EXPECT_EQ(deque.size(), 5);
    for (std::size_t i = 0; i < 5; ++i) {
      EXPECT_EQ(deque[i], src[i]);
    }

    deque.assign({src[4], src[3], src[2], src[1], src[0]});

    EXPECT_EQ(deque.size(), 5);
    for (std::size_t i = 0; i < 5; ++i) {
      EXPECT_EQ(deque[i], src[4 - i]);
    }
  }
#endif

#if ASSIGN_RANGE
  {
    BEGIN_TEST(tmanager, "Assign range",
               "deque.assign(src.begin(), src.end());");

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
    BEGIN_TEST(tmanager, "InsertFill at begin",
               "deque.insert(deque.cbegin(), count, value)");

    ds::Deque<T, 3, 3> deque;
    const auto insert_count = 3;

    deque.insert(deque.cbegin(), insert_count, src[0]);

    EXPECT_EQ(deque.size(), insert_count);
    for (std::size_t i = 0; i < insert_count; ++i) {
      EXPECT_EQ(deque[i], src[0]);
    }
  }

  {
    BEGIN_TEST(tmanager, "InsertFill at end",
               "deque.insert(deque.cend(), count, value)");

    ds::Deque<T, 3, 3> deque({src[0], src[0], src[0]});
    const auto initial_size = deque.size();
    const auto insert_count = 2;

    deque.insert(deque.cend(), insert_count, src[1]);

    EXPECT_EQ(deque.size(), initial_size + insert_count);
    for (std::size_t i = initial_size; i < deque.size(); ++i) {
      EXPECT_EQ(deque[i], src[1]);
    }
  }
#endif

#if INSERT_INIT_LIST
  {
    BEGIN_TEST(tmanager, "InsertInitList at begin",
               "deque.insert(deque.cbegin(), {values...})");

    ds::Deque<T, 3, 3> deque;
    const std::initializer_list<T> init_list = {src[0], src[1], src[2]};

    deque.insert(deque.cbegin(), init_list);

    EXPECT_EQ(deque.size(), init_list.size());
    std::size_t i = 0;
    for (const auto &value : init_list) {
      EXPECT_EQ(deque[i++], value);
    }
  }

  {
    BEGIN_TEST(tmanager, "InsertInitList at end",
               "deque.insert(deque.cend(), {values...})");

    ds::Deque<T, 3, 3> deque = {src[0], src[1], src[2]};
    const auto initial_size = deque.size();
    const std::initializer_list<T> append_list = {src[3], src[4]};

    deque.insert(deque.cend(), append_list);

    EXPECT_EQ(deque.size(), initial_size + append_list.size());
    std::size_t i = initial_size;
    for (const auto &value : append_list) {
      EXPECT_EQ(deque[i++], value);
    }
  }
#endif

#if INSERT_RANGE
  {
    BEGIN_TEST(tmanager, "InsertRange at begin",
               "deque.insert(deque.cbegin(), first, last)");

    ds::Deque<T, 3, 3> source({src[0], src[1], src[2], src[3], src[4]});
    ds::Deque<T, 3, 3> deque;

    deque.insert(deque.cbegin(), source.begin(), source.end());

    EXPECT_EQ(deque.size(), source.size());
    for (std::size_t i = 0; i < source.size(); ++i) {
      EXPECT_EQ(deque[i], source[i]);
    }
  }

  {
    BEGIN_TEST(tmanager, "InsertRange at end",
               "deque.insert(deque.cend(), first, last)");

    ds::Deque<T, 3, 3> source({src[0], src[1], src[2], src[3], src[4]});
    ds::Deque<T, 3, 3> deque = source;
    const auto initial_size = deque.size();

    deque.insert(deque.cend(), source.begin(), source.end());

    EXPECT_EQ(deque.size(), initial_size + source.size());
    for (std::size_t i = 0; i < source.size(); ++i) {
      EXPECT_EQ(deque[initial_size + i], source[i]);
    }
  }
#endif

#if ERASE
  {
    BEGIN_TEST(tmanager, "Erase", "deque.erase(iterator);");

    ds::Deque<T, 3, 3> deque1;

    for (std::size_t i{0}; i < size; ++i) {
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

    for (std::size_t i{0}; i < size; ++i) {
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

    for (std::size_t i{0}; i < size; ++i) {
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
    BEGIN_TEST(tmanager, "Erase range const",
               "deque.erase(const_iterator, const_iterator);");

    ds::Deque<T, 3, 3> deque1;

    auto it = deque1.erase(deque1.begin(), deque1.begin());
    EXPECT_EQ(it, deque1.begin());

    for (std::size_t i{0}; i < size; ++i) {
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

    for (std::size_t i{0}; i < size; ++i) {
      deque.push_back(src[i]);
    }

    auto old_capacity{deque.capacity()};
    deque.clear();

    EXPECT_EQ(deque.size(), 0);
    EXPECT_EQ(deque.capacity(), old_capacity);
    EXPECT_EQ(deque.begin(), deque.end());
  }
#endif

  tmanager.summary();
}

#endif // DEQUE_METHODS_TESTS_HPP
