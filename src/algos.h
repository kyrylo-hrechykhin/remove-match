#include <string>
#include <unordered_map>

using namespace std;

namespace algos {

string replace_linear_v1(unordered_map<string, string>& matches, string input);

string replace_linear_v2(unordered_map<string, string>& matches, string input);

// recursive without keeping any result
string replace_recursively_v1(unordered_map<string, string>& matches, string input);

// recursive with keeping results for strings only 8 bytes long
string replace_recursively_v2(unordered_map<string, string>& matches, string input);

// recursive with keeping results for all input string
string replace_recursively_v3(unordered_map<string, string>& matches, string input);

// recursive without keeping any result
string replace_recursively_in_place_v1(unordered_map<string, string>& matches, string input);

// recursive with keeping results for string only 8 bytes long
string replace_recursively_in_place_v2(unordered_map<string, string>& matches, string input);

// recursive with keeping results for all input string
string replace_recursively_in_place_v3(unordered_map<string, string>& matches, string input);

}
