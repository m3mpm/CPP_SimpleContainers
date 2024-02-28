#ifndef SRC_M3MPM_QUEUE_H_
#define SRC_M3MPM_QUEUE_H_
#include <stddef.h>

#include <initializer_list>
#include <iostream>

#include "stack.h"

namespace m3mpm {
template <typename T>
class Queue : public LSQContainer<T> {
 public:
  using value_type = T;
  using const_reference = const T &;

 public:
  Queue() : LSQContainer<value_type>::LSQContainer() {}
  explicit Queue(const std::initializer_list<value_type> &items)
      : LSQContainer<value_type>::LSQContainer(items) {}

  void pop();
  const_reference front();
  const_reference back() { return LSQContainer<T>::tail_->data_; }
};
}  // namespace m3mpm
#include "queue.cpp"
#endif  // SRC_M3MPM_QUEUE_H_
