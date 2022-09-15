#pragma once

#include <string>
#include <unordered_map>

using namespace std;

namespace algos {

// recursive without keeping any result
string replace_recursively_v1(unordered_map<string, string>& matches, string input);

// recursive with keeping results for strings only 8 bytes long or less
string replace_recursively_v2(unordered_map<string, string>& matches, string input);

// recursive with keeping results for all input string
string replace_recursively_v3(unordered_map<string, string>& matches, string input);

}
