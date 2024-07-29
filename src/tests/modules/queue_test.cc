/**
 * @file queue_test.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Unit tests for the queue class
 * @version 1.0
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../../s21_containers.h"
#include "../main_test.h"

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> l;

  EXPECT_TRUE(l.empty());
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> original;
  original.push(1);
  original.push(2);
  original.push(3);

  s21::queue<int> copy(original);

  EXPECT_EQ(copy.size(), original.size());

  while (!original.empty()) {
    EXPECT_EQ(copy.front(), original.front());
    copy.pop();
    original.pop();
  }

  original.push(2);
  original.push(3);
  original.push(4);
  s21::queue<int> copy2(original);
  copy2.pop();
  EXPECT_EQ(original.front(), 2);
  EXPECT_EQ(copy2.front(), 3);
}

TEST(QueueTest, InitializerListConstructor) {
  s21::queue<int> q = {1, 2, 3, 4, 5};

  EXPECT_EQ(q.size(), 5);

  EXPECT_EQ(q.front(), 1);
  q.pop();
  EXPECT_EQ(q.front(), 2);
  q.pop();
  EXPECT_EQ(q.front(), 3);
  q.pop();
  EXPECT_EQ(q.front(), 4);
  q.pop();
  EXPECT_EQ(q.front(), 5);
  q.pop();

  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<int> original{1, 2, 3};
  s21::queue<int> moved(std::move(original));

  EXPECT_TRUE(original.empty());
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved.front(), 1);
  moved.pop();
  EXPECT_EQ(moved.front(), 2);
  moved.pop();
  EXPECT_EQ(moved.front(), 3);
  moved.pop();
  EXPECT_TRUE(moved.empty());
}