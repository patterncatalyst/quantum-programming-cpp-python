#include <numbers>

#include <gtest/gtest.h>

#include "weighted_coin.hpp"

// RY(pi/3) on |0> should put exactly a quarter of the probability on outcome 1.
TEST(WeightedCoin, ExactProbabilityIsOneQuarter) {
    const double theta = std::numbers::pi / 3.0;
    EXPECT_NEAR(scratch::prob_one_exact(theta), 0.25, 1e-9);
}

// With enough shots the measured fraction should sit close to the exact 0.25.
TEST(WeightedCoin, SampledFractionTracksExact) {
    const double theta = std::numbers::pi / 3.0;
    const qpp::idx shots = 20000;
    auto [zeros, ones] = scratch::weighted_coin_counts(theta, shots);

    EXPECT_EQ(zeros + ones, shots);
    const double fraction = static_cast<double>(ones) / static_cast<double>(shots);
    EXPECT_NEAR(fraction, 0.25, 0.03);
}
