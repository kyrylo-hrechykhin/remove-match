#include "algos.h"

#include <list>
#include <stack>

namespace algos {

string replace_linear_v1(unordered_map<string, string>& matches, string input) {
  if (input.length() < 2) {
    return input;
  }

  list<char> left_letters;
  left_letters.push_back(input[0]);

  size_t i = 1;
  while (i < input.length()) {

    if (left_letters.empty()) {
      left_letters.push_back(input[i]);
      ++i;
      continue;
    }

    if (matches.find(string({ left_letters.back(), input[i] })) != matches.end()) {
      left_letters.pop_back();
    }
    else {
      left_letters.push_back(input[i]);
    }

    ++i;
  }

  return { left_letters.begin(), left_letters.end() };
}

string replace_linear_v2(unordered_map<string, string>& matches, string input) {
  if (input.length() < 2) {
    return input;
  }

  stack<int> left_letter_indices;
  left_letter_indices.push(0);

  size_t i = 1;
  while (i < input.length()) {

    if (left_letter_indices.empty()) {
      left_letter_indices.push(i);
      ++i;
      continue;
    }

    if (matches.find(string({ input[left_letter_indices.top()], input[i] })) != matches.end()) {
      input[left_letter_indices.top()] = '*';
      input[i] = '*';
      left_letter_indices.pop();
    }
    else {
      left_letter_indices.push(i);
    }

    ++i;
  }

  input.erase(remove(input.begin(), input.end(), '*'), input.end());

  return input;
}

string replace_recursively_v1(unordered_map<string, string>& matches, string input) {
  if (matches.find(input) != matches.end()) {
    return matches[input];
  }
  
  if (input.length() <= 2) {
    return input;
  }

  auto mid_index = input.length() / 2;
  auto left_input = replace_recursively_v1(matches, input.substr(0, mid_index));
  auto right_input = replace_recursively_v1(matches, input.substr(mid_index));

  auto left_input_size = left_input.size();
  auto right_input_size = static_cast<int>(right_input.size());
  auto right_index = 0; 

  if (!left_input.empty() && !right_input.empty()) {
    while (left_input_size > 0 && right_index < right_input_size) {
      if (matches.find(string({ left_input[left_input_size - 1], right_input[right_index] })) == matches.end()) {
        break;
      }

      --left_input_size;
      ++right_index;
    }
  }

  return matches[input] = left_input.substr(0, left_input_size) + right_input.substr(right_index);
}

string replace_recursively_v2(unordered_map<string, string>& matches, string input) {
    if (input.length() < 8 && matches.find(input) != matches.end()) {
        return matches[input];
    }

    if (input.length() <= 2) {
        return input;
    }

    auto mid_index = input.length() / 2;
    auto left_input = replace_recursively_v2(matches, input.substr(0, mid_index));
    auto right_input = replace_recursively_v2(matches, input.substr(mid_index));

    auto left_input_size = left_input.size();
    auto right_input_size = static_cast<int>(right_input.size());
    auto right_index = 0;

    if (!left_input.empty() && !right_input.empty()) {
        while (left_input_size > 0 && right_index < right_input_size) {
            if (matches.find(string({ left_input[left_input_size - 1], right_input[right_index] })) == matches.end()) {
                break;
            }

            --left_input_size;
            ++right_index;
        }
    }

    auto result = left_input.substr(0, left_input_size) + right_input.substr(right_index);
    if (input.length() < 8)
        matches[input] = result;

    return result;
}
}
