// The noiseless Bell reference from Quantum++. On real hardware you would see the
// same two peaks plus a few counts on 01 and 10 from noise; comparing against this
// ideal is how you read a device's error rate.
#include <iostream>

#include "bell_reference.hpp"

int main() {
    std::cout << ">> Noiseless Bell reference (Quantum++), 1000 shots\n";
    for (const auto& [bits, count] : scratch::bell_reference_counts(1000)) {
        std::cout << "  " << bits << ": " << count << "\n";
    }
    std::cout << "\nQuantum++ has no hardware backend; see the Qiskit side to run on a "
                 "real device.\n";
    return 0;
}
