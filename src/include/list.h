/**
 * @file list.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Declaration of the list class
 * @version 1.0
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_LIST_H_
#define SRC_INCLUDE_LIST_H_

#include <iostream>

namespace containers {
/**
 * @brief Class that implements a list.
 *
 * @details
 *
 * List is a sequence container that stores a set of elements with arbitrary
 * size, in the form of nodes connected in sequence by pointers. Each node
 * stores a value corresponding to an element in the list, and a pointer to the
 * next element. This container design allows you to avoid a rigidly fixed size,
 * such as in a static array, and makes adding a new element to the container
 * more user-friendly.
 *
 */
template <typename T>
class list {
 public:
  // types
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  // using iterator = /* implementation-defined */;
  // using const_iterator = /* implementation-defined */;

  // construct/copy/destroy
  list() noexcept;
  explicit list(size_type n) noexcept;
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list() noexcept;
  list operator=(list &&l);

  void push_back(const_reference value) noexcept;

 private:
  struct Node {
    value_type value_;
    Node *prev_{nullptr};
    Node *next_{nullptr};

    explicit Node(const value_type &value) : value_{value} {}
  };

  Node *head_{nullptr};
  Node *tail_{nullptr};
  size_type size_{0};
};
}  // namespace containers

#endif  // SRC_INCLUDE_LIST_H_
