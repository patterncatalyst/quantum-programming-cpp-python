// A quantum coin flip as a Quantum++ circuit: Hadamard then measure. Shared by
// the runnable program and its test so both exercise the same code.
#pragma once

#include <utility>

#include <qpp/qpp.hpp>

namespace scratch {

// Run the one-qubit coin-flip circuit `shots` times and return the outcome
// counts as a {zeros, ones} pair.
inline std::pair<qpp::idx, qpp::idx> coin_flip_counts(qpp::idx shots) {
    using namespace qpp;

    QCircuit qc{1, 1};   // one qubit, one classical bit
    qc.gate(gt.H, 0);    // put the qubit in an equal superposition
    qc.measure(0, 0);    // collapse it and record the result in bit 0

    QEngine engine{qc};
    engine.execute(shots);

    idx zeros = 0;
    idx ones = 0;
    for (const auto& [outcome, count] : engine.get_stats().data()) {
        if (outcome.front() == 0) {
            zeros += count;
        } else {
            ones += count;
        }
    }
    return {zeros, ones};
}

}  // namespace scratch
