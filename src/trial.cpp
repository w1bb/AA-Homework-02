// Copyright (c) 2023 Valentin-Ioan VINTILA.
// All rights reserved.

// -----------------------------------------------------------------------------
// This file implements the SAT algorithm for the first part of the problem.
// However, once this is implemented, the "rise" section is an easy adaptation
// of the same algorithm.
// -----------------------------------------------------------------------------

// Include standard libraries
#include <vector>
#include <iostream>

// Include the custom SAT communication protocol
#include "SAT.hpp"

int main() {
    // Inside the function, std can be used.
    using namespace std;

    // Generate the original query using the data from the std input
    int n, m, k;
    cin >> n >> m >> k;
    vector< vector<int> > queries;
    queries.resize(n);
    int aux_n, x;
    for (int i = 1; i <= m; ++i) {
        cin >> aux_n;
        for (int j = 0; j < aux_n; ++j) {
            cin >> x;
            queries[x - 1].push_back(i);
        }
    }
    
    // Compute the final solution
    wi::SAT::convert_to_at_most_k_cnf_query(m, queries, k);
    vector<bool>* sol = wi::SAT::solve_SAT(queries);

    if (!sol) {
        // No solution
        cout << "False";
    } else {
        // At least a solution
        cout << "True" << endl;
        vector<int> indeces;

        // Insert the correct indeces
        for (int i = 1; i <= m; ++i)
            if (sol->at(i))
                indeces.push_back(i);
        
        // Fill the rest with other indeces to get exactly k packs
        for (int i = 1; (int)indeces.size() < k && i <= m; ++i)
            if (!sol->at(i))
                indeces.push_back(i);
        
        // Output the final indeces
        cout << indeces.size() << endl;
        for (int x : indeces)
            cout << x << ' ';

        // Free the memory allocated by wi::SAT::solve_SAT.
        delete sol;
    }
    
    return 0;
}
