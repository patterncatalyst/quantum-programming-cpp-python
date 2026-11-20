// Deutsch-Jozsa and Bernstein-Vazirani, each solved in a single oracle query.
#include <iostream>

#include "bernstein_vazirani.hpp"
#include "deutsch_jozsa.hpp"

int main() {
    const qpp::idx n = 3;
    const qpp::idx shots = 1000;

    std::cout << ">> Deutsch-Jozsa on " << n << " input qubits, " << shots
              << " shots\n";
    std::cout << "constant oracle: all-zero outcomes = "
              << scratch::deutsch_jozsa_all_zero_count(scratch::Oracle::Constant0, n,
                                                       shots)
              << "/" << shots << "  (constant => all " << shots << ")\n";
    std::cout << "balanced oracle: all-zero outcomes = "
              << scratch::deutsch_jozsa_all_zero_count(scratch::Oracle::Balanced, n,
                                                       shots)
              << "/" << shots << "  (balanced => 0)\n";

    const std::string secret = "1011";
    std::cout << "\n>> Bernstein-Vazirani, hidden string " << secret << "\n";
    std::cout << "recovered: " << scratch::bernstein_vazirani_recover(secret, shots)
              << "\n";
    return 0;
}
