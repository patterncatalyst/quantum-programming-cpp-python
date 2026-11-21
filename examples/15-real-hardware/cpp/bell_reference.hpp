// Quantum++ is a simulator: there is no hardware backend to submit to. What it gives
// you is the noiseless reference distribution that real-hardware results are compared
// against. Here that reference is the Bell state's perfect 00/11 split. Running on
// actual hardware is a Qiskit + IBM Quantum task, covered on the Python side.
#pragma once

#include <map>
#include <string>

#include <qpp/qpp.hpp>

namespace scratch {

// Noiseless Bell-state counts: the ideal result hardware is measured against.
inline std::map<std::string, qpp::idx> bell_reference_counts(qpp::idx shots) {
    using namespace qpp;
    QCircuit qc{2, 2};
    qc.gate(gt.H, 0);
    qc.CTRL(gt.X, 0, 1);
    qc.measure(0, 0, false);
    qc.measure(1, 1, false);

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
