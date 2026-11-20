#include <gtest/gtest.h>

#include "coin_flip.hpp"

// With a fair coin, 1000 shots should land close to a 500/500 split. We allow a
// wide band so the test never flakes on sampling noise, while still catching a
// circuit that is stuck on one outcome.
TEST(CoinFlip, SplitsRoughlyEvenly) {
    const qpp::idx shots = 1000;
    auto [zeros, ones] = scratch::coin_flip_counts(shots);

    EXPECT_EQ(zeros + ones, shots);
    EXPECT_GT(zeros, 350);
    EXPECT_GT(ones, 350);
}
