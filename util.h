#include <iostream>
#pragma once

// utils
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

// user_input_utils
bool is_number(char c);
bool check_user_input(std::string user_input);
std::tuple<double, double, char, bool>
handle_user_input(std::string user_input);
std::string get_user_input();
