// Copyright (c) 2023 Valentin-Ioan VINTILA.
// All rights reserved.

// -----------------------------------------------------------------------------
// This file implements the approximation algorithm used to solve the set cover
// problem. For a more detailed explanation, please check out the README.
// -----------------------------------------------------------------------------

// Include standard libraries
#include <map>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

// Include the custom SAT communication protocol
#include "SAT.hpp"

int main() {
    // Inside the function, std can be used.
    using namespace std;

    // Generate the sets using the data from the std input
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
        if (!card_to_value[name])
            card_to_value[name] = ++last_val;
    }

    vector< set<int> > all_sets;
    all_sets.resize(p+1);

    for (int i = 1; i <= p; ++i) {
        int aux_n;
        cin >> aux_n;
        cin.get();
        for (int j = 0; j < aux_n; ++j) {
            getline(cin, name);
            if (card_to_value[name] > 0)
                all_sets[i].insert(card_to_value[name]);
        }
    }

    // The result will be a filled indeces vector
    vector<int> indeces;

    if (p <= 9) {
        // If p is small enough, brute force can be applied instead of a general
        // approximation, since speed is NOT a concern in these situations.

        for (int k = 1; k <= p && !indeces.size(); ++k) {
            string bitmask(k, 1);
            bitmask.resize(p, 0);
            do {
                vector<bool> test;
                test.resize(last_val + 1);
                int left = last_val;

                for (int i = 1; i <= p; ++i) {
                    if (bitmask[i-1]) {
                        for (int x : all_sets[i]) {
                            if (!test[x]) {
                                test[x] = true;
                                --left;
                            }
                        }
                    }
                }
                if (!left) {
                    // Insert the correct indeces
                    for (int i = 1; i <= p; ++i)
                        if (bitmask[i-1])
                            indeces.push_back(i);
                    break;
                }
            } while (prev_permutation(bitmask.begin(), bitmask.end()));
        }
    } else {
        // If p is big, a greedy approach can be used instead, since speed IS a
        // concern at this point.

        // A O(n) solution exists, but there is no need to implement such a
        // complex algorithm. Thus, O(n^2) should be good enough.

        vector<bool> done_with;
        done_with.resize(last_val + 1);

        do {
            int best = 0, best_uncovered = 0;
            for (int x : all_sets[best])
                if (!done_with[x])
                    best_uncovered++;

            int current_uncovered;
            for (int i = 1; i < (int)all_sets.size(); ++i) {
                current_uncovered = 0;
                for (int x : all_sets[i])
                    if (!done_with[x])
                        current_uncovered++;
                if (current_uncovered > best_uncovered) {
                    best = i;
                    best_uncovered = current_uncovered;
                }
            }
            
            // Insert the correct indeces
            indeces.push_back(best);
            for (int x : all_sets[best])
                done_with[x] = true;

            best = 1;
            for (int i = 1; i < (int)done_with.size(); ++i) {
                if (!done_with[i]) {
                    best = 0;
                    break;
                }
            }
            if (best == 1)
                break;
        } while (1);
    }
    
    // Output the final indeces
    cout << indeces.size() << endl;
    for (int x : indeces)
        cout << x << ' ';
    return 0;
}
