// Quantum++ side of the framework comparison: print the exact outcome probabilities
// of a shared three-qubit circuit. The Qiskit program prints the same numbers.
#include <iomanip>
#include <iostream>

#include "framework_demo.hpp"

int main() {
    std::cout << ">> Shared circuit in Quantum++: H q0, CNOT q0->q1, RY(pi/2) q2\n";
    std::cout << std::fixed << std::setprecision(3);
    for (const auto& [bits, p] : scratch::outcome_probs()) {
        std::cout << "  " << bits << ": " << p << "\n";
    }
    return 0;
}
