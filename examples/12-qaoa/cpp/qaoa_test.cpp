#include <gtest/gtest.h>

#include "qaoa.hpp"

namespace {
const std::vector<scratch::Edge> kTriangle = {{0, 1}, {1, 2}, {0, 2}};
}

// cut_value counts edges with differing endpoints (qubit 0 is the MSB).
TEST(Qaoa, CutValue) {
    EXPECT_EQ(scratch::cut_value(0b000, kTriangle, 3), 0);  // all same side
    EXPECT_EQ(scratch::cut_value(0b111, kTriangle, 3), 0);
    EXPECT_EQ(scratch::cut_value(0b100, kTriangle, 3), 2);  // one vs two
    EXPECT_EQ(scratch::cut_value(0b011, kTriangle, 3), 2);
}

// Optimized QAOA samples a maximum cut (value 2) as its most likely bitstring.
TEST(Qaoa, SamplesAMaxCut) {
    auto [gamma, beta, exp_cut] = scratch::qaoa_optimize(kTriangle, 3, 40);
    (void)gamma;
    (void)beta;
    EXPECT_GT(exp_cut, 1.0);  // beats the random-assignment average of 1.5... at least > 1

    auto [bits, cut, fraction] = scratch::qaoa_sample(kTriangle, 3, gamma, beta, 4000);
    (void)bits;
    (void)fraction;
    EXPECT_EQ(cut, 2);  // the most-sampled bitstring is an optimal cut
}
