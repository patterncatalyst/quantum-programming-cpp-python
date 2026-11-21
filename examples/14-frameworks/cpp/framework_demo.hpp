// The same circuit in Quantum++ and Qiskit gives the same state, so the choice
// between frameworks is about ergonomics, not correctness. This is the Quantum++
// side: H on q0, CNOT to q1, and RY(pi/2) on q2, read as an exact probability map.
#pragma once

#include <map>
#include <numbers>
#include <string>

#include <qpp/qpp.hpp>

namespace scratch {

inline std::map<std::string, double> outcome_probs() {
    using namespace qpp;
    QCircuit qc{3, 3};
    qc.gate(gt.H, 0);
    qc.CTRL(gt.X, 0, 1);
    qc.gate(gt.RY(std::numbers::pi / 2.0), 2);

    QEngine engine{qc};
    engine.execute();
    ket psi = engine.get_state();

    std::map<std::string, double> probs;
    for (idx b = 0; b < 8; ++b) {
        const double p = std::norm(psi(b));
        if (p > 1e-12) {
            std::string bits;
            for (int q = 2; q >= 0; --q) {   // qubit 0 is the most significant bit
                bits += static_cast<char>('0' + ((b >> q) & 1u));
            }
            probs[bits] = p;
        }
    }
    return probs;
}

}  // namespace scratch
