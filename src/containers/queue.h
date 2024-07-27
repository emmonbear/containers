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

template <typename T, typename Container = s21::list<T>>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

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
  Container c;
};

template <typename value_type, typename Container>
queue<value_type, Container>::queue(
    std::initializer_list<value_type> const &items)
    : c(items) {}

template <typename value_type, typename Container>
queue<value_type, Container>::queue(const queue &q) : c(q.c) {}

template <typename value_type, typename Container>
queue<value_type, Container>::queue(queue &&q) : c(std::move(q.c)) {}

template <typename value_type, typename Container>
queue<value_type, Container>::~queue() {}

template <typename value_type, typename Container>
typename queue<value_type, Container>::queue &
queue<value_type, Container>::operator=(queue &&q) {
  swap(q);

  return *this;
}

template <typename value_type, typename Container>
typename queue<value_type, Container>::const_reference
queue<value_type, Container>::front() const {
  return c.front();
}

template <typename value_type, typename Container>
typename queue<value_type, Container>::const_reference
queue<value_type, Container>::back() const {
  return c.back();
}

template <typename value_type, typename Container>
bool queue<value_type, Container>::empty() const {
  return c.empty();
}

template <typename value_type, typename Container>
typename queue<value_type, Container>::size_type
queue<value_type, Container>::size() const {
  return c.size();
}

template <typename value_type, typename Container>
void queue<value_type, Container>::push(const_reference value) {
  c.push_back();
}

template <typename value_type, typename Container>
void queue<value_type, Container>::pop() {
  c.pop_front();
}

template <typename value_type, typename Container>
void queue<value_type, Container>::swap(queue &other) noexcept {
  c.swap(other.c);
}

}  // namespace s21

#endif  // SRC_CONTAINERS_QUEUE_H_
