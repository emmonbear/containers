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

namespace s21 {
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
  class ListIterator;
  class ListConstIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = list<T>::ListIterator;
  using const_iterator = list<T>::ListConstIterator;
  using pointer = T *;

  list() noexcept;
  explicit list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list &operator=(const list &l);
  list(list &&l);
  list &operator=(list &&l);

  ~list() noexcept;

  bool operator==(const list &l) const;

  const_reference front() const;
  const_reference back() const;

  void push_back(const_reference value) noexcept;
  void pop_back() noexcept;

  bool empty() noexcept;
  size_type size() const;

  void clear() noexcept;

 private:
  struct Node;
  Node *head_{nullptr};
  Node *tail_{nullptr};
  size_type size_{0};

  void copy_from(const list &l);
};

template <typename value_type>
class list<value_type>::Node {
  friend class list;

  value_type value_;
  Node *prev_;
  Node *next_;

  explicit Node(const_reference value)
      : value_{value}, prev_{nullptr}, next_{nullptr} {}
};

template <typename value_type>
class list<value_type>::ListIterator {
 public:
  friend class list;

  ListIterator() noexcept = default;
  explicit ListIterator(Node *node) noexcept : node_{node} {}

  reference operator*() const;
  pointer operator->() const;
  ListIterator &operator++();
  ListIterator operator++(int);
  ListIterator &operator--();
  ListIterator operator--(int);
  bool operator==(const ListIterator &other) const;
  bool operator!=(const ListIterator &other) const;

 private:
  Node *node_{nullptr};
};
///////////////////////////////////////////////////////////////////////////////

template <typename value_type>
typename list<value_type>::reference list<value_type>::ListIterator::operator*()
    const {
  return node_->value_;
}

template <typename value_type>
typename list<value_type>::pointer list<value_type>::ListIterator::operator->()
    const {
  return &(node_->value_);
}

template <typename value_type>
typename list<value_type>::ListIterator::ListIterator &
list<value_type>::ListIterator::operator++() {
  node_ = node_->next_;

  return *this;
}

template <typename value_type>
typename list<value_type>::ListIterator::ListIterator
list<value_type>::ListIterator::operator++(int) {
  ListIterator tmp{*this};
  ++(*this);

  return tmp;
}

template <typename value_type>
typename list<value_type>::ListIterator::ListIterator &
list<value_type>::ListIterator::operator--() {
  node_ = node_->prev_;

  return *this;
}

template <typename value_type>
typename list<value_type>::ListIterator::ListIterator
list<value_type>::ListIterator::operator--(int) {
  ListIterator tmp{*this};
  --(*this);

  return tmp;
}

template <typename value_type>
bool list<value_type>::ListIterator::operator==(
    const ListIterator &other) const {
  return node_ == other.node_;
}

template <typename value_type>
bool list<value_type>::ListIterator::operator!=(
    const ListIterator &other) const {
  return !(*this == other);
}

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

/**
 * @brief Constructs a new list with a specified number of default-initialized
 * elements.
 *
 * @details
 *
 * This constructor initializes an empty list and appends `n`
 * default-initialized elements to the list.
 *
 * @param n The number of elements to add to the list.
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
list<value_type>::list(size_type n) {
  for (size_type i = 0; i < n; i++) {
    push_back(value_type());
  }
}

/**
 * @brief Constructs a new list from an initializer list of values.
 *
 * @details
 *
 * This constructor initializes an empty list and appends each element
 * from the given initializer list to the end of the list.
 *
 * @param items An initializer list of values to populate the list.
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items)
    : head_{nullptr}, tail_{nullptr}, size_{0} {
  for (const value_type &item : items) {
    push_back(item);
  }
}

/**
 * @brief Copy constructor for creating a new list as a copy of another list.
 *
 * @details
 *
 * This constructor initializes a new list as a copy of the provided list `l`.
 * It initializes the head, tail, and size of the new list and then copies all
 * elements from `l` to the new list using the `copy_from` method.
 *
 * @param l The list to be copied.
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
list<value_type>::list(const list &l)
    : head_{nullptr}, tail_{nullptr}, size_{0} {
  copy_from(l);
}

/**
 * @brief Assignment operator.
 *
 * @details
 *
 * Copies the contents of list @p l into the current list.
 *
 * @param l The list to copy from.
 * @tparam value_type The type of elements stored in the list.
 * @return Reference to the current list object after copying.
 */
