// QAOA for MaxCut on a triangle: optimize the two angles, then sample the solution.
#include <iomanip>
#include <iostream>

#include "qaoa.hpp"

int main() {
    const qpp::idx n = 3;
    const std::vector<scratch::Edge> triangle = {{0, 1}, {1, 2}, {0, 2}};
    const qpp::idx shots = 2000;

    auto [gamma, beta, exp_cut] = scratch::qaoa_optimize(triangle, n, 40);
    auto [bits, cut, fraction] = scratch::qaoa_sample(triangle, n, gamma, beta, shots);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << ">> QAOA MaxCut on a triangle (max cut = 2)\n";
    std::cout << "best gamma = " << gamma << ", beta = " << beta << "\n";
    std::cout << "expected cut = " << exp_cut << "\n";
    std::cout << "most-sampled " << bits << " with cut " << cut << " (fraction "
              << fraction << ")\n";
    return 0;
}
