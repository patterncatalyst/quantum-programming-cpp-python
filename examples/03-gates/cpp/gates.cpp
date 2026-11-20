// Single-qubit gates and a two-qubit circuit with Quantum++. X flips a basis
// state, Z adds a phase, and H followed by CNOT entangles two qubits.
#include <iostream>

#include <qpp/qpp.hpp>

int main() {
    using namespace qpp;

    std::cout << ">> Single-qubit gates (Quantum++)\n";
    std::cout << "X|0> = |1>:\n" << disp(apply(0_ket, gt.X, {0})) << "\n\n";
    std::cout << "Z|1> = -|1>:\n" << disp(apply(1_ket, gt.Z, {0})) << "\n\n";

    std::cout << ">> Two-qubit circuit: H on q0, then CNOT(0 -> 1)\n";
    ket psi = 00_ket;
    psi = apply(psi, gt.H, {0});
    psi = apply(psi, gt.CNOT, {0, 1});
    std::cout << disp(psi) << "\n";
    return 0;
}
