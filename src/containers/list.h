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
#include <limits>  // for std::numeric_limits

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

  using value_type = T;  ///< Alias for the type of values stored in the list.
  using reference =
      T &;  ///< Alias for a reference to the type of values stored in the list.
  using const_reference = const T &;  ///< Alias for a constant reference to the
                                      ///< type of values stored in the list.
  using size_type =
      std::size_t;  ///< Alias for the type used for size measurements.
  using iterator = ListIterator;  ///< Alias for the iterator type for the list.
  using const_iterator = ListConstIterator;  ///< Alias for the constant
                                             ///< iterator type for the list.
  using pointer =
      T *;  ///< Alias for a pointer to the type of values stored in the list.
  using const_pointer = const T *;  ///< Alias for a constant pointer to the
                                    ///< type of values stored in the list.

  // List Functions
  list() noexcept;
  explicit list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list &operator=(const list &l);
  list(list &&l);
  list &operator=(list &&l);

  ~list() noexcept;

  // List Element Access
  const_reference front() const;
  const_reference back() const;

  // List Iterators
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  // List Capacity
  bool empty() const noexcept;
  size_type size() const;
  size_type max_size() const;

  // List Modifiers
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  iterator erase(iterator pos);
  void push_back(const_reference value) noexcept;
  void pop_back() noexcept;
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  // Other
  bool operator==(const list &l) const;
  void print() const;

 private:
  struct Node;
  Node *head_{nullptr};
  Node *tail_{nullptr};
  size_type size_{0};

  void copy_from(const list &l);
};

/**
 * @brief A node in the doubly linked list.
 * @tparam value_type The type of the value stored in the node.
 */
template <typename value_type>
struct list<value_type>::Node {
  friend class list;

  value_type value_;
  Node *prev_;
  Node *next_;

  explicit Node(const_reference value)
      : value_{value}, prev_{nullptr}, next_{nullptr} {}
};

/**
 * @brief Iterator class for iterating over a doubly linked list.
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
class list<value_type>::ListIterator {
 public:
  friend class list;

  ListIterator() noexcept = default;
  explicit ListIterator(Node *node) noexcept : node_{node} {}

  reference operator*();
  pointer operator->();
  ListIterator &operator++();
  ListIterator operator++(int);
  ListIterator &operator--();
  ListIterator operator--(int);
  bool operator==(const ListIterator &other) const;
  bool operator!=(const ListIterator &other) const;

 private:
  Node *node_{nullptr};
};

/**
 * @brief Iterator class for iterating through a constant list.
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
class list<value_type>::ListConstIterator {
 public:
  friend class list;

  ListConstIterator() noexcept = default;
  explicit ListConstIterator(Node *node) : node_{node} {}

  const_reference operator*() const;
  const_pointer operator->() const;
  ListConstIterator &operator++();
  ListConstIterator operator++(int);
  ListConstIterator &operator--();
  ListConstIterator operator--(int);
  bool operator==(const ListConstIterator &other) const;
  bool operator!=(const ListConstIterator &other) const;

 private:
  Node *node_{nullptr};
};

// ListIterator ###############################################################

/**
 * @brief Dereference operator.
 * @tparam value_type The type of elements stored in the list.
 * @return Reference to the value stored in the current node.
 */
template <typename value_type>
typename list<value_type>::reference
list<value_type>::ListIterator::operator*() {
  static value_type default_value{};
  return node_ ? node_->value_ : default_value;
}

/**
 * @brief Arrow operator.
 * @tparam value_type The type of elements stored in the list.
 * @return Pointer to the value stored in the current node.
 */
template <typename value_type>
typename list<value_type>::pointer
list<value_type>::ListIterator::operator->() {
  return &(node_->value_);
}

/**
 * @brief Pre-increment operator (++i).
 * @tparam value_type The type of elements stored in the list.
 * @return Reference to the updated iterator.
 */
template <typename value_type>
typename list<value_type>::ListIterator::ListIterator &
list<value_type>::ListIterator::operator++() {
  node_ = node_->next_;

  return *this;
}

/**
 * @brief Post-increment operator (i++).
 * @tparam value_type The type of elements stored in the list.
 * @return A copy of the iterator before the increment.
 */
template <typename value_type>
typename list<value_type>::ListIterator::ListIterator
list<value_type>::ListIterator::operator++(int) {
  ListIterator tmp{*this};
  ++(*this);

  return tmp;
}

/**
 * @brief Pre-decrement operator (--i).
 * @tparam value_type The type of elements stored in the list.
 * @return Reference to the updated iterator.
 */
template <typename value_type>
typename list<value_type>::ListIterator::ListIterator &
list<value_type>::ListIterator::operator--() {
  node_ = node_->prev_;

  return *this;
}

/**
 * @brief Post-decrement operator (i--).
 * @tparam value_type The type of elements stored in the list.
 * @return A copy of the iterator before decrementing.
 */
