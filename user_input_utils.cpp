#include "user_input_utils.h"
#include <iostream>
#include <string>

bool is_number(char c) { return c >= '0' && c <= '9'; }

bool is_operation(const char c) {
  bool res = false;
  char operations[4] = {'+', '-', '*', '/'};
  for (char o : operations) {
    if (c == o) {
      res = true;
    }
  }
  return res;
}

bool check_user_input(std::string user_input) {
  bool a = false, b = false, o = false;
  for (char c : user_input) {
    if (!is_number(c) && !is_operation(c)) {
      return false;
    } else if (o && is_operation(c)) {
      return false;
    } else if (is_operation(c)) {
      o = true;
    } else if (o && is_number(c)) {
      b = true;
    } else if (!o && is_number(c)) {
      a = true;
    }
  }
  if (!o) {
    return false;
  }
  if (!a || !b) {
    return false;
  }
  return true;
}

std::tuple<double, double, char, bool>
handle_user_input(std::string user_input) {
  int a = {}, b = {};
  char o = {};

  for (char c : user_input) {
    if (is_number(c)) {
      if (!is_operation(o)) {
        a *= 10;
        a += (c - '0');
      } else {
        b *= 10;
        b += (c - '0');
      }
    } else if (is_operation(c)) {
      o = (char)c;
    } else {
      return {0, 0, ' ', false};
    }
  }
  return {a, b, o, true};
}

std::string get_user_input() {
  std::string user_input;
  std::cout << "what do you want to get calculated?(+, -, /, *)\n: ";
  std::cin >> user_input;
  return user_input;
}
