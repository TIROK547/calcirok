#pragma once
#include <iostream>

bool is_number(char c);
bool check_user_input(std::string user_input);
std::tuple<double, double, char, bool>
handle_user_input(std::string user_input);
std::string get_user_input();
