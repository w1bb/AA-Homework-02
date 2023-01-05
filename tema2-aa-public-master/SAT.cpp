// Copyright (c) 2023 Valentin-Ioan VINTILA.
// All rights reserved.

#include "SAT.hpp"

namespace wi {
namespace SAT {



    std::vector<bool>* solve_SAT(
        const int var_count,
        std::vector< std::vector<int> >& cnf_query
    ) {
        // Generate the input file
        std::ofstream fin("sat.in");
        fin << "p cnf " << var_count << " " << cnf_query.size();
        for (std::vector<int>& line : cnf_query) {
            fin.put('\n');
            for (int& x : line)
                fin << x << ' ';
            fin.put('0');
        }
        fin.close();

        // Ask the oracle for a wise answer
        ask_oracle();

        // Check if there is a solution
        std::ifstream fsol("sat.sol");
        std::string sol_type;
        fsol >> sol_type;
        if (sol_type != "True") {
            fsol.close();
            return nullptr;
        }

        // Return said solution
        int n, x;
        fsol >> n;
        // if (n != var_count) {
        //     // std::cout << "THIS IS WEIRD! n (" << n
        //     //           << ") != var_count (" << var_count << ")"
        //     //           << std::endl;
        // }
        std::vector<bool>* result = new (std::vector<bool>);
        result->resize(n + 1);
        for (int i = 0; i < n; ++i) {
            fsol >> x;
            if (x > 0)
                (*result)[x] = true;
        }
        fsol.close();
        return result;
    }

    void ask_oracle() {
        std::string command = "python3 sat_oracle.py sat.in sat.sol";
        std::array<char, 512> buffer{};
        std::string output;

        auto pipe = popen("python3 sat_oracle.py sat.in sat.sol", "r");

        while (!feof(pipe)) {
            if (fgets(buffer.data(), 512, pipe) != nullptr) {
                output += buffer.data();
            }
        }

        auto rc = pclose(pipe);
        if (rc != EXIT_SUCCESS) {
            std::cerr << "Error encountered while running oracle" << std::endl;
            std::cerr << output << std::endl;
            exit(-1);
        }
    }
}
}
