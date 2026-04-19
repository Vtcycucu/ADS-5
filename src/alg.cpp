// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include "tstack.h"

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}
bool is_op(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}
std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> st;
  std::string rs;
  for (size_t i = 0; i < inf.size(); i++) {
    char c = inf[i];
    if (c == ' ') continue;
    if (isdigit(c)) {
      while (i < inf.size() && isdigit(inf[i])) {
        rs += inf[i];
        i++;
      }
      rs += ' ';
      i--;
    } else if (c == '(') {
      st.Push(c);
    } else if (c == ')') {
      while (!st.IsEmpty() && st.Top() != '(') {
        rs += st.Top();
        rs += ' ';
        st.Pop();
      }
      st.Pop();
    } else if (is_op(c)) {
      while (!st.IsEmpty() && priority(st.Top()) >= priority(c)) {
        rs += st.Top();
        rs += ' ';
        st.Pop();
      }
      st.Push(c);
    }
  }
  while (!st.IsEmpty()) {
    rs += st.Top();
    rs += ' ';
    st.Pop();
  }
  return rs;
}
int eval(const std::string& post) {
  TStack<int, 100> st;
  for (size_t i = 0; i < post.size(); i++) {
    if (post[i] == ' ') continue;
    if (isdigit(post[i])) {
      int n = 0;
      while (i < post.size() && isdigit(post[i])) {
        n = n * 10 + (post[i] - '0');
        i++;
      }
      st.Push(n);
      i--;
    } else {
      int b = st.Top(); st.Pop();
      int a = st.Top(); st.Pop();
      int rs = 0;
      switch (post[i]) {
        case '+': rs = a + b; break;
        case '-': rs = a - b; break;
        case '*': rs = a * b; break;
        case '/': rs = a / b; break;
      }
      st.Push(rs);
    }
  }
  return st.Top();
}
