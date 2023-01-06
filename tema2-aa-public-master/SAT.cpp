// Copyright (c) 2023 Valentin-Ioan VINTILA.
// All rights reserved.

// Include the associated header file 
#include "SAT.hpp"

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
    ) {
        // This lambda function computes the R aux literals
        auto compute_R = [&](const int i, const int j) {
            return (i-1) * k + j + old_var_count;
        };

        // Following the articles, these generate the final query:

        // (Part of) Eq. 1
        query.push_back({-1, compute_R(1, 1)});

        // Eq. 2
        for (int j = 1+1; j <= k; ++j)
            query.push_back({-compute_R(1, j)});
        
        for (int i = 1+1; i < old_var_count; ++i) {
            // (Part of) Eq. 1
            query.push_back({-i, compute_R(i, 1)});
            // (Part of) Eq. 3
            query.push_back({-compute_R(i-1, 1), compute_R(i, 1)});

            for (int j = 1+1; j <= k; ++j) {
                // (Part of) Eq. 3
                query.push_back({-compute_R(i-1, j), compute_R(i, j)});
                // Eq. 4
                query.push_back({-i, -compute_R(i-1, j-1), compute_R(i, j)});
            }

            // (Part of) Eq. 5
            query.push_back({-i, -compute_R(i-1, k)});
        }

        // (Part of) Eq. 5
        if (old_var_count - 1 > 0)
            query.push_back({-old_var_count, -compute_R(old_var_count-1, k)});
    }

    /**
     * This function counts the number of variables (literals) used in a CNF-SAT
     * query.
     *
     * @param query The query for which the count is required.
     * @return The number of variables.
     */
    int count_variables_in_query(
        std::vector< std::vector<int> >& query
    ) {
        int result = 0;
        for (std::vector<int>& v : query)
            result = std::max(
                result,
                *std::max_element(v.begin(), v.end())
            );
        return result;
    }

    /**
     * This function solves a CNF-SAT query by calling a Python SAT solver. The
     * call is made via ask_oracle().
     *
     * @param var_count The number of variables found in the SAT 
     * @return The number of variables.
     */
    std::vector<bool>* solve_SAT(
        std::vector< std::vector<int> >& query
    ) {
        // Get the literal count in the current query
        const int var_count = count_variables_in_query(query);

        // Generate the input file
        std::ofstream fin("sat.in");
        fin << "p cnf " << var_count << " " << query.size();
        for (std::vector<int>& line : query) {
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

    /**
     * This function calls the python SAT implementation.
     */
    void ask_oracle() {
        std::array<char, 512> buffer{};
        std::string output;

        auto pipe = popen(
            "python3 sat_oracle.py sat.in sat.sol",
            "r"
        );

        while (!feof(pipe)) {
            if (fgets(buffer.data(), 512, pipe) != nullptr)
                output += buffer.data();
        }

        auto rc = pclose(pipe);
        if (rc != EXIT_SUCCESS) {
            std::cerr << "Error encountered while running oracle" << std::endl;
            std::cerr << output << std::endl;
            exit(-1);
        }
    }
}
