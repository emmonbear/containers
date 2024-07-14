/**
 * @file list_test.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Unit tests for the list class
 * @version 1.0
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <list>

#include "../../s21_containers.h"
#include "../main_test.h"

template <typename T>
static void print_original(const std::list<T> &l) {
  for (auto it = l.cbegin(); it != l.cend(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

template <typename T>
static void print_lists(const std::list<T> &std_list,
                        const s21::list<T> &s21_list) {
  std::cout << "std_list(size = " << std_list.size() << "):" << std::endl;

  print_original(std_list);

  std::cout << "s21_list(size = " << s21_list.size() << "):" << std::endl;

  s21_list.print();
}

template <typename T>
static bool compare_lists(const std::list<T> &std_list,
                          const s21::list<T> &s21_list, bool expect) {
  bool res = true;
  auto std_it = std_list.cbegin();
  auto s21_it = s21_list.cbegin();

  if (std_list.size() != s21_list.size()) {
    res = false;
  }

  for (; std_it != std_list.cend() && s21_it != s21_list.cend();
       ++std_it, ++s21_it) {
    if (*std_it != *s21_it) {
      res = false;
    }
  }

  if (res != expect) {
    print_lists(std_list, s21_list);
  }
  return res;
}

/// @todo Добавить проверки указателей
TEST(ListTest, DefaultConstructor) {
  std::list<int> list_1;
  s21::list<int> list_2;

  EXPECT_EQ(list_1.size(), 0);
  EXPECT_EQ(list_2.size(), 0);
}

/// @todo Не обработан
TEST(ListTest, PopFrontEmpty) {
  std::list<int> std_list;

  ASSERT_DEATH(std_list.pop_front(), ".*");
}

TEST(ListTest, PopFrontNormal1) {
  std::list<int> std_list{1, 2};
  s21::list<int> s21_list{1, 2};

  std_list.pop_front();
  s21_list.pop_front();

  EXPECT_TRUE(compare_lists(std_list, s21_list, true));
}

TEST(ListTest, PopFrontNormal2) {
  std::list<int> std_list{1, 2, 3};
  s21::list<int> s21_list{1, 2, 3};

  std_list.pop_front();
  s21_list.pop_front();

  EXPECT_TRUE(compare_lists(std_list, s21_list, true));
}

TEST(ListTest, PopFrontNormal3) {
  std::list<int> std_list{1};
  s21::list<int> s21_list{1};

  std_list.pop_front();
  s21_list.pop_front();

  EXPECT_TRUE(compare_lists(std_list, s21_list, true));
}

TEST(ListTest, PopFrontFail1) {
  std::list<int> std_list{1, 2, 3};
  s21::list<int> s21_list{1, 2};

  std_list.pop_front();
  s21_list.pop_front();

  EXPECT_FALSE(compare_lists(std_list, s21_list, false));
}

TEST(ListTest, SwapNormal1) {
  std::list<int> std_list_1{1, 2, 3};
  s21::list<int> s21_list_1{1, 2, 3};

  std::list<int> std_list_2{3, 2, 1};
  s21::list<int> s21_list_2{3, 2, 1};

  std_list_1.swap(std_list_2);
  s21_list_1.swap(s21_list_2);

  std::list<int> expected_std_1{3, 2, 1};
  std::list<int> expected_std_2{1, 2, 3};
  s21::list<int> expected_s21_1{3, 2, 1};
  s21::list<int> expected_s21_2{1, 2, 3};

  EXPECT_EQ(std_list_1, expected_std_1);
  EXPECT_EQ(std_list_2, expected_std_2);

  EXPECT_EQ(s21_list_1, expected_s21_1);
  EXPECT_EQ(s21_list_2, expected_s21_2);

  EXPECT_TRUE(compare_lists(std_list_1, s21_list_1, true));
  EXPECT_TRUE(compare_lists(std_list_2, s21_list_2, true));
}

TEST(ListTest, SwapNormal2) {
  std::list<int> std_list_1{1, 2, 3, 5, 6};
  s21::list<int> s21_list_1{1, 2, 3, 5, 6};

  std::list<int> std_list_2{3, 2, 1};
  s21::list<int> s21_list_2{3, 2, 1};

  std_list_1.swap(std_list_2);
  s21_list_1.swap(s21_list_2);

  std::list<int> expected_std_1{3, 2, 1};
  std::list<int> expected_std_2{1, 2, 3, 5, 6};
  s21::list<int> expected_s21_1{3, 2, 1};
  s21::list<int> expected_s21_2{1, 2, 3, 5, 6};

  EXPECT_EQ(std_list_1, expected_std_1);
  EXPECT_EQ(std_list_2, expected_std_2);

  EXPECT_EQ(s21_list_1, expected_s21_1);
  EXPECT_EQ(s21_list_2, expected_s21_2);

  EXPECT_TRUE(compare_lists(std_list_1, s21_list_1, true));
  EXPECT_TRUE(compare_lists(std_list_2, s21_list_2, true));
}

TEST(ListTest, SpliceNormal1) {
  s21::list<int> s21_list_1{1, 2, 3, 4, 5};
  s21::list<int> s21_list_2{6, 7, 8, 9};

  s21::list<int> s21_expected{1, 6, 7, 8, 9, 2, 3, 4, 5};

  auto it = s21_list_1.cbegin();
  ++it;

  s21_list_1.splice(it, s21_list_2);

  EXPECT_TRUE(s21_list_1 == s21_expected);
}

TEST(ListTest, SpliceNormal2) {
  s21::list<int> s21_list_1{1, 2, 3, 4, 5};
  s21::list<int> s21_list_2{6};

  s21::list<int> s21_expected{6, 1, 2, 3, 4, 5};

  auto it = s21_list_1.cbegin();

  s21_list_1.splice(it, s21_list_2);

  EXPECT_TRUE(s21_list_1 == s21_expected);
}

TEST(ListTest, SpliceNormal3) {
  s21::list<int> s21_list_1;
  s21::list<int> s21_list_2{6};

  s21::list<int> s21_expected{6};

  s21::list<int>::const_iterator it = s21_list_1.cbegin();

  s21_list_1.splice(it, s21_list_2);

  EXPECT_TRUE(s21_list_1 == s21_expected);
}

TEST(ListTest, SpliceEmpty) {
  s21::list<int> s21_list_1{1, 2, 3, 4, 5};
  s21::list<int> s21_list_2;

  s21::list<int> s21_expected{1, 2, 3, 4, 5};
  std::list<int> std_expected{1, 2, 3, 4, 5};

  auto s21_it = s21_list_1.cbegin();

  s21_list_1.splice(s21_it, s21_list_2);

  EXPECT_TRUE(s21_list_1 == s21_expected);
}

TEST(ListTest, EraseNormal1) {
  s21::list<int> s21_list{1};
  s21::list<int> s21_expected;
  auto it = s21_list.begin();

  s21_list.erase(it);

  EXPECT_TRUE(s21_list == s21_expected);
}

TEST(ListTest, EraseNormal2) {
  s21::list<int> s21_list{1, 2};
  s21::list<int> s21_expected{2};
  auto it = s21_list.begin();

  s21_list.erase(it);

  EXPECT_TRUE(s21_list == s21_expected);
}

TEST(ListTest, EraseNormal3) {
  s21::list<int> s21_list{1, 2};
  s21::list<int> s21_expected{1};
  auto it = s21_list.begin();
  ++it;

  s21_list.erase(it);

  EXPECT_TRUE(s21_list == s21_expected);
}

TEST(ListTest, EraseNormal4) {
  s21::list<int> s21_list{1, 2, 4, 3, 4, 5, 6};
  s21::list<int> s21_expected{1, 2, 3, 4, 5, 6};
  auto it = s21_list.begin();
  ++it;
  ++it;

  s21_list.erase(it);

  EXPECT_TRUE(s21_list == s21_expected);
}

TEST(ListTest, MergeNormal1) {
  s21::list<int> l_1{1, 3, 5, 7};
  s21::list<int> l_2{4, 6, 9, 10};
  s21::list<int> expected_1{1, 3, 4, 5, 6, 7, 9, 10};

  l_1.merge(l_2);

  EXPECT_TRUE(l_1 == expected_1);
  EXPECT_TRUE(l_2.empty());
}

TEST(ListTest, MergeEmpty1) {
  s21::list<int> l_1;
  s21::list<int> l_2{4, 6, 9, 10};
  s21::list<int> expected_1{4, 6, 9, 10};

  l_1.merge(l_2);

  EXPECT_TRUE(l_1 == expected_1);
  EXPECT_TRUE(l_2.empty());
}

TEST(ListTest, MergeEmpty2) {
  s21::list<int> l_1{4, 6, 9, 10};
  s21::list<int> l_2;
  s21::list<int> expected_1{4, 6, 9, 10};

  l_1.merge(l_2);

  EXPECT_TRUE(l_1 == expected_1);
  EXPECT_TRUE(l_2.empty());
}

TEST(ListTest, MergeNonSorted) {
  s21::list<int> l_1{2, 1, 3, 5, 2, 9, 7};
  s21::list<int> l_2{1, 4, 5, 3, 4};
  s21::list<int> expected_1{1, 2, 1, 3, 4, 5, 2, 5, 3, 4, 9, 7};

  l_1.merge(l_2);

  EXPECT_TRUE(l_1 == expected_1);
  EXPECT_TRUE(l_2.empty());
}

TEST(ListTest, ReverseNormal1) {
  s21::list<int> l{2, 1, 3, 5, 2, 9, 7};
  s21::list<int> expected{7, 9, 2, 5, 3, 1, 2};

  l.reverse();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, ReverseNormal2) {
  s21::list<int> l{2, 1};
  s21::list<int> expected{1, 2};

  l.reverse();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, ReverseNormal3) {
  s21::list<int> l{1};
  s21::list<int> expected{1};

  l.reverse();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, UniqueNormal1) {
  s21::list<int> l{2, 2, 1, 2, 2, 2, 3, 3, 4, 1};
  s21::list<int> expected{2, 1, 2, 3, 4, 1};

  l.unique();

  EXPECT_TRUE(l == expected);
}
