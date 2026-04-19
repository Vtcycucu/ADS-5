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
  std::string res;
  for (size_t i = 0; i < inf.size(); i++) {
    char c = inf[i];
    if (c == ' ') continue;
    if (isdigit(c)) {
      while (i < inf.size() && isdigit(inf[i])) {
        res += inf[i];
        i++;
      }
      res += ' ';
      i--; 
    }
    else if (c == '(') {
      st.Push(c);
    }
    else if (c == ')') {
      while (!st.IsEmpty() && st.Top() != '(') {
        res += st.Top();
        res += ' ';
        st.Pop();
      }
      st.Pop();
    }
    else if (is_op(c)) {
      while (!st.IsEmpty() && priority(st.Top()) >= priority(c)) {
        res += st.Top();
        res += ' ';
        st.Pop();
      }
      st.Push(c);
    }
  }
  while (!st.IsEmpty()) {
    res += st.Top();
    res += ' ';
    st.Pop();
  }
  return res;
}
int eval(const std::string& post) {
  TStack<int, 100> st;
  for (size_t i = 0; i < post.size(); i++) {
    if (post[i] == ' ') continue;
    if (isdigit(post[i])) {
      int num = 0;
      while (i < post.size() && isdigit(post[i])) {
        num = num * 10 + (post[i] - '0');
        i++;
      }
      st.Push(num);
      i--;
    }
    else {
      int b = st.Top(); st.Pop();
      int a = st.Top(); st.Pop();
      int res = 0;
      switch (post[i]) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/': res = a / b; break;
      }
      st.Push(res);
    }
  }
  return st.Top();
}
