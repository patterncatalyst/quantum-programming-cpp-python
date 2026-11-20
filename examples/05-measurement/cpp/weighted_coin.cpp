// Run a weighted coin at two shot counts to watch the measured fraction close in
// on the exact probability. The output of a quantum program is a probability
// distribution; sampling estimates it, and more shots means a tighter estimate.
#include <iomanip>
#include <iostream>
#include <numbers>

#include "weighted_coin.hpp"

int main() {
    const double theta = std::numbers::pi / 3.0;  // tilts P(1) to 0.25
    const double p_one = scratch::prob_one_exact(theta);

    std::cout << ">> Weighted coin: RY(pi/3) then measure\n";
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "exact P(1) = " << p_one << "\n\n";

    for (qpp::idx shots : {100, 10000}) {
        auto [zeros, ones] = scratch::weighted_coin_counts(theta, shots);
        const double fraction = static_cast<double>(ones) / static_cast<double>(shots);
        std::cout << shots << " shots: 0=" << zeros << " 1=" << ones
                  << "  measured P(1) = " << fraction << "\n";
    }
    return 0;
}