template <typename value_type>
typename list<value_type>::ListIterator::ListIterator
list<value_type>::ListIterator::operator--(int) {
  ListIterator tmp{*this};
  --(*this);

  return tmp;
}

/**
 * @brief Equality comparison operator.
 * @tparam value_type The type of elements stored in the list.
 * @param other The iterator to compare against.
 * @return true if both iterators point to the same node, false otherwise.
 */
template <typename value_type>
bool list<value_type>::ListIterator::operator==(
    const ListIterator &other) const {
  return node_ == other.node_;
}

/**
 * @brief Inequality comparison operator.
 * @tparam value_type The type of elements stored in the list.
 * @param other The iterator to compare against.
 * @return true if the iterators point to different nodes, false otherwise.
 */
template <typename value_type>
bool list<value_type>::ListIterator::operator!=(
    const ListIterator &other) const {
  return !(*this == other);
}

// ListConstIterator ##########################################################

/**
 * @brief Dereference operator.
 * @tparam value_type The type of elements stored in the list.
 * @return const_reference A reference to the value of the current node.
 */
template <typename value_type>
typename list<value_type>::const_reference
list<value_type>::ListConstIterator::operator*() const {
  static value_type default_value{};
  return node_ ? node_->value_ : default_value;
}

/**
 * @brief Member access operator.
 * @tparam value_type The type of elements stored in the list.
 * @return const_pointer A pointer to the value of the current node.
 */
template <typename value_type>
typename list<value_type>::const_pointer
list<value_type>::ListConstIterator::operator->() const {
  return &(node_->value_);
}

/**
 * @brief Pre-increment operator (++i).
 * @tparam value_type The type of elements stored in the list.
 * @return Reference to the updated iterator.
 */
template <typename value_type>
typename list<value_type>::ListConstIterator &
list<value_type>::ListConstIterator::operator++() {
  node_ = node_->next_;

  return (*this);
}

/**
 * @brief Post-increment operator (i++).
 * @tparam value_type The type of elements stored in the list.
 * @return A copy of the iterator before the increment.
 */
template <typename value_type>
typename list<value_type>::ListConstIterator
list<value_type>::ListConstIterator::operator++(int) {
  ListConstIterator tmp{*this};
  ++(*this);

  return tmp;
}

/**
 * @brief Pre-decrement operator (--i).
 * @tparam value_type The type of elements stored in the list.
 * @return Reference to the updated iterator.
 */
template <typename value_type>
typename list<value_type>::ListConstIterator &
list<value_type>::ListConstIterator::operator--() {
  node_ = node_->prev_;

  return (*this);
}

/**
 * @brief Post-decrement operator (i--).
 * @tparam value_type The type of elements stored in the list.
 * @return A copy of the iterator before decrementing.
 */
template <typename value_type>
typename list<value_type>::ListConstIterator
list<value_type>::ListConstIterator::operator--(int) {
  ListConstIterator tmp{*this};
  --(*this);

  return tmp;
}

/**
 * @brief Equality comparison operator.
 * @tparam value_type The type of elements stored in the list.
 * @param other The iterator to compare against.
 * @return true if both iterators point to the same node, false otherwise.
 */
template <typename value_type>
bool list<value_type>::ListConstIterator::operator==(
    const ListConstIterator &other) const {
  return node_ == other.node_;
}

/**
 * @brief Inequality comparison operator.
 * @tparam value_type The type of elements stored in the list.
 * @param other The iterator to compare against.
 * @return true if the iterators point to different nodes, false otherwise.
 */
template <typename value_type>
bool list<value_type>::ListConstIterator::operator!=(
    const ListConstIterator &other) const {
  return !(*this == other);
}

// List ########################################################################

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

/**
 * @brief Returns an iterator to the beginning of the list.
 * @tparam value_type The type of the value stored in the list.
 * @return iterator An iterator to the first element in the list.
 */
template <typename value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  return empty() ? iterator{nullptr} : iterator{head_};
}

/**
 * @brief Returns an iterator to the end of the list.
 * @tparam value_type The type of the value stored in the list.
 * @return iterator An iterator to the element following the last element in the
 * list.
 */
template <typename value_type>
typename list<value_type>::iterator list<value_type>::end() {
  return iterator{nullptr};
}

template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::cbegin() const {
  return empty() ? const_iterator{nullptr} : const_iterator{head_};
}

template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::cend() const {
  return const_iterator{nullptr};
}

