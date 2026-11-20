// Verifies the Bell state's amplitudes rather than trusting that the program
// merely ran: |00> and |11> each carry probability 1/2, |01> and |10> zero.
#include <complex>

#include <gtest/gtest.h>
#include <qpp/qpp.hpp>

TEST(BellState, EqualSuperpositionOf00And11) {
    using namespace qpp;

    ket psi = 00_ket;
    psi = apply(psi, gt.H, {0});
    psi = apply(psi, gt.CNOT, {0, 1});

    EXPECT_NEAR(std::norm(psi(0)), 0.5, 1e-9);  // |00>
    EXPECT_NEAR(std::norm(psi(1)), 0.0, 1e-9);  // |01>
    EXPECT_NEAR(std::norm(psi(2)), 0.0, 1e-9);  // |10>
    EXPECT_NEAR(std::norm(psi(3)), 0.5, 1e-9);  // |11>
}
