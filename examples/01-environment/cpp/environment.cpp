// Confirms the C++ quantum environment: Quantum++ is on the include path and a
// one-qubit Hadamard produces an equal superposition.
#include <iostream>

#include <qpp/qpp.hpp>

int main() {
    using namespace qpp;

    std::cout << ">> C++ quantum environment is ready (Quantum++)\n";
    ket q = 0_ket;             // |0>
    q = apply(q, gt.H, {0});   // Hadamard -> (|0> + |1>)/sqrt(2)
    std::cout << "H|0> =\n" << disp(q) << "\n";
    return 0;
}