template <typename value_type>
typename list<value_type>::list &list<value_type>::operator=(const list &l) {
  if (this != l) {
    clear();
    copy_from(l);
  }

  return *this;
}

/**
 * @brief Move constructor.
 *
 * @details
 *
 * Constructs a new list by transferring ownership of the data from the
 * specified list `l` to this list. The source list `l` is left in an
 * empty state.
 *
 * @param l The list to move from.
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
list<value_type>::list(list &&l)
    : head_{l.head_}, tail_{l.tail_}, size_{l.size_} {
  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.size_ = 0;
}

/**
 * @brief Move assignment operator.
 *
 * @details
 *
 * Moves the contents of the list @p l into the current list and returns a
 * reference to the modified list.
 * @param l The list to move from.
 * @return * template <typename value_type>&
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
typename list<value_type>::list &list<value_type>::operator=(list &&l) {
  if (this != &l) {
    clear();
    head_ = l.head_;
    tail_ = l.tail_;
    size_ = l.size_;

    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
  }

  return std::move(*this);
}

/**
 * @brief Destructor for the list class.
 *
 * @details
 *
 * The destructor calls the clear() method to free all elements of the list,
 * preventing memory leaks
 *
 * @tparam value_type The type of elements stored in the list.
 */
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
  Node *new_node = new Node{value};

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
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
bool list<value_type>::empty() noexcept {
  return size_ == 0;
}

/**
 * @brief Clear the contents of the list.
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
void list<value_type>::clear() noexcept {
  while (!empty()) {
    pop_back();
  }
}

/**
 * @brief Removes the last element of the list.
 * @tparam value_type The type of elements stored in the list.
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

/**
 * @brief Returns the number of elements in the list.
 * @return size_type The number of elements in the list.
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
typename list<value_type>::size_type list<value_type>::size() const {
  return size_;
}

/**
 * @brief Copies elements from another list to the current list.
 *
 * @details
 *
 * This method copies all elements from the provided list `l` to the current
 * list. It iterates through the elements of `l` and appends each element to the
 * current list.
 *
 * @param l The list from which elements will be copied.
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
void list<value_type>::copy_from(const list &l) {
  Node *current = l.head_;

  while (current) {
    push_back(current->value_);
    current = current->next_;
  }
}

/**
 * @brief Equality operator to compare two lists.
 *
 * @param l The list to compare with the current list.
 * @tparam value_type The type of elements stored in the list.
 * @retval true if both lists have the same size and all corresponding elements
 * are equal.
 * @retval false if the sizes of the lists are different or if at least one
 * element differs.
 */
template <typename value_type>
bool list<value_type>::operator==(const list &l) const {
  if (size_ != l.size_) {
    return false;
  }

  Node *current_1 = head_;
  Node *current_2 = l.head_;

  while (current_1 && current_2) {
    if (current_1->value_ != current_2->value_) {
      return false;
    }

    current_1 = current_1->next_;
    current_2 = current_2->next_;
  }

  return true;
}

/**
 * @brief Access the first element.
 * @tparam value_type The type of elements stored in the list.
 * @return const_reference A reference to the first element in the list.
 * @throw std::out_of_range if the list is empty.
 */
template <typename value_type>
typename list<value_type>::const_reference list<value_type>::front() const {
  if (empty()) {
    throw std::out_of_range("list is empty");
  }

  return head_->value_;
}

/**
 * @brief Access the last element.
 * @tparam value_type The type of elements stored in the list.
 * @return const_reference A reference to the last element in the list.
 * @throw std::out_of_range if the list is empty.
 */
template <typename value_type>
typename list<value_type>::const_reference list<value_type>::back() const {
  if (empty()) {
    throw std::out_of_range("list is empty");
  }

  return tail_->value_;
}

// ITERATOR'S METHODS
// template <typename value_type>
// typename list<value_type>::iterator& list<value_type>::iterator::operator++()
// {
//   if (node_) {
//     node_ = node_->next_;
//   }

//   return *this;
// }

}  // namespace s21

#endif  // SRC_CONTAINERS_LIST_H_
