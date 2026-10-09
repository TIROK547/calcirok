#include "user_input_utils.h"
#include "util.h"

#include <iomanip>
#include <iostream>
#include <string>

int main() {
  std::cout << "#----------------------# \n";
  std::cout << "| WELCOME TO CALCIROK! | \n";
  std::cout << "#----------------------# \n";

  // 15 significant digits, so 1234567+1 prints as 1234568, not 1.23457e+06.
  std::cout << std::setprecision(15);

  while (true) {
    auto input = get_user_input();
    if (!input) { // end of input (Ctrl+D)
      std::cout << '\n';
      break;
    }

    const std::string &user_input = *input;
    if (user_input == "q" || user_input == "quit" || user_input == "exit") {
      break;
    }
    if (user_input.empty()) {
      continue;
    }

    if (!check_user_input(user_input)) {
      std::cout << "the input must be 2 whole numbers and an operation "
                   "(+ - * /), e.g. 12+34.\n";
      continue;
    }

    auto [a, b, o, ok] = handle_user_input(user_input);
    if (!ok) {
      std::cout << "something went wrong; \n"
                << "the input must be 2 whole numbers and an operation "
                   "(+ - * /), e.g. 12+34.\n";
      continue;
    }

    auto result = calculate(a, b, o);
    if (!result) {
      std::cout << "can't calculate that (division by zero or result too "
                   "large).\n";
      continue;
    }

    std::cout << *result << '\n';
  }

  return 0;
}
