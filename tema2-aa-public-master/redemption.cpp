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

    vector< set<int> > all_sets;
    all_sets.resize(p+1);

    for (int i = 1; i <= p; ++i) {
        int aux_n;
        cin >> aux_n;
        cin.get();
        for (int j = 0; j < aux_n; ++j) {
            getline(cin, name);
            if (card_to_value[name] > 0) {
                all_sets[i].insert(card_to_value[name]);
            }
        }
        // Remove duplicates
        // sort(all_sets[i].begin(), all_sets[i].end());
        // all_sets[i].erase(
        //     unique(all_sets[i].begin(), all_sets[i].end()),
        //     all_sets[i].end()
        // );
    }

    vector<bool> done_with;
    done_with.resize(last_val + 1);

    vector<int> indeces;

    do {
        int best = 0, best_uncovered = 0;
        for (int x : all_sets[best])
            if (!done_with[x])
                best_uncovered++;

        int current_uncovered;
        for (int i = 1; i < all_sets.size(); ++i) {
            current_uncovered = 0;
            for (int x : all_sets[i])
                if (!done_with[x])
                    current_uncovered++;
            if (current_uncovered > best_uncovered) {
                best = i;
            }
        }
        
        indeces.push_back(best);
        for (int x : all_sets[best]) {
            done_with[x] = true;
        }

        best = 1;
        for (int i = 1; i < done_with.size(); ++i) {
            if (!done_with[i]) {
                best = 0;
                break;
            }
        }
        if (best == 1)
            break;
    } while (1);
    
    cout << indeces.size() << endl;
    for (int x : indeces)
        cout << x << ' ';
    return 0;
}
