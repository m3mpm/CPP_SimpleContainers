#ifndef SRC_M3MPM_NODE_H_
#define SRC_M3MPM_NODE_H_
namespace m3mpm {
template <typename T>
class Node {
 public:
  T data_;
  Node *pNext_;
  Node *pPrev_;
  Node(): data_(), pNext_(nullptr), pPrev_(nullptr) {}
  explicit Node(const T &data) : Node() {data_ = data;}
};
}  // namespace m3mpm
#endif  // SRC_M3MPM_NODE_H_
