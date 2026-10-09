#pragma once

#include <optional>
#include <string>
#include <tuple>

// True if the input has the shape <digits><operation><digits>, e.g. "12+34".
// Whitespace must already be stripped (get_user_input does this).
bool check_user_input(const std::string &user_input);

// Parses an input that passed check_user_input into {lhs, rhs, operation, ok}.
std::tuple<double, double, char, bool>
handle_user_input(const std::string &user_input);

// Prompts for one line and returns it with all whitespace removed.
// Returns std::nullopt on end of input (Ctrl+D or closed stdin).
std::optional<std::string> get_user_input();
