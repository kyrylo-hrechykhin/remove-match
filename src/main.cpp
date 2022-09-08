#include <chrono>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <utility>

#include "algos.h"
#include "test_data_generators.h"

using namespace std;

auto matches = unordered_map<string, string> {
  { "AB", "" },
  { "BA", "" },
  { "CD", "" },
  { "DC", "" }
};

auto tests = vector<pair<string, string>> ({
  { "ABAB", "" },
  { "AABB", "" },
  { "", "" },
  { "BAAB", "" },
  { "D", "D" }
});

int main()
{
  vector<pair<string, string>> failed_tests;
  for (auto test : tests) {
    auto result = algos::replace_linear_v1(matches, test.first);
    
    if (result != test.second)
      failed_tests.push_back({ "replace_linear_v1", test.first });
  }

  for (auto test : tests) {
    auto result = algos::replace_linear_v2(matches, test.first);
    
    if (result != test.second)
      failed_tests.push_back({ "replace_linear_v2", test.first });
  }

  for (auto test : tests) {
    auto result = algos::replace_recursively_v1(matches, test.first);
    
    if (result != test.second)
      failed_tests.push_back({ "replace_recursively_v1", test.first });
  }

  if (!failed_tests.empty()) {
    for (auto& failed_test : failed_tests) {
      cout << failed_test.first << ": " << failed_test.second << "\n";
    }

    return 0;
  }

  string time_results_linear_algo_1;
  for (auto& file : filesystem::recursive_directory_iterator{ filesystem::path("./testing") })
  {
      ifstream fs{ file.path() };

      string input;
      string expected_result;

      fs >> input;
      fs >> expected_result;

      auto begin = chrono::high_resolution_clock::now();

      auto result = algos::replace_linear_v1(matches, input);

      auto end = chrono::high_resolution_clock::now();
      auto time_result = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

      time_results_linear_algo_1 += file.path().u8string();
      time_results_linear_algo_1 += ",";
      time_results_linear_algo_1 += to_string(time_result);
      time_results_linear_algo_1 += ",";
      time_results_linear_algo_1 += ((result != expected_result) ? "not ok" : "ok");
      time_results_linear_algo_1 += "\n";
  }

  {
  ofstream fs("time_results_linear_algo_1.csv");
  fs << time_results_linear_algo_1;
  fs.close();
  }
  
  string time_results_linear_algo_2;
  for (auto& file : filesystem::recursive_directory_iterator{ filesystem::path("./testing") })
  {
      ifstream fs{ file.path() };

      string input;
      string expected_result;

      fs >> input;
      fs >> expected_result;

      auto begin = chrono::high_resolution_clock::now();

      auto result = algos::replace_linear_v2(matches, input);

      auto end = chrono::high_resolution_clock::now();
      auto time_result = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

      time_results_linear_algo_2 += file.path().u8string();
      time_results_linear_algo_2 += ",";
      time_results_linear_algo_2 += to_string(time_result);
      time_results_linear_algo_2 += ",";
      time_results_linear_algo_2 += ((result != expected_result) ? "not ok" : "ok");
      time_results_linear_algo_2 += "\n";
  }

  {
  ofstream fs("time_results_linear_algo_2.csv");
  fs << time_results_linear_algo_2;
  fs.close();
  }

  string time_results_recursive_algo_v1;
  for (auto& file : filesystem::recursive_directory_iterator{ filesystem::path("./testing") })
  {
      ifstream fs{ file.path() };

      string input;
      string expected_result;

      fs >> input;
      fs >> expected_result;

      auto begin = chrono::high_resolution_clock::now();

      auto result = algos::replace_recursively_v1(matches, input);

      auto end = chrono::high_resolution_clock::now();
      auto time_result = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

      time_results_recursive_algo_v1 += file.path().u8string();
      time_results_recursive_algo_v1 += ",";
      time_results_recursive_algo_v1 += to_string(time_result);
      time_results_recursive_algo_v1 += ",";
      time_results_recursive_algo_v1 += ((result != expected_result) ? "not ok" : "ok");
      time_results_recursive_algo_v1 += "\n";
  }

  {
  ofstream fs("time_results_recursive_algo_v1.csv");
  fs << time_results_recursive_algo_v1;
  fs.close();
  }

  return 0;
}
