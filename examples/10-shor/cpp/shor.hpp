// Shor's algorithm with Quantum++: factor N by finding the order r of a modulo N.
// The quantum part is phase estimation on the modular-multiplication operator
// U_a|y> = |a*y mod N>; its eigenphases are s/r, so the counting register measures
// a multiple of 1/r. Continued fractions turn that into r, and a classical gcd then
// splits N. We use the explicit permutation unitary for U_a: it is the exact
// operator, dense but tiny on a simulator (a scalable circuit decomposition exists
// but is not needed here). Demonstrated on N = 15, a = 7, whose order is 4.
#pragma once

#include <cstdint>
#include <map>
#include <numeric>
#include <utility>
#include <vector>

#include <qpp/qpp.hpp>

namespace scratch {

inline std::uint64_t mod_pow(std::uint64_t base, std::uint64_t exp, std::uint64_t mod) {
    std::uint64_t result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1u) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Permutation unitary for |y> -> |(mul * y) mod N> on m qubits (basis index = the
// integer value, which is qpp's big-endian ordering for the target qubit list).
inline qpp::cmat mul_mod_gate(std::uint64_t mul, std::uint64_t N, qpp::idx m) {
    const qpp::idx dim = static_cast<qpp::idx>(1) << m;
    qpp::cmat U = qpp::cmat::Zero(dim, dim);
    for (qpp::idx y = 0; y < dim; ++y) {
        const qpp::idx image =
            (static_cast<std::uint64_t>(y) < N)
                ? static_cast<qpp::idx>((mul * static_cast<std::uint64_t>(y)) % N)
                : y;
        U(image, y) = 1.0;  // column y maps to row (mul*y mod N)
    }
    return U;
}

// Best denominator < N among the continued-fraction convergents of value / 2^t.
// For an eigenphase s/r this recovers r (when s and r are coprime).
inline std::uint64_t order_from_measurement(std::uint64_t value, qpp::idx t,
                                            std::uint64_t N) {
    std::uint64_t n = value;
    std::uint64_t d = static_cast<std::uint64_t>(1) << t;
    std::uint64_t k_prev2 = 1;  // k_{-2}
    std::uint64_t k_prev1 = 0;  // k_{-1}
    std::uint64_t best = 1;
    while (d != 0) {
        const std::uint64_t a = n / d;
        const std::uint64_t k = a * k_prev1 + k_prev2;
        if (k >= N) {
            break;
        }
        k_prev2 = k_prev1;
        k_prev1 = k;
        if (k > 0) {
            best = k;
        }
        const std::uint64_t rem = n % d;
        n = d;
        d = rem;
    }
    return best;
}

// One order-finding run: phase estimation on U_a with t counting qubits and an
// m-qubit target prepared in |1>. Returns the map of measured counting values.
inline std::map<std::uint64_t, qpp::idx> order_finding_counts(
    std::uint64_t a, std::uint64_t N, qpp::idx t, qpp::idx m, qpp::idx shots) {
    using namespace qpp;
    QCircuit qc{t + m, t};
    qc.gate(gt.X, t + m - 1);  // target register = |1> (least significant qubit)
    for (idx j = 0; j < t; ++j) {
        qc.gate(gt.H, j);
    }
    std::vector<idx> target(m);
    for (idx i = 0; i < m; ++i) {
        target[i] = t + i;
    }
    for (idx j = 0; j < t; ++j) {
        const auto power = static_cast<std::uint64_t>(1) << j;
        const std::uint64_t mul = mod_pow(a, power, N);  // a^(2^j) mod N
        qc.CTRL(mul_mod_gate(mul, N, m), j, target);
    }
    std::vector<idx> counting(t);
    for (idx i = 0; i < t; ++i) {
        counting[i] = i;
    }
    qc.TFQ(counting, false);  // inverse QFT, qubit 0 is the MSB (see Chapter 9)
    for (idx i = 0; i < t; ++i) {
        qc.measure(i, i, false);
    }

    QEngine engine{qc};
    engine.execute(shots);

    std::map<std::uint64_t, idx> values;
    for (const auto& [outcome, count] : engine.get_stats().data()) {
        std::uint64_t v = 0;
        for (idx i = 0; i < t; ++i) {
            v = (v << 1) | static_cast<std::uint64_t>(outcome[i]);
        }
        values[v] += count;
    }
    return values;
}

// Factor N using order-finding for base a. Returns {p, q} with p*q == N, or {1, N}
// if this run of the (probabilistic) algorithm found no non-trivial factor.
inline std::pair<std::uint64_t, std::uint64_t> shor_factor(std::uint64_t a,
                                                           std::uint64_t N,
                                                           qpp::idx t, qpp::idx m,
                                                           qpp::idx shots) {
    // Classical first step: if a and N already share a factor, we are done and no
    // quantum work is needed. Order-finding below assumes gcd(a, N) == 1.
    const std::uint64_t common = std::gcd(a, N);
    if (common > 1 && common < N) {
        return {common, N / common};
    }

    const auto counts = order_finding_counts(a, N, t, m, shots);
    for (const auto& [value, count] : counts) {
        (void)count;
        if (value == 0) {
            continue;
        }
        const std::uint64_t r = order_from_measurement(value, t, N);
        if (r == 0 || mod_pow(a, r, N) != 1 || (r % 2) != 0) {
            continue;  // not a true even order
        }
        const std::uint64_t x = mod_pow(a, r / 2, N);
        if (x == N - 1) {
            continue;  // a^(r/2) == -1 mod N gives only trivial factors
        }
        const std::uint64_t g1 = std::gcd(x - 1, N);
        const std::uint64_t g2 = std::gcd(x + 1, N);
        if (g1 > 1 && g1 < N) {
            return {g1, N / g1};
        }
        if (g2 > 1 && g2 < N) {
            return {g2, N / g2};
        }
    }
    return {1, N};
}

}  // namespace scratch
