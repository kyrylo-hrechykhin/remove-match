#include "replace_linear.h"

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

}
