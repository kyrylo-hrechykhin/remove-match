#include "replace_recursive_inplace.h"

namespace algos {

pair<unsigned int, unsigned int> replace_recursively_in_place_internal_v1(unordered_map<string, string>& matches,
                                                                          unsigned int first,
                                                                          unsigned int last,
                                                                          string& input) {

  if (last - first < 2) {
    return { first, last };
  }

  if (last - first == 2) {
    if (matches.find({ input[first], input[last - 1] }) != matches.end()) {
      input[first] = input[last - 1] = 'x';
      return { first, first };
    }

    return { first, last };
  }

  auto mid_index = (first + last) / 2;
  auto left_range = replace_recursively_in_place_internal_v1(matches, first, mid_index, input);
  auto right_range = replace_recursively_in_place_internal_v1(matches, mid_index, last, input);

  if (left_range.first != left_range.second) {

      while (left_range.first < left_range.second
          && right_range.first < right_range.second
          && matches.find({ input[left_range.second - 1], input[right_range.first] }) != matches.end()) {
          input[left_range.second - 1] = input[right_range.first] = 'x';
      
          --left_range.second;
          ++right_range.first;
      }
  }

  auto insert_index = left_range.second;
  auto new_last = right_range.second;

  if (mid_index != left_range.second) {
      int copy_index = right_range.first;
      while (copy_index < right_range.second && input[copy_index] != 'x') {
          input[insert_index] = input[copy_index];
          input[copy_index] = 'x';

          ++insert_index;
          ++copy_index;
      }

      new_last = insert_index;
      while (insert_index < last && input[insert_index] != 'x') {
          input[insert_index] = 'x';
          ++insert_index;
      }
  }


  return { first, new_last };
}

pair<unsigned int, unsigned int> replace_recursively_in_place_internal_v2(unordered_map<string, string>& matches,
                                                                          unsigned int first,
                                                                          unsigned int last,
                                                                          string& input) {

  if (last - first < 2) {
    return { first, last };
  }

  string input_substr;
  if (last - first <= 8) {
    input_substr = input.substr(first, last - first);
    if (matches.find(input_substr) != matches.end()) {
      auto& result = matches[input_substr];

      if (result.length() == last - first) {
        return { first, last };
      }

      unsigned int insert_index = first;
      auto new_last = first + static_cast<unsigned int>(result.length());
      while (insert_index < new_last) {
        input[insert_index] = result[insert_index - first];
        ++insert_index;
      }

      while(insert_index < last) {
        input[insert_index] = 'x';
        ++insert_index;
      }

      return { first, new_last };
    }

    if (last - first == 2) {
        return { first, last };
    }
  }

  auto mid_index = (first + last) / 2;
  auto left_range = replace_recursively_in_place_internal_v2(matches, first, mid_index, input);
  auto right_range = replace_recursively_in_place_internal_v2(matches, mid_index, last, input);

  if (left_range.first != left_range.second) {

      while (left_range.first < left_range.second
          && right_range.first < right_range.second) {

          string substr = string({ input[left_range.second - 1], input[right_range.first] });
          if (matches.find(substr) == matches.end() ||
              !matches[substr].empty())
              break;

          input[left_range.second - 1] = input[right_range.first] = 'x';

          --left_range.second;
          ++right_range.first;
      }
  }

  auto insert_index = left_range.second;
  auto new_last = right_range.second;

  if (mid_index != left_range.second) {
      int copy_index = right_range.first;
      while (copy_index < right_range.second && input[copy_index] != 'x') {
          input[insert_index] = input[copy_index];
          input[copy_index] = 'x';

          ++insert_index;
          ++copy_index;
      }

      new_last = insert_index;
      while (insert_index < last && input[insert_index] != 'x') {
          input[insert_index] = 'x';
          ++insert_index;
      }
  }

  if (last - first <= 8) {
    matches[input_substr] = input.substr(first, new_last - first);
  }

  return { first, new_last };
}

pair<unsigned int, unsigned int> replace_recursively_in_place_internal_v3(unordered_map<string, string>& matches,
                                                                          unsigned int first,
                                                                          unsigned int last,
                                                                          string& input) {

  if (last - first < 2) {
    return { first, last };
  }

  auto input_substr = input.substr(first, last - first);
  if (matches.find(input_substr) != matches.end()) {
      auto& result = matches[input_substr];

      if (result.length() == last - first) {
          return { first, last };
      }

      unsigned int insert_index = first;
      auto new_last = first + static_cast<unsigned int>(result.length());
      while (insert_index < new_last) {
          input[insert_index] = result[insert_index - first];
          ++insert_index;
      }

      while (insert_index < last) {
          input[insert_index] = 'x';
          ++insert_index;
      }

      return { first, new_last };
  }

  auto mid_index = (first + last) / 2;
  auto left_range = replace_recursively_in_place_internal_v3(matches, first, mid_index, input);
  auto right_range = replace_recursively_in_place_internal_v3(matches, mid_index, last, input);

  if (left_range.first != left_range.second) {

      while (left_range.first < left_range.second
          && right_range.first < right_range.second) {

          string substr = string({ input[left_range.second - 1], input[right_range.first] });
          if (matches.find(substr) == matches.end() ||
              !matches[substr].empty())
              break;

          input[left_range.second - 1] = input[right_range.first] = 'x';

          --left_range.second;
          ++right_range.first;
      }
  }

  auto insert_index = left_range.second;
  auto new_last = right_range.second;

  if (mid_index != left_range.second) {
      int copy_index = right_range.first;
      while (copy_index < right_range.second && input[copy_index] != 'x') {
          input[insert_index] = input[copy_index];
          input[copy_index] = 'x';

          ++insert_index;
          ++copy_index;
      }

      new_last = insert_index;
      while (insert_index < last && input[insert_index] != 'x') {
          input[insert_index] = 'x';
          ++insert_index;
      }
  }

  matches[input_substr] = input.substr(first, new_last - first);
  return { first, new_last };
}

string replace_recursively_in_place_v1(unordered_map<string, string>& matches, string input) {

  if (input.length() < 2)
    return input;

  auto range = replace_recursively_in_place_internal_v1(matches, 0, input.length(), input);

  auto last_iter = input.begin();
  advance(last_iter, range.second);

  input.erase(last_iter, input.end());

  return input;
}

string replace_recursively_in_place_v2(unordered_map<string, string>& matches, string input) {

  if (input.length() < 2)
    return input;

  auto range = replace_recursively_in_place_internal_v2(matches, 0, input.length(), input);

  auto last_iter = input.begin();
  advance(last_iter, range.second);

  input.erase(last_iter, input.end());

  return input;
}

string replace_recursively_in_place_v3(unordered_map<string, string>& matches, string input) {

  if (input.length() < 2)
    return input;

  auto range = replace_recursively_in_place_internal_v3(matches, 0, input.length(), input);

  auto last_iter = input.begin();
  advance(last_iter, range.second);

  input.erase(last_iter, input.end());

  return input;
}

}
