namespace m3mpm {

template <typename T>
typename Stack<T>::const_reference Stack<T>::top() {
  return this->size_ ? this->tail_->data_
                     : throw std::logic_error("Stack is empty");
}

}  // namespace m3mpm
