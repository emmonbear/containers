/**
 * @file stack_test.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Unit tests for the stack class
 * @version 1.0
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <list>
#include <stack>

#include "../../s21_containers.h"
#include "../main_test.h"

template <typename T>
static bool compare_stacks(std::stack<T, std::list<int>> &std_stack,
                           s21::stack<T, s21::list<int>> &s21_stack) {
  while (!std_stack.empty() && !s21_stack.empty()) {
    if (std_stack.top() != s21_stack.top()) {
      return false;
    }

    std_stack.pop();
    s21_stack.pop();
  }

  return true;
}

template <typename T>
static bool compare_stacks(std::stack<T> &std_stack,
                           s21::stack<T> &s21_stack) {
  while (!std_stack.empty() && !s21_stack.empty()) {
    if (std_stack.top() != s21_stack.top()) {
      return false;
    }

    std_stack.pop();
    s21_stack.pop();
  }

  return true;
}

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> s;

  EXPECT_TRUE(s.empty());
}

TEST(QueueTest, CopyConstructorContainer1) {
  s21::list<int> s21_l{1, 2, 3};
  std::list<int> std_l{1, 2, 3};

  s21::stack<int, s21::list<int>> s21_stack(s21_l);
  std::stack<int, std::list<int>> std_stack(std_l);
  EXPECT_EQ(s21_stack.size(), std_stack.size());

  EXPECT_TRUE(compare_stacks(std_stack, s21_stack));
}

TEST(QueueTest, CopyConstructorContainer2) {
  s21::list<int> s21_l{3, 4, 1, 2, 9};
  std::list<int> std_l{3, 4, 1, 2, 9};

  s21::stack<int, s21::list<int>> s21_stack(s21_l);
  std::stack<int, std::list<int>> std_stack(std_l);

  EXPECT_EQ(s21_stack.size(), std_stack.size());

  EXPECT_TRUE(compare_stacks(std_stack, s21_stack));
}

TEST(QueueTest, CopyConstructorContainerFail) {
  s21::list<int> s21_l{1, 2, 3, 4};
  std::list<int> std_l{1, 2, 3};

  s21::stack<int, s21::list<int>> s21_stack(s21_l);
  std::stack<int, std::list<int>> std_stack(std_l);

  EXPECT_FALSE(compare_stacks(std_stack, s21_stack));
}

TEST(QueueTest, MoveConstructorContainer1) {
  s21::list<int> s21_l{1, 2, 3};
  std::list<int> std_l{1, 2, 3};

  s21::stack<int, s21::list<int>> s21_stack(std::move(s21_l));
  std::stack<int, std::list<int>> std_stack(std::move(std_l));
  EXPECT_EQ(s21_stack.size(), std_stack.size());

  EXPECT_TRUE(s21_l.empty());
  EXPECT_TRUE(std_l.empty());
  EXPECT_TRUE(compare_stacks(std_stack, s21_stack));
}

TEST(QueueTest, MoveConstructorContainer2) {
  s21::list<int> s21_l{3, 4, 1, 2, 9};
  std::list<int> std_l{3, 4, 1, 2, 9};

  s21::stack<int, s21::list<int>> s21_stack(std::move(s21_l));
  std::stack<int, std::list<int>> std_stack(std::move(std_l));

  EXPECT_EQ(s21_stack.size(), std_stack.size());

  EXPECT_TRUE(s21_l.empty());
  EXPECT_TRUE(std_l.empty());

  EXPECT_TRUE(compare_stacks(std_stack, s21_stack));
}

TEST(QueueTest, CopyConstructor1) {
  s21::stack<int> s21_original;
  std::stack<int> std_original;

  s21_original.push(1);
  s21_original.push(2);
  s21_original.push(3);

  std_original.push(1);
  std_original.push(2);
  std_original.push(3);

  s21::stack<int> s21_copy(s21_original);
  std::stack<int> std_copy(std_original);

  EXPECT_EQ(s21_original.size(), std_original.size());
  EXPECT_EQ(std_copy.size(), s21_copy.size());

  EXPECT_TRUE(compare_stacks(std_copy, s21_copy));
}

TEST(QueueTest, CopyConstructorFail) {
  s21::stack<int> s21_original;
  std::stack<int> std_original;

  s21_original.push(1);
  s21_original.push(2);
  s21_original.push(3);
  s21_original.push(6);

  std_original.push(1);
  std_original.push(2);
  std_original.push(3);

  s21::stack<int> s21_copy(s21_original);
  std::stack<int> std_copy(std_original);

  EXPECT_NE(s21_original.size(), std_original.size());
  EXPECT_NE(std_copy.size(), s21_copy.size());

  EXPECT_FALSE(compare_stacks(std_copy, s21_copy));
}

TEST(QueueTest, MoveConstructor1) {
  s21::stack<int> s21_original;
  std::stack<int> std_original;

  s21_original.push(1);
  s21_original.push(2);
  s21_original.push(3);

  std_original.push(1);
  std_original.push(2);
  std_original.push(3);

  s21::stack<int> s21_copy(std::move(s21_original));
  std::stack<int> std_copy(std::move(std_original));

  EXPECT_EQ(s21_original.size(), std_original.size());
  EXPECT_EQ(std_copy.size(), s21_copy.size());

  EXPECT_TRUE(compare_stacks(std_copy, s21_copy));
}

TEST(QueueTest, PushLvalue) {
  s21::stack<int> s21_original;
  std::stack<int> std_original;

  int num = 1;
  s21_original.push(num);
  s21_original.push(num);
  s21_original.push(num);

  std_original.push(num);
  std_original.push(num);
  std_original.push(num);

  s21::stack<int> s21_copy(std::move(s21_original));
  std::stack<int> std_copy(std::move(std_original));

  EXPECT_EQ(s21_original.size(), std_original.size());
  EXPECT_EQ(std_copy.size(), s21_copy.size());

  EXPECT_TRUE(compare_stacks(std_copy, s21_copy));
}