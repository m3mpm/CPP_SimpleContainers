#ifndef SRC_M3MPM_STACK_H_
#define SRC_M3MPM_STACK_H_
#include <stddef.h>

#include <initializer_list>
#include <iostream>

#include "LSQContainer.h"

namespace m3mpm {
template <typename T>
class Stack : public LSQContainer<T> {
 public:
  using value_type = T;
  using const_reference = const T &;

 public:
  Stack() : LSQContainer<value_type>::LSQContainer() {}
  explicit Stack(const std::initializer_list<value_type> &items)
      : LSQContainer<value_type>::LSQContainer(items) {}

  const_reference top();
};
}  // namespace m3mpm
#include "stack.cpp"
#endif  // SRC_M3MPM_STACK_H_
