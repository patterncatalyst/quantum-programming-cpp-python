// Grover's search for a marked three-bit item: two iterations concentrate almost
// all of the probability on the target.
#include <iomanip>
#include <iostream>

#include "grover.hpp"

int main() {
    const std::string target = "101";
    const qpp::idx shots = 1000;

    std::cout << ">> Grover search for " << target << " among "
              << (1 << target.size()) << " items, " << shots << " shots\n";
    std::cout << "iterations: " << scratch::grover_iterations(target.size()) << "\n";

    auto [found, fraction] = scratch::grover_search(target, shots);
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "most measured: " << found << "  fraction = " << fraction << "\n";
    return 0;
}
