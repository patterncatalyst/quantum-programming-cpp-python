// Factor 15 with Shor's algorithm: order-finding for a = 7 (order 4) then a gcd.
#include <cstdint>
#include <iostream>

#include "shor.hpp"

int main() {
    const std::uint64_t N = 15;
    const std::uint64_t a = 7;
    const qpp::idx t = 4;  // counting qubits
    const qpp::idx m = 4;  // target qubits (enough for values 0..N-1)
    const qpp::idx shots = 2000;

    std::cout << ">> Shor's algorithm: factor " << N << " with base a = " << a << "\n";
    std::cout << "phase-estimation outcomes (value/" << (1u << t) << "):\n";
    for (const auto& [value, count] : scratch::order_finding_counts(a, N, t, m, shots)) {
        std::cout << "  " << value << "/" << (1u << t) << "  count=" << count << "\n";
    }

    auto [p, q] = scratch::shor_factor(a, N, t, m, shots);
    std::cout << N << " = " << p << " x " << q << "\n";
    return 0;
}