/**
 * @brief Checks whether the container is empty.
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
bool list<value_type>::empty() const noexcept {
  return size_ == 0;
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

template <typename value_type>
typename list<value_type>::size_type list<value_type>::max_size() const {
  return std::numeric_limits<size_type>::max();
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

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  Node *new_node = new Node(value);

  if (!pos.node_) {
    new_node->prev_ = tail_;

    if (tail_) {
      tail_->next_ = new_node;
    } else {
      head_ = new_node;
    }

    tail_ = new_node;

  } else {
    new_node->prev_ = pos.node_->prev_;
    new_node->next_ = pos.node_;

    if (pos.node_->prev_) {
      pos.node_->prev_->next_ = new_node;
    } else {
      head_ = new_node;
    }

    pos.node_->prev_ = new_node;
  }

  ++size_;

  return iterator(new_node);
}

/// @todo Не обработан iterator == nullptr. Ориганальная не обрабатывает.
/// Мой вариант возвращает nullptr, при попытке разыменовать который вызывается
/// конструктор по умолчанию для value_type{} (как и оригинальный). Но попытка
/// удалить элемент по begin() в оригинальном списке вызывает double free or
/// corruption (out) make: *** [Makefile:62: test] Aborted (core dumped)
/// Оригинальная функция возвращает итератор, что удобно и логично(по крайней
/// мере при реализации merge, избавляя от необходимости создавать буферные
/// итераторы). Вопрос почему в ТЗ функция его не возвращает остается открытым
template <typename value_type>
typename list<value_type>::iterator list<value_type>::erase(iterator pos) {
  if ((pos != end()) && (!empty())) {
    Node *node_to_remove = pos.node_;
    iterator next_it = iterator(node_to_remove->next_);

    if (node_to_remove == head_) {
      head_ = node_to_remove->next_;
    } else if (node_to_remove == tail_) {
      tail_ = node_to_remove->prev_;
      tail_->next_ = nullptr;
    } else {
      node_to_remove->next_->prev_ = node_to_remove->prev_;
      node_to_remove->prev_->next_ = node_to_remove->next_;
    }

    delete node_to_remove;
    --size_;

    return next_it;
  }

  return end();
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

template <typename value_type>
void list<value_type>::push_front(const_reference value) {
  Node *new_node = new Node(value);

  if (empty()) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->next_ = head_;
    head_->prev_ = new_node;
    head_ = new_node;
  }

  ++size_;
}

/// @todo Не обработан случай, когда список пустой. Поведение оригинальной
/// непредсказуемо
template <typename value_type>
void list<value_type>::pop_front() {
  if (head_) {
    Node *old_head = head_;
    head_ = head_->next_;

    if (head_) {
      head_->prev_ = nullptr;
    } else {
      tail_ = nullptr;
    }

    delete old_head;
    --size_;
  }
}

template <typename value_type>
void list<value_type>::swap(list &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename value_type>
void list<value_type>::merge(list &other) {
  auto this_it = begin();
  auto other_it = other.begin();

  while (this_it != end() && other_it != other.end()) {
    if (*other_it < *this_it) {
      insert(this_it, std::move(*other_it));
      other_it = other.erase(other_it);
    } else {
      ++this_it;
    }
  }

  while (other_it != other.end()) {
    push_back(std::move(*other_it));
    other_it = other.erase(other_it);
  }
}

template <typename value_type>
void list<value_type>::splice(const_iterator pos, list &other) {
  if (this == &other || other.empty()) {
    return;
  }

  if (empty()) {
    swap(other);
  } else {
    auto pos_node = pos.node_;
    auto first_other = other.head_;
    auto last_other = other.tail_;

    if (pos_node == head_) {
      head_ = first_other;
    } else {
      pos_node->prev_->next_ = first_other;
      first_other->prev_ = pos_node->prev_;
    }

    last_other->next_ = pos_node;
    pos_node->prev_ = last_other;

    other.head_ = nullptr;
    other.tail_ = nullptr;

    size_ += other.size_;
    other.size_ = 0;
  }
}

template <typename value_type>
void list<value_type>::reverse() {
  if (size_ < 2) {
    return;
  }

  Node *current = head_;
  Node *next_node = nullptr;
  Node *prev_node = nullptr;

  while (current != nullptr) {
    next_node = current->next_;
    current->next_ = prev_node;
    current->prev_ = next_node;
    prev_node = current;
    current = next_node;
  }

  tail_ = head_;
  head_ = prev_node;
}

template <typename value_type>
void list<value_type>::unique() {
  if (empty() || !head_->next_) {
    return;
  }

  Node *current = head_;

  while (current && current->next_) {
    if (current->value_ == current->next_->value_) {
      Node *node_to_remove = current->next_;
      current->next_ = node_to_remove->next_;

      if (node_to_remove->next_) {
        node_to_remove->next_->prev_ = current;
      } else {
        tail_ = current;
      }

      delete node_to_remove;
      --size_;
    } else {
      current = current->next_;
    }
  }
}

template <typename value_type>
void list<value_type>::sort() {
  
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

template <typename value_type>
void list<value_type>::print() const {
  for (auto it = cbegin(); it != cend(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

}  // namespace s21

#endif  // SRC_CONTAINERS_LIST_H_
