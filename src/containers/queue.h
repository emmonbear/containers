/**
 * @file queue.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Declaration of the queue class
 * @version 1.0
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_CONTAINERS_QUEUE_H_
#define SRC_CONTAINERS_QUEUE_H_

namespace s21 {

/**
 * @brief Template class for a queue data structure.
 *
 * @tparam T The type of elements stored in the queue.
 * @tparam Container The type of the underlying container used to store the
 * elements. Defaults to s21::list<T> if not specified.
 */
template <typename T, typename Container = s21::list<T>>
class queue {
 public:
  using value_type = T;  ///< Alias for the type of values stored in the queue.
  using reference = T
      &;  ///< Alias for a mutable reference to an element stored in the queue.
  using const_reference = const T &;  ///< Alias for a read-only reference to an
                                      ///< element stored in the queue.
  using size_type = std::size_t;  ///< Alias for the type used to represent the
                                  ///< number of elements in the queue.

  queue() = default;
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();
  queue &operator=(queue &&q);

  /// Queue Element access
  const_reference front() const;
  const_reference back() const;

  // Queue Capacity
  bool empty() const;
  size_type size() const;

  // Queue Modifiers
  void push(const_reference value);
  void pop();
  void swap(queue &other) noexcept;

 private:
  Container c;  ///< The container used to store elements in the queue.
};

/**
 * @brief Constructor with initializer list.
 *
 * @details
 *
 * Initializes the queue with the elements from the given initializer list.
 *
 * @param items An initializer list containing elements to initialize the queue.
 * @tparam value_type The type of elements stored in the queue.
 * @tparam Container The type of the underlying container used to store the
 * elements.
 */
template <typename value_type, typename Container>
queue<value_type, Container>::queue(
    std::initializer_list<value_type> const &items)
    : c(items) {}

/**
 * @brief Copy constructor.
 *
 * @details
 *
 * Initializes a new queue as a copy of the given queue.
 * @param q The queue to copy from.
 * @tparam value_type The type of elements stored in the queue.
 * @tparam Container The type of the underlying container used to store the
 * elements.
 */
template <typename value_type, typename Container>
queue<value_type, Container>::queue(const queue &q) : c(q.c) {}

/**
 * @brief Move constructor.
 *
 * @details
 *
 * Initializes a new queue by moving the contents from the given queue.
 * This leaves the given queue in a valid but unspecified state.
 * @param q The queue to move from.
 * @tparam value_type The type of elements stored in the queue.
 * @tparam Container The type of the underlying container used to store the
 * elements.
 */
template <typename value_type, typename Container>
queue<value_type, Container>::queue(queue &&q) : c(std::move(q.c)) {}

/**
 * @brief Destructor.
 *
 * @details
 *
 * Destroys the queue, releasing any resources used.
 * @tparam value_type The type of elements stored in the queue.
 * @tparam Container The type of the underlying container used to store the
 * elements.
 */
template <typename value_type, typename Container>
queue<value_type, Container>::~queue() {}

/**
 * @brief Move assignment operator.
 *
 * @details
 *
 * Moves the contents of the given queue into the current queue.
 * After the operation, the given queue is left in a valid but unspecified
 * state.
 * @param q The queue to move from.
 * @return A reference to the modified queue.
 * @tparam value_type The type of elements stored in the queue.
 * @tparam Container The type of the underlying container used to store the
 * elements.
 */
template <typename value_type, typename Container>
typename queue<value_type, Container>::queue &
queue<value_type, Container>::operator=(queue &&q) {
  swap(q);

  return *this;
}

/**
 * @brief Returns a constant reference to the first element in the queue.
 *
 * @details
 *
 * Provides access to the first element in the queue without modifying it.
 * If the queue is empty, the behavior is undefined.
 * @return A constant reference to the first element in the queue.
 * @tparam value_type The type of elements stored in the queue.
 * @tparam Container The type of the underlying container used to store the
 * elements.
 */
template <typename value_type, typename Container>
typename queue<value_type, Container>::const_reference
queue<value_type, Container>::front() const {
  return c.front();
}

/**
 * @brief Returns a constant reference to the last element in the queue.
 *
 * @details
 *
 * Provides access to the last element in the queue without modifying it.
 * If the queue is empty, the behavior is undefined.
 * @return A constant reference to the last element in the queue.
 * @tparam value_type The type of elements stored in the queue.
 * @tparam Container The type of the underlying container used to store the
 * elements.
 */
template <typename value_type, typename Container>
typename queue<value_type, Container>::const_reference
queue<value_type, Container>::back() const {
  return c.back();
}

/**
 * @brief Checks if the queue is empty.
 *
 * @details
 *
 * Returns true if the queue contains no elements, and false otherwise.
 * @return True if the queue is empty, false otherwise.
 * @tparam value_type The type of elements stored in the queue.
 * @tparam Container The type of the underlying container used to store the
 * elements.
 */
template <typename value_type, typename Container>
bool queue<value_type, Container>::empty() const {
  return c.empty();
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @details
 *
 * Provides the current size of the queue, indicating how many elements it
 * contains.
 * @return The number of elements in the queue.
 * @tparam value_type The type of elements stored in the queue.
 * @tparam Container The type of the underlying container used to store the
 * elements.
 */
template <typename value_type, typename Container>
typename queue<value_type, Container>::size_type
queue<value_type, Container>::size() const {
  return c.size();
}

/**
 * @brief Adds an element to the end of the queue.
 *
 * @details
 *
 * Inserts the given element at the end of the queue. This increases the size of
 * the queue by one.
 * @param value The element to add to the queue.
 * @tparam value_type The type of elements stored in the queue.
 * @tparam Container The type of the underlying container used to store the
 * elements.
 */
template <typename value_type, typename Container>
void queue<value_type, Container>::push(const_reference value) {
  c.push_back();
}

/**
 * @brief Removes the element at the front of the queue.
 *
 * @details
 *
 * Removes the first element from the queue. This decreases the size of the
 * queue by one. If the queue is empty, the behavior is undefined.
 * @tparam value_type The type of elements stored in the queue.
 * @tparam Container The type of the underlying container used to store the
 * elements.
 */
template <typename value_type, typename Container>
void queue<value_type, Container>::pop() {
  c.pop_front();
}

/**
 * @brief Swaps the contents of this queue with another queue.
 *
 * @details
 *
 * Exchanges the contents of this queue with the contents of the given queue.
 * Both queues are left in valid but unspecified states. This operation is
 * noexcept, meaning it will not throw exceptions.
 * @param other The queue to swap contents with.
 * @tparam value_type The type of elements stored in the queue.
 * @tparam Container The type of the underlying container used to store the
 * elements.
 */
template <typename value_type, typename Container>
void queue<value_type, Container>::swap(queue &other) noexcept {
  c.swap(other.c);
}
}  // namespace s21

#endif  // SRC_CONTAINERS_QUEUE_H_
