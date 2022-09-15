#include "test_data_generators.h"

#include <random>
#include <stdlib.h>
#include <time.h>

namespace test_data_generators {

  string get_best_case_scenario_data_of_size(int n) {
    string input;
    for (int i = 0; i < n / 2; ++i) {
      input += "AB";
    }

    if (n % 2 != 0)
        input += "A";

    return input;
  }

  string get_worst_case_scenario_data_of_size(int n) {
    string input;

    int i = 0;
    while (i++ < n / 2)
      input += "A";

    while (i++ <= n)
      input += "B";

    if (n % 2 != 0)
        input += "B";

    return input;
  }

  string get_random_data_of_size(int n) {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis('A', 'D');

    string input;
    while (n-- > 0) {
        input += dis(gen);
    }

    return input;
  }

}
