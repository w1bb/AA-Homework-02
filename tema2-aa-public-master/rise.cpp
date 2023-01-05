// Copyright (c) 2023 Valentin-Ioan VINTILA.
// All rights reserved.

#include "SAT.hpp"
#include <bits/stdc++.h>

using namespace std;

int main() {
    int last_val = 0;
    map<string, int> card_to_value;

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
        if (!card_to_value[name]) {
            card_to_value[name] = ++last_val;
        }
    }

    vector< vector<int> > general_queries;
    general_queries.resize(last_val);

    for (int i = 1; i <= p; ++i) {
        int aux_n;
        cin >> aux_n;
        cin.get();
        for (int j = 0; j < aux_n; ++j) {
            getline(cin, name);
            if (card_to_value[name] > 0) {
                general_queries[card_to_value[name] - 1].push_back(i);
            }
        }
    }

    for (int k = 1; k <= p; ++k) {
        vector< vector<int> > queries = general_queries;
        wi::SAT::convert_to_at_most_k_cnf_query(p, queries, k);

        vector<bool>* sol = wi::SAT::solve_SAT(
            wi::SAT::count_variables_in_queries(queries),
            queries
        );
        if (sol) {
            vector<int> indeces;
            for (int i = 1; i <= p; ++i) {
                if (sol->at(i))
                    indeces.push_back(i);
            }
            cout << indeces.size() << endl;
            for (int x : indeces)
                cout << x << ' ';
            break;
        }
    }

    return 0;
}
