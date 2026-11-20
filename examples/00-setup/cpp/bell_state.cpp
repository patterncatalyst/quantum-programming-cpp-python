// Bell state in Quantum++ (qpp): the "hello world" that proves the C++ quantum
// toolchain builds and runs. Start in |00>, apply H to qubit 0, then CNOT(0->1).
// The result is (|00> + |11>)/sqrt(2): measuring gives 00 or 11 with equal
// probability, never 01 or 10.
#include <complex>
#include <iostream>
#include <string>

#include <qpp/qpp.hpp>

int main() {
    using namespace qpp;

    ket psi = 00_ket;
    psi = apply(psi, gt.H, {0});
    psi = apply(psi, gt.CNOT, {0, 1});

    std::cout << ">> Bell state |psi> = (|00> + |11>)/sqrt(2)\n";
    std::cout << disp(psi) << "\n\n";

    const idx shots = 1000;
    std::cout << ">> Expected counts over " << shots << " shots (from the state):\n";
    for (idx i = 0; i < static_cast<idx>(psi.rows()); ++i) {
        const double p = std::norm(psi(i));
        if (p > 1e-9) {
            std::string bits;
            bits += std::to_string((i >> 1) & 1U);
            bits += std::to_string(i & 1U);
            std::cout << "  |" << bits << ">: " << static_cast<idx>(p * shots)
                      << "  (p=" << p << ")\n";
        }
    }
    return 0;
}
