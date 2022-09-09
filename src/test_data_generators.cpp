#include "test_data_generators.h"

#include <stdlib.h>
#include <time.h>

namespace test_data_generators {

  string get_best_case_scenario_data_of_size(int n) {
    string input;
    for (int i = 0; i < n / 2; ++i) {
      input += "AB";
    }

    return input;
  }

  string get_worst_case_scenario_data_of_size(int n) {
    string input;

    int i = 0;
    while (i++ < n / 2)
      input += "A";

    while (i++ <= n)
      input += "B";

    return input;
  }

  string get_random_data_of_size(int n) {

    srand(time(0));

    string input;
    while (n-- > 0) {
      input += (rand() % 4) + 'A';
    }

    return input;
  }

}