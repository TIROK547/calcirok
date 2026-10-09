#include "util.h"

#include <cmath>

double add(double a, double b) { return a + b; }

double subtract(double a, double b) { return a - b; }

double multiply(double a, double b) { return a * b; }

double divide(double a, double b) { return a / b; }

std::optional<double> calculate(double a, double b, char op) {
  double res = 0;

  switch (op) {
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
    if (b == 0) {
      return std::nullopt;
    }
    res = divide(a, b);
    break;
  default:
    return std::nullopt;
  }

  if (!std::isfinite(res)) {
    return std::nullopt;
  }
  return res;
}
