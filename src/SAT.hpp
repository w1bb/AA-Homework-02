// Copyright (c) 2023 Valentin-Ioan VINTILA.
// All rights reserved.

// -----------------------------------------------------------------------------
// This file implements the effective communication between the current program
// and the python SAT implementation.
// -----------------------------------------------------------------------------

#ifndef _WI_SAT_HPP
#define _WI_SAT_HPP

// Include standard libraries
#include <array>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

// A class / struct would be an overkill for such a simple task. This is why
// everything is defined in two namespaces.
namespace wi::SAT {
    /**
     * This function converts a CNF-SAT query into a CNF-SAT query that only
     * allows at most k of the initial literals to be true.
     *
     * @param old_var_count The original number of variables (literals).
     * @param query The CNF-SAT query that will be modified in-place.
     * @param k The most literals that can be set to true.
     */
    void convert_to_at_most_k_cnf_query(
        const int old_var_count,
        std::vector< std::vector<int> >& query,
        const int k
    );

    /**
     * This function counts the number of variables (literals) used in a CNF-SAT
     * query.
     *
     * @param query The query for which the count is required.
     * @return The number of variables.
     */
    int count_variables_in_query(
        std::vector< std::vector<int> >& query
    );

    /**
     * This function solves a CNF-SAT query by calling a Python SAT solver. The
     * call is made via ask_oracle().
     *
     * @param var_count The number of variables found in the SAT 
     * @return The number of variables.
     */
    std::vector<bool>* solve_SAT(
        std::vector< std::vector<int> >& query
    );

    /**
     * This function calls the python SAT implementation.
     */
    void ask_oracle();
}

#endif // _WI_SAT_HPP
