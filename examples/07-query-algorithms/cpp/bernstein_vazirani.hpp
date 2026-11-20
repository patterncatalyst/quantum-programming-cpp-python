// Bernstein-Vazirani with Quantum++: recover a hidden bit-string s in a single
// query. The oracle computes f(x) = s . x (mod 2); the same Hadamard sandwich as
// Deutsch-Jozsa then leaves the input register holding s exactly.
#pragma once

#include <string>
#include <vector>

#include <qpp/qpp.hpp>

namespace scratch {

// Run Bernstein-Vazirani for the hidden string `secret` (e.g. "1011", read with
// bit 0 first) and return the single most-measured outcome as a bit-string.
inline std::string bernstein_vazirani_recover(const std::string& secret,
                                              qpp::idx shots) {
    using namespace qpp;
    const idx n = static_cast<idx>(secret.size());
    const idx out = n;
    QCircuit qc{n + 1, n};

    qc.gate(gt.X, out);                       // output qubit to |1>
    for (idx i = 0; i <= n; ++i) {
        qc.gate(gt.H, i);
    }

    for (idx i = 0; i < n; ++i) {             // oracle: CNOT where secret bit set
        if (secret[i] == '1') {
            qc.CTRL(gt.X, i, out);
        }
    }

    for (idx i = 0; i < n; ++i) {
        qc.gate(gt.H, i);
    }
    for (idx i = 0; i < n; ++i) {
        qc.measure(i, i, false);
    }

    QEngine engine{qc};
    engine.execute(shots);

    // Return the outcome with the highest count as a bit-string (bit 0 first).
    std::vector<idx> best;
    idx best_count = 0;
    for (const auto& [outcome, count] : engine.get_stats().data()) {
        if (count > best_count) {
            best_count = count;
            best = outcome;
        }
    }
    std::string bits;
    for (idx i = 0; i < n; ++i) {
        bits += static_cast<char>('0' + best[i]);
    }
    return bits;
}

}  // namespace scratch
