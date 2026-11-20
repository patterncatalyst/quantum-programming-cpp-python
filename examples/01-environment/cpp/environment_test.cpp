#include <complex>

#include <gtest/gtest.h>
#include <qpp/qpp.hpp>

TEST(Environment, HadamardOnZeroIsEqualSuperposition) {
    using namespace qpp;
    ket q = 0_ket;
    q = apply(q, gt.H, {0});
    EXPECT_NEAR(std::norm(q(0)), 0.5, 1e-9);
    EXPECT_NEAR(std::norm(q(1)), 0.5, 1e-9);
}
