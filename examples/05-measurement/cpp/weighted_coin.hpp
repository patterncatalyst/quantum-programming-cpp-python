// A weighted quantum coin: an RY rotation tilts the qubit so the two outcomes
// are no longer equally likely. The exact probability comes from the squared
// amplitude; the measured fraction comes from sampling. This header exposes both
// so the program and the test can compare them.
#pragma once

#include <complex>
#include <utility>

#include <qpp/qpp.hpp>

namespace scratch {

// Exact probability of measuring 1 after RY(theta) on |0>: sin^2(theta / 2).
inline double prob_one_exact(double theta) {
    using namespace qpp;
    ket psi = apply(0_ket, gt.RY(theta), {0});
    return std::norm(psi(1));
}

// Sample the RY(theta) circuit `shots` times and return the {zeros, ones} counts.
inline std::pair<qpp::idx, qpp::idx> weighted_coin_counts(double theta,
                                                          qpp::idx shots) {
    using namespace qpp;

    QCircuit qc{1, 1};
    qc.gate(gt.RY(theta), 0);
    qc.measure(0, 0);

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
