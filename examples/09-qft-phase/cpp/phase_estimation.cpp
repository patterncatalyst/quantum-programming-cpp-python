// Estimate a few known phases and print the recovered value and fraction.
#include <cstdint>
#include <iostream>

#include "phase_estimation.hpp"

int main() {
    const qpp::idx t = 3;
    const qpp::idx shots = 1000;

    std::cout << ">> Phase estimation with " << t << " counting qubits, " << shots
              << " shots\n";
    for (double phi : {0.125, 0.25, 0.375, 0.5}) {
        const std::uint64_t value = scratch::phase_estimate_value(phi, t, shots);
        const double estimate = static_cast<double>(value) / (1u << t);
        std::cout << "phi = " << phi << " -> value " << value << "/" << (1u << t)
                  << " = " << estimate << "\n";
    }
    return 0;
}
