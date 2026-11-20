// Three faces of entanglement, each run on the simulator and reported as counts:
// the Bell pair, the GHZ state, and quantum teleportation.
#include <iostream>
#include <numbers>

#include "entanglement.hpp"

namespace {

void print_counts(const std::map<std::string, qpp::idx>& counts) {
    for (const auto& [outcome, count] : counts) {
        std::cout << "  " << outcome << ": " << count << "\n";
    }
}

}  // namespace

int main() {
    const qpp::idx shots = 1000;

    std::cout << ">> Bell pair (H, CNOT), " << shots << " shots\n";
    print_counts(scratch::bell_counts(shots));

    std::cout << "\n>> GHZ state (3 qubits), " << shots << " shots\n";
    print_counts(scratch::ghz_counts(shots));

    const double theta = std::numbers::pi / 3.0;
    const qpp::idx ok = scratch::teleport_zero_count(theta, shots);
    std::cout << "\n>> Teleportation of RY(pi/3)|0>, " << shots << " shots\n";
    std::cout << "  target returns to |0> after undo: " << ok << "/" << shots
              << "\n";
    return 0;
}
