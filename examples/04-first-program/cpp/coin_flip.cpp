// Your first complete quantum program with Quantum++: build a circuit, run it
// on the simulator for many shots, and read the measured counts. A Hadamard on
// one qubit followed by a measurement is a fair quantum coin: about half the
// shots land on 0 and half on 1.
#include <iostream>

#include "coin_flip.hpp"

int main() {
    const qpp::idx shots = 1000;
    auto [zeros, ones] = scratch::coin_flip_counts(shots);

    std::cout << ">> Quantum coin flip: H then measure, " << shots << " shots\n";
    std::cout << "0: " << zeros << "\n";
    std::cout << "1: " << ones << "\n";
    return 0;
}
