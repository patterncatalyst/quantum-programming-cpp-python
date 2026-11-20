// Prepare |0>, apply a Hadamard as a raw 2x2 matrix, read the probabilities, and
// sample measurements with a plain RNG. No quantum library: this is the state
// vector in the open.
#include <iostream>
#include <random>

#include "qubit.hpp"

int main() {
    using namespace scratch;

    Qubit psi = apply_gate(hadamard(), ket0);
    const double p0 = prob0(psi);
    const double p1 = prob1(psi);

    std::cout << ">> Single qubit, built from scratch\n";
    std::cout << "state: " << psi[0] << " |0> + " << psi[1] << " |1>\n";
    std::cout << "P(0) = " << p0 << ", P(1) = " << p1 << "\n";

    std::mt19937 rng(12345);
    std::uniform_real_distribution<double> u(0.0, 1.0);
    const int shots = 1000;
    int zeros = 0;
    for (int i = 0; i < shots; ++i) {
        if (u(rng) < p0) {
            ++zeros;
        }
    }
    std::cout << "measured over " << shots << " shots: |0>=" << zeros
              << ", |1>=" << (shots - zeros) << "\n";
    return 0;
}
