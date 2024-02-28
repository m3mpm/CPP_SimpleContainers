#ifndef SRC_M3MPM_LSQCONTAINER_H_
#define SRC_M3MPM_LSQCONTAINER_H_
#include <stddef.h>
#include <initializer_list>
#include <iostream>

#include "node.h"


namespace m3mpm {
template <typename T>
class LSQContainer : public Node<T> {
 protected:
  size_t size_;
  Node<T> *head_;
  Node<T> *tail_;
 public:
  LSQContainer();
  explicit LSQContainer(const std::initializer_list<T> &items);
  explicit LSQContainer(size_t size_n);
  LSQContainer(const LSQContainer &l);
  LSQContainer(LSQContainer &&l);
  ~LSQContainer();
  LSQContainer<T> &operator=(LSQContainer &&l);
  LSQContainer<T> &operator=(const LSQContainer &l);

  bool empty();
  inline size_t size() { return size_; }

  void swap(LSQContainer &other);
  void push(const T &value);
  void print() const;
  void pop();
};
}  // namespace m3mpm
#include "LSQContainer.cpp"
#endif  // SRC_M3MPM_LSQCONTAINER_H_
