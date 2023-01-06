// Copyright (c) 2023 Valentin-Ioan VINTILA.
// All rights reserved.

#ifndef _WI_SAT_HPP
#define _WI_SAT_HPP

#include <array>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

namespace wi {
namespace SAT {
    void convert_to_at_most_k_cnf_query(
        const int old_var_count,
        std::vector< std::vector<int> >& query,
        const int k
    );
    int count_variables_in_query(
        std::vector< std::vector<int> >& query
    );
    std::vector<bool>* solve_SAT(
        std::vector< std::vector<int> >& query
    );
    void ask_oracle();

}
}

#endif // _WI_SAT_HPP