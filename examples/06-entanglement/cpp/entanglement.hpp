// Entanglement with Quantum++: the Bell pair, the three-qubit GHZ state, and
// quantum teleportation. Each is a QCircuit sampled on the engine so the test
// can assert on measured counts. Measurements are non-destructive so qubit
// indices stay stable through the circuit.
#pragma once

#include <map>
#include <string>
#include <vector>

#include <qpp/qpp.hpp>

namespace scratch {

// Turn an outcome vector like {1, 0, 1} into the string "101".
inline std::string bits(const std::vector<qpp::idx>& outcome) {
    std::string s;
    for (qpp::idx b : outcome) {
        s += static_cast<char>('0' + b);
    }
    return s;
}

// Bell state: H on q0, CNOT to q1, measure both. Only "00" and "11" appear.
inline std::map<std::string, qpp::idx> bell_counts(qpp::idx shots) {
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
        counts[bits(outcome)] += count;
    }
    return counts;
}

// GHZ state on three qubits: H on q0, then CNOT fan-out. Only "000" and "111".
inline std::map<std::string, qpp::idx> ghz_counts(qpp::idx shots) {
    using namespace qpp;
    QCircuit qc{3, 3};
    qc.gate(gt.H, 0);
    qc.CTRL(gt.X, 0, 1);
    qc.CTRL(gt.X, 1, 2);
    qc.measure(0, 0, false);
    qc.measure(1, 1, false);
    qc.measure(2, 2, false);

    QEngine engine{qc};
    engine.execute(shots);

    std::map<std::string, idx> counts;
    for (const auto& [outcome, count] : engine.get_stats().data()) {
        counts[bits(outcome)] += count;
    }
    return counts;
}

// Teleport RY(theta)|0> from q0 to q2, then undo the preparation on q2 and
// measure it. Perfect teleportation means q2 returns to |0> on every shot
// regardless of the two mid-circuit measurement outcomes. Returns how many of
// `shots` measured q2 as 0.
inline qpp::idx teleport_zero_count(double theta, qpp::idx shots) {
    using namespace qpp;
    QCircuit qc{3, 3};

    qc.gate(gt.RY(theta), 0);     // state to teleport, on q0

    qc.gate(gt.H, 1);             // Bell pair across q1, q2
    qc.CTRL(gt.X, 1, 2);

    qc.CTRL(gt.X, 0, 1);          // Bell measurement on q0, q1
    qc.gate(gt.H, 0);
    qc.measure(0, 0, false);      // -> classical bit 0
    qc.measure(1, 1, false);      // -> classical bit 1

    qc.cCTRL(gt.X, 1, 2);         // correction: X on q2 if bit 1 set
    qc.cCTRL(gt.Z, 0, 2);         // correction: Z on q2 if bit 0 set

    qc.gate(gt.RY(-theta), 2);    // undo the preparation on the teleported qubit
    qc.measure(2, 2, false);      // -> classical bit 2, should always be 0

    QEngine engine{qc};
    engine.execute(shots);

    idx zeros = 0;
    for (const auto& [outcome, count] : engine.get_stats().data()) {
        if (outcome[2] == 0) {
            zeros += count;
        }
    }
    return zeros;
}

}  // namespace scratch
