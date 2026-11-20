// Quantum phase estimation with Quantum++: given a gate U with U|psi> =
// e^{2 pi i phi}|psi>, recover phi into a t-bit counting register. The counting
// qubits are Hadamarded, each controls U raised to a power of two, and an inverse
// QFT turns the accumulated phases into the binary digits of phi. We use the phase
// gate P(2 pi phi) with eigenvector |1>, so phi is known and the estimate checkable.
#pragma once

#include <complex>
#include <cstdint>
#include <numbers>
#include <vector>

#include <qpp/qpp.hpp>

namespace scratch {

// The single-qubit phase gate diag(1, e^{i theta}).
inline qpp::cmat phase_gate(double theta) {
    qpp::cmat m = qpp::cmat::Zero(2, 2);
    m(0, 0) = 1.0;
    m(1, 1) = std::exp(std::complex<double>(0.0, theta));
    return m;
}

// Estimate phi with t counting qubits and return the most-measured integer value
// (the estimate is value / 2^t).
inline std::uint64_t phase_estimate_value(double phi, qpp::idx t, qpp::idx shots) {
    using namespace qpp;
    const double theta = 2.0 * std::numbers::pi * phi;
    const idx eig = t;  // eigenstate qubit sits after the t counting qubits

    QCircuit qc{t + 1, t};
    qc.gate(gt.X, eig);                       // prepare the |1> eigenstate
    for (idx j = 0; j < t; ++j) {
        qc.gate(gt.H, j);
    }
    for (idx j = 0; j < t; ++j) {             // controlled-U^(2^j)
        const auto reps = static_cast<double>(static_cast<std::uint64_t>(1) << j);
        qc.CTRL(phase_gate(theta * reps), j, eig);
    }

    std::vector<idx> counting(t);
    for (idx i = 0; i < t; ++i) {
        counting[i] = i;
    }
    // Inverse QFT on the counting register. swap=false keeps counting qubit 0 as
    // the most significant bit, matching the controlled-U^(2^j) powers above.
    qc.TFQ(counting, false);

    for (idx i = 0; i < t; ++i) {
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
    // Counting qubit 0 is the most significant bit of the estimate.
    std::uint64_t value = 0;
    for (idx i = 0; i < t; ++i) {
        value = (value << 1) | static_cast<std::uint64_t>(best[i]);
    }
    return value;
}

}  // namespace scratch
