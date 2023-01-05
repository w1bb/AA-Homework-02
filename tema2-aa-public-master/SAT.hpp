// Copyright (c) 2023 Valentin-Ioan VINTILA.
// All rights reserved.

#ifndef _WI_SAT_HPP
#define _WI_SAT_HPP

#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <array>
#include <utility>
#include <string>

namespace wi {
namespace SAT {
    void convert_to_at_most_k_cnf_query(
        const int old_variables,
        std::vector< std::vector<int> >& queries,
        const int k
    );
    const int count_variables_in_queries(
        std::vector< std::vector<int> >& queries
    );
    std::vector<bool>* solve_SAT(
        const int var_count,
        std::vector< std::vector<int> >& cnf_query
    );
    void ask_oracle();

}
}

#endif // _WI_SAT_HPP