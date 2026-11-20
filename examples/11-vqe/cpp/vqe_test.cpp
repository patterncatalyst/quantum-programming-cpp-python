#include <cmath>

#include <gtest/gtest.h>

#include "vqe.hpp"

// VQE finds the exact ground energy of H = c1 X + c2 Z, which is -sqrt(c1^2 + c2^2).
TEST(Vqe, FindsGroundEnergy) {
    const double c1 = 0.5;
    const double c2 = 1.0;
    const qpp::cmat H = scratch::hamiltonian(c1, c2);

    const double expected = -std::sqrt(c1 * c1 + c2 * c2);
    EXPECT_NEAR(scratch::ground_energy(H), expected, 1e-9);

    auto [theta, e_vqe] = scratch::vqe_minimize(H, 2000);
    (void)theta;
    EXPECT_NEAR(e_vqe, expected, 1e-3);  // within the grid resolution
    EXPECT_GE(e_vqe, expected);          // variational principle: never below ground
}

// With only a Z term the ground energy is -|c2| and VQE reaches it.
TEST(Vqe, PureZHamiltonian) {
    const qpp::cmat H = scratch::hamiltonian(0.0, 1.0);
    auto [theta, e_vqe] = scratch::vqe_minimize(H, 2000);
    (void)theta;
    EXPECT_NEAR(e_vqe, -1.0, 1e-3);
}
