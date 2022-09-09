#include <chrono>
#include <fstream>
#include <filesystem>
#include <functional>
#include <iostream>
#include <vector>
#include <utility>

#include "algos.h"
#include "test_data_generators.h"

using namespace std;

auto tests = vector<pair<string, string>> ({
  { "ABAB", "" },
  { "AABB", "" },
  { "", "" },
  { "BAAB", "" },
  { "D", "D" }
});

void test_algo_on_simple_test_data(vector<pair<string, string>>& failed_tests,
  function<string(unordered_map<string, string>&, string)> algo,
  string id) {
  
  auto matches = unordered_map<string, string>{
    { "AB", "" },
    { "BA", "" },
    { "CD", "" },
    { "DC", "" }
  };

  for (auto test : tests) {
      auto result = algos::replace_linear_v1(matches, test.first);

      if (result != test.second)
          failed_tests.push_back({ id, test.first });
  }
}

void test_algo_on_data(function<string(unordered_map<string, string>&, string)> algo, string id) {

  string time_results;
  for (auto& file : filesystem::recursive_directory_iterator{ filesystem::path("./testing") })
  {
      ifstream fs{ file.path() };

      string input;
      string expected_result;

      fs >> input;
      fs >> expected_result;

      auto matches = unordered_map<string, string> {
        { "AB", "" },
        { "BA", "" },
        { "CD", "" },
        { "DC", "" }
      };

      auto begin = chrono::high_resolution_clock::now();

      auto result = algo(matches, input);

      auto end = chrono::high_resolution_clock::now();
      auto time_result = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

      time_results += file.path().u8string();
      time_results += ",";
      time_results += to_string(time_result);
      time_results += ",";
      time_results += ((result != expected_result) ? "not ok" : "ok");
      time_results += "\n";
  }

  string result_file_name = id + ".csv";
  ofstream fs(result_file_name);
  fs << time_results;
  fs.close();
}

int main()
{
  vector<pair<string, string>> failed_tests;
  test_algo_on_simple_test_data(failed_tests, algos::replace_linear_v1, "replace_linear_v1");
  test_algo_on_simple_test_data(failed_tests, algos::replace_linear_v2, "replace_linear_v2");
  test_algo_on_simple_test_data(failed_tests, algos::replace_recursively_v1, "replace_recursively_v1");
  test_algo_on_simple_test_data(failed_tests, algos::replace_recursively_v2, "replace_recursively_v2");

  if (!failed_tests.empty()) {
    for (auto& failed_test : failed_tests) {
      cout << failed_test.first << ": " << failed_test.second << "\n";
    }

    return 0;
  }

  test_algo_on_data(algos::replace_linear_v1, "replace_linear_v1");
  test_algo_on_data(algos::replace_linear_v2, "replace_linear_v2");
  test_algo_on_data(algos::replace_recursively_v1, "replace_recursively_v1");
  test_algo_on_data(algos::replace_recursively_v2, "replace_recursively_v2");
}
