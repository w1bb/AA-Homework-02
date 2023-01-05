// Copyright (c) 2023 Valentin-Ioan VINTILA.
// All rights reserved.

#include "mediator.hpp"
#include <bits/stdc++.h>

using namespace std;

#define COMPUTE_T(i, j) (((i)-1) * k + ((j)-1) + 1 + n)

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

    // Add sequential encoding

    // for (int i = 1; i <= m; ++i) {
    //     for (int j = 1; j <= k; ++j) {
    //         const int t = (i-1) * k + (j-1) + 1 + n;
    //         cout << "Encoding (" << i << ", " << j << "): " << t << endl;
    //     }
    // }

    queries.push_back({-1, COMPUTE_T(1, 1)});
    for (int j = 1+1; j <= k; ++j)
        queries.push_back({-COMPUTE_T(1, j)});
    for (int i = 1+1; i < m; ++i) {
        queries.push_back({-i, COMPUTE_T(i, 1)});
        queries.push_back({-COMPUTE_T(i-1, 1), COMPUTE_T(i, 1)});
        for (int j = 1+1; j <= k; ++j) {
            queries.push_back({-i, -COMPUTE_T(i-1, j-1), COMPUTE_T(i, j)});
            // queries.push_back({-COMPUTE_T(i-1, j), COMPUTE_T(i, j)});
        }
        queries.push_back({-i, -COMPUTE_T(i-1, k)});
    }
    if (m - 1 > 0)
        queries.push_back({-m, -COMPUTE_T(m-1, k)});
    // cout << "DONE\n";

    // // Step 1:
    // for (int i = 1; i <= m-1; ++i) {
    //     const int j = 1;
    //     const int t = (i-1) * k + (j-1) + 1 + n;
    //     queries.push_back({-i, t});
    // }

    // // Step 2:
    // for (int j = 2; j <= m; ++j) {
    //     const int i = 1;
    //     const int t = (i-1) * k + (j-1) + 1 + n;
    //     queries.push_back({-t});
    // }

    // // Step 3:
    // for (int i = 2; i <= m-1; ++i) {
    //     for (int j = 1; j <= k; ++j) {
    //         const int t1 = (i-1-1) * k + (j-1) + 1 + n;
    //         const int t2 = (i-1) * k + (j-1) + 1 + n;
    //         queries.push_back({-t1, t2});
    //     }
    // }

    // // Step 4:
    // for (int i = 2; i <= m-1; ++i) {
    //     for (int j = 2; j <= k; ++j) {
    //         const int t1 = (i-1-1) * k + (j-1-1) + 1 + n;
    //         const int t2 = (i-1) * k + (j-1) + 1 + n;
    //         queries.push_back({-i, -t1, t2});
    //     }
    // }

    // // Step 5:
    // for (int i = 1; i <= m; ++i) {
    //     const int j = k;
    //     const int t = (i-1-1) * k + (j-1) + 1 + n;
    //     queries.push_back({-i, t});
    // }

    // cout << "Here is the final query (" << (m - 1) * k + n << " vars):\n";
    // for (vector<int>& v : queries) {
    //     for (int x : v) {
    //         cout << x << ' ';
    //     }
    //     cout << endl;
    // }

    vector<bool>* sol = wi::Mediator::solve_SAT((m - 1) * k + n, queries);
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
