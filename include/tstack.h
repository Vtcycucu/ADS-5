// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  T data[size];
  int top_;
 public:
  TStack() : top_(-1) {}
  bool IsEmpty() const {
    return top_ == -1;
  }
  bool IsFull() const {
    return top_ == size - 1;
  }
  void Push(const T& val) {
    if (IsFull()) {
      return;
    }
    data[++top_] = val;
  }
  void Pop() {
    if (IsEmpty()) {
      return;
    }
    top_--;
  }
  T Top() const {
    if (IsEmpty()) {
      return T();
    }
    return data[top_];
  }
};

#endif  // INCLUDE_TSTACK_H_
