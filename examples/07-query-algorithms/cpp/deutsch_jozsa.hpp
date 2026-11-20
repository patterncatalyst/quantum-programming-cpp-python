// Deutsch-Jozsa with Quantum++: decide in a single query whether a function is
// constant or balanced. n input qubits plus one output qubit; after the oracle
// and a final layer of Hadamards, measuring the inputs gives all-zeros exactly
// when the function is constant.
#pragma once

#include <qpp/qpp.hpp>

namespace scratch {

enum class Oracle { Constant0, Constant1, Balanced };

// Run Deutsch-Jozsa on n input qubits with the given oracle and return how many
// of `shots` measured the input register as all-zeros.
inline qpp::idx deutsch_jozsa_all_zero_count(Oracle oracle, qpp::idx n,
                                             qpp::idx shots) {
    using namespace qpp;
    const idx out = n;  // the output qubit sits after the n inputs
    QCircuit qc{n + 1, n};

    qc.gate(gt.X, out);                       // output qubit to |1>
    for (idx i = 0; i <= n; ++i) {
        qc.gate(gt.H, i);                     // Hadamard every qubit
    }

    switch (oracle) {                         // U_f: |x>|y> -> |x>|y xor f(x)>
        case Oracle::Constant0:
            break;                            // f(x) = 0: do nothing
        case Oracle::Constant1:
            qc.gate(gt.X, out);               // f(x) = 1: flip the output
            break;
        case Oracle::Balanced:
            for (idx i = 0; i < n; ++i) {     // f(x) = x_0 xor ... xor x_{n-1}
                qc.CTRL(gt.X, i, out);
            }
            break;
    }

    for (idx i = 0; i < n; ++i) {
        qc.gate(gt.H, i);                     // Hadamard the inputs again
    }
    for (idx i = 0; i < n; ++i) {
        qc.measure(i, i, false);             // measure only the inputs
    }

    QEngine engine{qc};
    engine.execute(shots);

    idx all_zero = 0;
    for (const auto& [outcome, count] : engine.get_stats().data()) {
        bool zero = true;
        for (idx i = 0; i < n; ++i) {
            if (outcome[i] != 0) {
                zero = false;
                break;
            }
        }
        if (zero) {
            all_zero += count;
        }
    }
    return all_zero;
}

}  // namespace scratch
