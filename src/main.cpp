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

void test_algo_on_data(function<string(unordered_map<string, string>&, string)> algo, string id, int iterations) {

  cout << "test algo '" << id << "' on data\n";

  string time_results;
  for (auto& file : filesystem::recursive_directory_iterator{ filesystem::path("./testing") })
  {
      ifstream fs{ file.path() };

      string input;
      string expected_result;

      fs >> input;
      fs >> expected_result;

      time_results += file.path().u8string();

      for (int i = 0; i < iterations; ++i) {
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

        time_results += ",";
        time_results += to_string(time_result);
      }
      
      time_results += "\n";
  }

  string result_file_name = id + ".csv";
  ofstream fs(result_file_name);
  fs << time_results;
  fs.close();
}

void test_algo_on_data(function<string(unordered_map<string, string>&, string)> algo, string id, const string& input, int iterations) {

    string time_results = to_string(input.length());

    for (int i = 0; i < iterations; ++i) {
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

        time_results += ",";
        time_results += to_string(time_result);
    }

    time_results += "\n";

    string result_file_name = id + ".csv";
    ofstream fs(result_file_name, ios_base::app);
    fs << time_results;
    fs.close();
}

void test_runner(std::function<string(int)> generate_input, string id, int first, int last, int number_of_runs = 1000) {

    for (int i = first; i <= last; i += last / number_of_runs) {
      auto input = generate_input(i);
      cout << "input of size: " << to_string(input.length()) << ": " << to_string((i * 100 / last)) << " % \n";

      test_algo_on_data(algos::replace_linear_v2, id + "_linear_v2", input, 20);
      test_algo_on_data(algos::replace_recursively_v1, id + "_recursively_v1", input, 20);
      test_algo_on_data(algos::replace_recursively_v2, id + "_recursively_v2", input, 20);
      test_algo_on_data(algos::replace_recursively_v3, id + "_recursively_v3", input, 20);
      test_algo_on_data(algos::replace_recursively_in_place_v1, id + "_recursively_in_place_v1", input, 20);
  }
}

int main()
{
  vector<pair<string, string>> failed_tests;
  test_algo_on_simple_test_data(failed_tests, algos::replace_linear_v1, "replace_linear_v1");
  test_algo_on_simple_test_data(failed_tests, algos::replace_linear_v2, "replace_linear_v2");
  test_algo_on_simple_test_data(failed_tests, algos::replace_recursively_v1, "replace_recursively_v1");
  test_algo_on_simple_test_data(failed_tests, algos::replace_recursively_v2, "replace_recursively_v2");
  test_algo_on_simple_test_data(failed_tests, algos::replace_recursively_v3, "replace_recursively_v3");
  test_algo_on_simple_test_data(failed_tests, algos::replace_recursively_in_place_v1, "replace_recursively_in_place_v1");

  if (!failed_tests.empty()) {
    for (auto& failed_test : failed_tests) {
      cout << failed_test.first << ": " << failed_test.second << "\n";
    }

    return 0;
  }

  test_runner(test_data_generators::get_random_data_of_size, "random", 0, 1000);
  //test_runner(test_data_generators::get_random_data_of_size, "random", 1000, 1000000);
  // test_runner(test_data_generators::get_random_data_of_size, "random", 1000000, 100000000, 100);

  test_runner(test_data_generators::get_best_case_scenario_data_of_size, "best_case", 0, 1000);
  test_runner(test_data_generators::get_best_case_scenario_data_of_size, "best_case", 1000, 1000000);
  // test_runner(test_data_generators::get_best_case_scenario_data_of_size, "best_case", 1000000, 100000000, 100);
}
