/**
 * @file list.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Implementation of the list class
 * @version 1.0
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/list.h"

namespace containers {

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

}  // namespace containers
