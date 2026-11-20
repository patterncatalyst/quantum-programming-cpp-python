// Quantum approximate optimization algorithm (QAOA) with Quantum++, solving MaxCut.
// A p=1 circuit alternates a cost layer (a ZZ phase on each graph edge) with a mixer
// (an RX on each qubit); a classical optimizer tunes the two angles to maximize the
// expected number of cut edges. Measuring the tuned circuit then returns a good cut.
// Demonstrated on a triangle, whose maximum cut is 2.
#pragma once

#include <cstdint>
#include <numbers>
#include <string>
#include <tuple>
#include <vector>

#include <qpp/qpp.hpp>

namespace scratch {

struct Edge {
    qpp::idx u;
    qpp::idx v;
};

// Number of edges whose endpoints get different bits (qubit 0 is the most
// significant bit of `bits`).
inline int cut_value(std::uint64_t bits, const std::vector<Edge>& edges, qpp::idx n) {
    int cut = 0;
    for (const auto& e : edges) {
        const auto bu = (bits >> (n - 1 - e.u)) & 1u;
        const auto bv = (bits >> (n - 1 - e.v)) & 1u;
        if (bu != bv) {
            ++cut;
        }
    }
    return cut;
}

// Build the p=1 QAOA circuit for the given angles (no measurement).
inline void build_qaoa(qpp::QCircuit& qc, const std::vector<Edge>& edges, qpp::idx n,
                       double gamma, double beta) {
    using namespace qpp;
    for (idx i = 0; i < n; ++i) {
        qc.gate(gt.H, i);
    }
    for (const auto& e : edges) {                 // cost layer: exp(-i gamma Z_u Z_v)
        qc.CTRL(gt.X, e.u, e.v);
        qc.gate(gt.RZ(2.0 * gamma), e.v);
        qc.CTRL(gt.X, e.u, e.v);
    }
    for (idx i = 0; i < n; ++i) {                 // mixer: exp(-i beta X)
        qc.gate(gt.RX(2.0 * beta), i);
    }
}

// Expected cut value of the tuned state, read from the state vector.
inline double expected_cut(const std::vector<Edge>& edges, qpp::idx n, double gamma,
                           double beta) {
    using namespace qpp;
    QCircuit qc{n, n};
    build_qaoa(qc, edges, n, gamma, beta);
    QEngine engine{qc};
    engine.execute();
    ket psi = engine.get_state();

    double value = 0.0;
    for (idx b = 0; b < (static_cast<idx>(1) << n); ++b) {
        value += std::norm(psi(b)) * cut_value(static_cast<std::uint64_t>(b), edges, n);
    }
    return value;
}

// Grid-search the two angles and return {gamma, beta, expected_cut}.
inline std::tuple<double, double, double> qaoa_optimize(const std::vector<Edge>& edges,
                                                        qpp::idx n, int grid) {
    double best_g = 0.0;
    double best_b = 0.0;
    double best_e = -1.0;
    for (int i = 0; i <= grid; ++i) {
        for (int j = 0; j <= grid; ++j) {
            const double g = std::numbers::pi * i / grid;
            const double b = std::numbers::pi * j / grid;
            const double e = expected_cut(edges, n, g, b);
            if (e > best_e) {
                best_e = e;
                best_g = g;
                best_b = b;
            }
        }
    }
    return {best_g, best_b, best_e};
}

// Sample the tuned circuit and return {best_bitstring, its_cut, its_fraction}.
inline std::tuple<std::string, int, double> qaoa_sample(const std::vector<Edge>& edges,
                                                        qpp::idx n, double gamma,
                                                        double beta, qpp::idx shots) {
    using namespace qpp;
    QCircuit qc{n, n};
    build_qaoa(qc, edges, n, gamma, beta);
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
    std::uint64_t bits = 0;
    std::string label;
    for (idx i = 0; i < n; ++i) {
        bits = (bits << 1) | static_cast<std::uint64_t>(best[i]);
        label += static_cast<char>('0' + best[i]);
    }
    return {label, cut_value(bits, edges, n),
            static_cast<double>(best_count) / static_cast<double>(shots)};
}

}  // namespace scratch
