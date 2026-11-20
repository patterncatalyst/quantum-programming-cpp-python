#include <complex>

#include <gtest/gtest.h>
#include <qpp/qpp.hpp>

TEST(Gates, XFlipsZeroToOne) {
    using namespace qpp;
    ket q = apply(0_ket, gt.X, {0});
    EXPECT_NEAR(std::norm(q(1)), 1.0, 1e-9);
}

TEST(Gates, HThenCnotBuildsBell) {
    using namespace qpp;
    ket psi = apply(apply(00_ket, gt.H, {0}), gt.CNOT, {0, 1});
    EXPECT_NEAR(std::norm(psi(0)), 0.5, 1e-9);  // |00>
    EXPECT_NEAR(std::norm(psi(3)), 0.5, 1e-9);  // |11>
}
