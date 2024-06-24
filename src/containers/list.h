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

#ifndef SRC_CONTAINERS_LIST_H_
#define SRC_CONTAINERS_LIST_H_

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

  bool empty() noexcept;

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

  void clear() noexcept;
  void pop_back() noexcept;
};

/**
 * @brief Default constructor for the list class.
 *
 * @details
 *
 * Constructs an empty list, initializing head, tail, and size to default
 * values. The constructor is noexcept, indicating it does not throw exceptions.
 *
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
list<value_type>::list() noexcept = default;

// template <typename value_type>
// list<value_type>::list(size_type n) noexcept
//     : head_{nullptr}, tail_{nullptr}, size_{0} {
//   if (n > max_size()) {
//     std::cerr << "Requested size exceeds maximum allowable size." <<
//     std::endl; exit 1;
//   }
//   for (size_type i = 0; i < n; i++) {
//     push_back(value_type());
//   }
// }

template <typename value_type>
list<value_type>::~list() noexcept {
  clear();
}

/**
 * @brief Adds a new node with the given value to the end of the list.
 *
 * @details
 *
 * This function creates a new node containing the specified value and appends
 * it to the end of the list. If memory allocation fails, an error message is
 * printed to the standard error stream (std::cerr)
 *
 * @param value The value to be added to the list.
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
void list<value_type>::push_back(const_reference value) noexcept {
  Node *new_node = new (std::nothrow) Node(value);

  if (!new_node) {
    std::cerr << "Error: Failed to allocate memory for new node." << std::endl;
    return;
  }

  if (!head_) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    tail_->next_ = new_node;
    new_node->prev_ = tail_;
    tail_ = new_node;
  }

  ++size_;
}

/**
 * @brief Checks whether the container is empty.
 *
 * @return * template <typename value_type>
 */
template <typename value_type>
bool list<value_type>::empty() noexcept {
  return size_ == 0;
}

/**
 * @brief Clear the contents of the list.
 *
 * @return * template <typename value_type>
 */
template <typename value_type>
void list<value_type>::clear() noexcept {
  while (!empty()) {
    pop_back();
  }
}

/**
 * @brief Removes the last element of the list.
 *
 * @return * template <typename value_type>
 */
template <typename value_type>
void list<value_type>::pop_back() noexcept {
  if (empty()) {
    std::cerr << "list is empty" << std::endl;
  } else {
    if (size_ == 1) {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      Node *prev = tail_->prev_;
      delete tail_;
      tail_ = prev;
      tail_->next_ = nullptr;
    }

    size_--;
  }
}

}  // namespace containers

#endif  // SRC_CONTAINERS_LIST_H_
