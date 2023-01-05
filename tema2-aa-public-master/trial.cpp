// Copyright (c) 2023 Valentin-Ioan VINTILA.
// All rights reserved.

#include "SAT.hpp"
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector< vector<int> > queries;
    queries.resize(n);

    // i = 1 .. n => X1 .. Xn => Xi
    // t = n+1 ... =>
    //   i = (t-n-1) / k + 1
    //   j = (t-n-1) % k + 1
    //   => R(i, j)
    // Reversed: t = (i-1) * k + (j-1) + 1 + n
    // Max t: n * (k + 1)

    int aux_n, x;
    for (int i = 1; i <= m; ++i) {
        cin >> aux_n;
        for (int j = 0; j < aux_n; ++j) {
            cin >> x;
            queries[x - 1].push_back(i);
        }
    }
    
    wi::SAT::convert_to_at_most_k_cnf_query(m, queries, k);

    vector<bool>* sol = wi::SAT::solve_SAT(
        wi::SAT::count_variables_in_queries(queries),
        queries
    );
    if (!sol) {
        cout << "False";
    } else {
        cout << "True" << endl;
        vector<int> indeces;
        for (int i = 1; i <= m; ++i) {
            if (sol->at(i))
                indeces.push_back(i);
        }
        for (int i = 1; indeces.size() < k && i <= m; ++i) {
            if (!sol->at(i))
                indeces.push_back(i);
        }
        cout << indeces.size() << endl;
        for (int x : indeces)
            cout << x << ' ';
    }
    return 0;
}
