// Grover's search with Quantum++: find a marked item in an unstructured space of
// 2^n items in about (pi/4) * sqrt(2^n) iterations instead of the classical 2^n.
// Each iteration flips the phase of the marked state (the oracle) and reflects the
// whole state about its average (the diffusion operator); together they rotate
// amplitude onto the marked item so a final measurement almost always finds it.
#pragma once

#include <cmath>
#include <numbers>
#include <string>
#include <utility>
#include <vector>

#include <qpp/qpp.hpp>

namespace scratch {

// A multi-controlled Z on all n qubits: controls are qubits 0..n-2, target n-1.
inline void multi_controlled_z(qpp::QCircuit& qc, qpp::idx n) {
    using namespace qpp;
    if (n == 1) {
        qc.gate(gt.Z, 0);
        return;
    }
    std::vector<idx> controls(n - 1);
    for (idx i = 0; i + 1 < n; ++i) {
        controls[i] = i;
    }
    qc.CTRL(gt.Z, controls, n - 1);
}

// Phase oracle: flip the sign of the amplitude on the `target` basis state.
inline void grover_oracle(qpp::QCircuit& qc, const std::string& target, qpp::idx n) {
    using namespace qpp;
    for (idx i = 0; i < n; ++i) {
        if (target[i] == '0') {
            qc.gate(gt.X, i);
        }
    }
    multi_controlled_z(qc, n);
    for (idx i = 0; i < n; ++i) {
        if (target[i] == '0') {
            qc.gate(gt.X, i);
        }
    }
}

// Diffusion operator: reflect the state about the uniform superposition.
inline void grover_diffusion(qpp::QCircuit& qc, qpp::idx n) {
    using namespace qpp;
    for (idx i = 0; i < n; ++i) {
        qc.gate(gt.H, i);
    }
    for (idx i = 0; i < n; ++i) {
        qc.gate(gt.X, i);
    }
    multi_controlled_z(qc, n);
    for (idx i = 0; i < n; ++i) {
        qc.gate(gt.X, i);
    }
    for (idx i = 0; i < n; ++i) {
        qc.gate(gt.H, i);
    }
}

// Optimal number of Grover iterations for a single marked item among 2^n.
inline qpp::idx grover_iterations(qpp::idx n) {
    const double size = std::pow(2.0, static_cast<double>(n));
    return static_cast<qpp::idx>(std::floor(std::numbers::pi / 4.0 * std::sqrt(size)));
}

// Search for `target` (bit-string, bit 0 first) and return the most-measured
// outcome and the fraction of shots that found it.
inline std::pair<std::string, double> grover_search(const std::string& target,
                                                    qpp::idx shots) {
    using namespace qpp;
    const idx n = static_cast<idx>(target.size());
    QCircuit qc{n, n};

    for (idx i = 0; i < n; ++i) {
        qc.gate(gt.H, i);
    }
    const idx iters = grover_iterations(n);
    for (idx r = 0; r < iters; ++r) {
        grover_oracle(qc, target, n);
        grover_diffusion(qc, n);
    }
    for (idx i = 0; i < n; ++i) {
        qc.measure(i, i, false);
    }

    QEngine engine{qc};
    engine.execute(shots);

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
    return {bits, static_cast<double>(best_count) / static_cast<double>(shots)};
}

}  // namespace scratch
