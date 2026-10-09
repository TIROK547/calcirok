#include "user_input_utils.h"
#include "util.h"
#include <iostream>
#include <string>

double calculate(double a, double b, char o) {
  double res = {};
  switch (o) {
  case '+':
    res = add(a, b);
    break;
  case '-':
    res = subtract(a, b);
    break;
  case '*':
    res = multiply(a, b);
    break;
  case '/':
    res = divide(a, b);
    break;
  default:
    res = 0;
    break;
  }
  return res;
}

int main() {
  std::cout << "#----------------------# \n";
  std::cout << "| WELCOME TO CALCIROK! | \n";
  std::cout << "#----------------------# \n";

  while (true) {
    std::string user_input = get_user_input();
    bool is_valid = check_user_input(user_input);

    if (!is_valid) {
      std::cout << "the input must be 2 valid numbers and a operation(-+*/).\n";
      continue;
    }

    auto [a, b, o, ok] = handle_user_input(user_input);
    if (!ok) {
      std::cout << "something went wrong; \n"
                << "the input must be 2 valid numbers and a operation(-+*/).\n";
      continue;
    }
    std::cout << calculate(a, b, o) << '\n';
  }
  return 0;
}
