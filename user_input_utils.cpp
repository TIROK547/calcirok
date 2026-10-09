#include "user_input_utils.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

namespace {

bool is_digit(char c) { return c >= '0' && c <= '9'; }

bool is_operation(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

} // namespace

bool check_user_input(const std::string &user_input) {
  bool has_lhs = false, has_rhs = false, has_op = false;

  for (char c : user_input) {
    if (!is_digit(c) && !is_operation(c)) {
      return false;
    } else if (has_op && is_operation(c)) {
      return false;
    } else if (is_operation(c)) {
      has_op = true;
    } else if (has_op) {
      has_rhs = true;
    } else {
      has_lhs = true;
    }
  }

  return has_op && has_lhs && has_rhs;
}

std::tuple<double, double, char, bool>
handle_user_input(const std::string &user_input) {
  double a = 0, b = 0;
  char o = '\0';

  for (char c : user_input) {
    if (is_digit(c)) {
      if (o == '\0') {
        a = a * 10 + (c - '0');
      } else {
        b = b * 10 + (c - '0');
      }
    } else if (is_operation(c)) {
      o = c;
    } else {
      return {0, 0, ' ', false};
    }
  }

  return {a, b, o, true};
}

std::optional<std::string> get_user_input() {
  std::cout << "what do you want to get calculated?(+, -, /, *; q to quit)\n: ";

  std::string line;
  if (!std::getline(std::cin, line)) {
    return std::nullopt;
  }

  line.erase(std::remove_if(line.begin(), line.end(),
                            [](unsigned char c) { return std::isspace(c); }),
             line.end());
  return line;
}
