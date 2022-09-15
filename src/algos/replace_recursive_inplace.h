#pragma once

#include <string>
#include <unordered_map>

using namespace std;

namespace algos {

// recursive without keeping results
string replace_recursively_in_place_v1(unordered_map<string, string>& matches, string input);

// recursive with keeping results for string only 8 bytes long or less
string replace_recursively_in_place_v2(unordered_map<string, string>& matches, string input);

// recursive with keeping results for all strings
string replace_recursively_in_place_v3(unordered_map<string, string>& matches, string input);

}
