// Copyright (c) 2023 Valentin-Ioan VINTILA.
// All rights reserved.

// -----------------------------------------------------------------------------
// This file implements the SAT algorithm for the second part of the problem.
// Once "trial" was implemented, the "rise" section is an easy adaptation of the
// same algorithm.
// -----------------------------------------------------------------------------

// Include standard libraries
#include <map>
#include <string>
#include <vector>
#include <iostream>

// Include the custom SAT communication protocol
#include "SAT.hpp"

int main() {
    // Inside the function, std can be used.
    using namespace std;

    // Generate the original query using the data from the std input
    map<string, int> card_to_value;
    int last_val = 0;

    int n, m, p;
    cin >> n >> m >> p;

    string name;
    cin.get();
    for (int i = 0; i < n; ++i) {
        getline(cin, name);
        card_to_value[name] = -1; // These cards are already acquired!
    }

    for (int i = 0; i < m; ++i) {
        getline(cin, name);
        if (!card_to_value[name])
            card_to_value[name] = ++last_val;
    }

    vector< vector<int> > general_queries;
    general_queries.resize(last_val);

    for (int i = 1; i <= p; ++i) {
        int aux_n;
        cin >> aux_n;
        cin.get();
        for (int j = 0; j < aux_n; ++j) {
            getline(cin, name);
            if (card_to_value[name] > 0)
                general_queries[card_to_value[name] - 1].push_back(i);
        }
    }

    // Binary search the solution
    // NOTE: In the examples provided, a linear search will be faster, but in a
    //       general case, the algorithm provided bellow shall be superior.
    vector<bool>* sol;
    int k, step;
    for (step = 1; step <= p; step <<= 1);
    for (k = 0; step; step >>= 1) {
        if (k + step <= p) {
            vector< vector<int> > queries = general_queries;
            wi::SAT::convert_to_at_most_k_cnf_query(p, queries, k + step);
            sol = wi::SAT::solve_SAT(queries);
            if (sol == nullptr)
                k += step;
            else
                delete sol;
        }
    }
    // Finally, preserve the correct solution
    wi::SAT::convert_to_at_most_k_cnf_query(p, general_queries, k + 1);
    sol = wi::SAT::solve_SAT(general_queries);

    // Insert the correct indeces
    vector<int> indeces;
    for (int i = 1; i <= p; ++i)
        if (sol->at(i))
            indeces.push_back(i);

    // Output the final indeces
    cout << indeces.size() << endl;
    for (int x : indeces)
        cout << x << ' ';

    // Free the memory allocated by wi::SAT::solve_SAT.
    delete sol;

    return 0;
}
