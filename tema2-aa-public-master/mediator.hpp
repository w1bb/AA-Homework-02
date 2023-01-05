// Copyright (c) 2023 Valentin-Ioan VINTILA.
// All rights reserved.

#ifndef _WI_MEDIATOR_HPP
#define _WI_MEDIATOR_HPP

#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <array>
#include <utility>
#include <string>

namespace wi {
namespace Mediator {

    std::vector<bool>* solve_SAT(
        const int var_count,
        std::vector< std::vector<int> >& cnf_query
    );
    void ask_oracle();

}
}

#endif // _WI_MEDIATOR_HPP