// Why a CPU simulator caps out around 25-30 qubits: the state vector holds 2^n
// complex amplitudes, so memory doubles with every qubit added. This header exposes
// the state-vector size and a GHZ run so the growth can be measured, not just asserted.
#pragma once

#include <complex>
#include <cstdint>
#include <map>
#include <string>

#include <qpp/qpp.hpp>

namespace scratch {

// Number of complex amplitudes in an n-qubit state vector: 2^n.
inline std::uint64_t statevector_dim(int n) {
    return static_cast<std::uint64_t>(1) << n;
}

// Bytes of memory for the state vector: 2^n times one complex<double> (16 bytes).
inline std::uint64_t statevector_bytes(int n) {
    return statevector_dim(n) * sizeof(std::complex<double>);
}

// Simulate a GHZ state on n qubits and return the measured outcome counts. Only the
// all-zeros and all-ones strings appear no matter how large n is; what grows is the
// hidden cost of holding the 2^n-amplitude state vector that produced them.
inline std::map<std::string, qpp::idx> ghz_counts(int n, qpp::idx shots) {
    using namespace qpp;
    QCircuit qc{static_cast<idx>(n), static_cast<idx>(n)};
    qc.gate(gt.H, 0);
    for (idx i = 1; i < static_cast<idx>(n); ++i) {
        qc.CTRL(gt.X, i - 1, i);
    }
    for (idx i = 0; i < static_cast<idx>(n); ++i) {
        qc.measure(i, i, false);
    }

    QEngine engine{qc};
    engine.execute(shots);

    std::map<std::string, idx> counts;
    for (const auto& [outcome, count] : engine.get_stats().data()) {
        std::string bits;
        for (idx b : outcome) {
            bits += static_cast<char>('0' + b);
        }
        counts[bits] += count;
    }
    return counts;
}

}  // namespace scratch
