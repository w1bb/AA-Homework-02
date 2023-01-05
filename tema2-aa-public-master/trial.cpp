// Copyright (c) 2023 Valentin-Ioan VINTILA.
// All rights reserved.

#include "mediator.hpp"
#include <bits/stdc++.h>

using namespace std;

int main() {
    vector< vector<int> > query;
    query.push_back({1, 2, -3, -4});
    query.push_back({-1, 3});
    query.push_back({-2, 4});
    query.push_back({1, 2, 4});
    query.push_back({-2, -3});

    vector<bool>* sol = wi::Mediator::solve_SAT(4, query);
    if (!sol) {
        cout << "No solution!";
    }
    for (bool res : (*sol)) {
        cout << res << ' ';
    }
    return 0;
}
