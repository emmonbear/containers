/**
 * @file stack.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Declaration of the stack class
 * @version 1.0
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_CONTAINERS_STACK_H_
#define SRC_CONTAINERS_STACK_H_

namespace s21 {

template <typename T, typename Container = list<T>>
class stack {
 public:
  using value_type =
      typename Container::value_type;  ///< Alias for the type of values stored
                                       ///< in the stack.
  using reference =
      typename Container::reference;  ///< Alias for a reference to the type of
                                      ///< values stored in the stack.
  using const_reference =
      typename Container::const_reference;  ///< Alias for a constant reference
                                            ///< to the type of values stored in
                                            ///< the stack.
  using size_type = typename Container::size_type;  ///< Alias for the type used
                                                    ///< for size measurements.
  using container_type = Container;
  // Stack Member functions

  stack() : c{Container()} {}
  stack(const Container &s);
  stack(Container &&s);
  stack(const stack &other);
  stack(stack &&other);
  ~stack() {}
  stack &operator=(stack &&s);

  // Stack Element access

  const_reference top() const;

  // Stack Capacity

  bool empty() const;
  size_type size();

  // Stack Modifiers

  void push(const_reference value);
  void push(value_type &&value);
  void pop();
  void swap(stack &other) noexcept;

 private:
  Container c;
};

template <typename T, typename Container>
stack<T, Container>::stack(const Container &s) : c(s) {}

template <typename T, typename Container>
stack<T, Container>::stack(Container &&other) : c(std::move(other)) {}

template <typename T, typename Container>
stack<T, Container>::stack(stack &&other) : c(std::move(other.c)) {}

template <typename value_type, typename Container>
auto stack<value_type, Container>::operator=(stack &&s) -> stack & {
  swap(s);

  return *this;
}

template <typename T, typename Container>
stack<T, Container>::stack(const stack& other)  : c(std::move(other.c)) {}


template <typename value_type, typename Container>
auto stack<value_type, Container>::top() const -> const_reference {
  return c.back();
}

template <typename value_type, typename Container>
bool stack<value_type, Container>::empty() const {
  return c.empty();
}

template <typename value_type, typename Container>
auto stack<value_type, Container>::size() -> size_type {
  return c.size();
}

template <typename value_type, typename Container>
void stack<value_type, Container>::push(const_reference value) {
  c.push_back(value);
}

template <typename value_type, typename Container>
void stack<value_type, Container>::push(value_type &&value) {
  c.push_back(std::move(value));
}

template <typename value_type, typename Container>
void stack<value_type, Container>::pop() {
  c.pop_back();
}

template <typename value_type, typename Container>
void stack<value_type, Container>::swap(stack &other) noexcept {
  std::swap(c, other.c);
}

}  // namespace s21

#endif  // SRC_CONTAINERS_STACK_H_
