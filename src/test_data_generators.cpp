#include "test_data_generators.h"

#include <random>
#include <stdlib.h>
#include <time.h>

namespace {

  string get_randomized_best_case_data_of_size(int n, double share_of_random) {
    auto base_data = test_data_generators::get_best_case_scenario_data_of_size(n);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> letters('A', 'D');
    uniform_int_distribution<int> indices(0, n);

    int letters_to_change = n * share_of_random;
    while (letters_to_change-- > 0) {

      auto random_index = indices(gen);
      base_data[random_index] = letters(gen);
    }

    return base_data;
  }

  string get_bestcasomized_random_data_of_size(int n, double share_of_best_case) {
    auto base_data = test_data_generators::get_random_data_of_size(n);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> indices(0, n);

    int letters_to_change = n * share_of_best_case;
    while (letters_to_change-- > 0) {

      auto random_index = indices(gen);

      // this change is based on assumption that best case scenario is
      // a set of repeated ABAB sequences
      base_data[random_index] = (random_index % 2 != 0) ? 'B' : 'A';
    }

    return base_data;
  }
}

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

  string get_10percent_random_data_of_size(int n) {
    return get_randomized_best_case_data_of_size(n, 0.1);
  }

  string get_20percent_random_data_of_size(int n) {
    return get_randomized_best_case_data_of_size(n, 0.2);
  }

  string get_30percent_random_data_of_size(int n) {
    return get_randomized_best_case_data_of_size(n, 0.3);
  }

  string get_40percent_random_data_of_size(int n) {
    return get_randomized_best_case_data_of_size(n, 0.4);
  }

  string get_60percent_random_data_of_size(int n) {
    return get_bestcasomized_random_data_of_size(n, 0.4);
  }

  string get_70percent_random_data_of_size(int n) {
    return get_bestcasomized_random_data_of_size(n, 0.3);
  }

  string get_80percent_random_data_of_size(int n) {
    return get_bestcasomized_random_data_of_size(n, 0.2);
  }

  string get_90percent_random_data_of_size(int n) {
    return get_bestcasomized_random_data_of_size(n, 0.1);
  }

  string get_A_letter_of_size(int n) {
    return string(n, 'A');
  }
}
