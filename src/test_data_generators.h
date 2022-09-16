#pragma once

#include <string>

using namespace std;

namespace test_data_generators {

// number of AB goes one after another: ABABABAB
string get_best_case_scenario_data_of_size(int n);

// number of A B C D goes one after another: AAAABBBB
string get_worst_case_scenario_data_of_size(int n);

// A B C D letters are randomized
string get_random_data_of_size(int n);

// best case scenario data that is n% randomized
string get_10percent_random_data_of_size(int n);
string get_20percent_random_data_of_size(int n);
string get_30percent_random_data_of_size(int n);
string get_40percent_random_data_of_size(int n);

// best case scenario data that is n% randomized
// technically random data that is (100 - n)% best-caso-mized
string get_60percent_random_data_of_size(int n);
string get_70percent_random_data_of_size(int n);
string get_80percent_random_data_of_size(int n);
string get_90percent_random_data_of_size(int n);

string get_A_letter_of_size(int n);

}
