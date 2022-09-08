#include <string>

using namespace std;

namespace test_data_generators {

  // number of AB goes one after another: ABABABAB
  string get_best_case_scenario_data_of_size(int n);

  // number of A B C D goes one after another: AAAABBBB
  string get_worst_case_scenario_data_of_size(int n);

  // A B C D letters are randomized
  string get_random_data_of_size(int n);

}
