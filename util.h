#pragma once

#include <optional>

double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

// Applies `op` (+ - * /) to a and b.
// Returns std::nullopt on an unknown operator, division by zero,
// or a result that is not a finite number.
std::optional<double> calculate(double a, double b, char op);
