#include <cstdint>

#include <gtest/gtest.h>

#include "shor.hpp"

// Order-finding on the classical side: the continued-fraction step recovers the
// true order r = 4 from the informative measurements (1/4 and 3/4).
TEST(Shor, ContinuedFractionRecoversOrder) {
    EXPECT_EQ(scratch::order_from_measurement(4, 4, 15), 4u);   // 4/16 = 1/4
    EXPECT_EQ(scratch::order_from_measurement(12, 4, 15), 4u);  // 12/16 = 3/4
}

TEST(Shor, ModularExponentiation) {
    EXPECT_EQ(scratch::mod_pow(7, 4, 15), 1u);  // order of 7 mod 15 is 4
    EXPECT_EQ(scratch::mod_pow(7, 2, 15), 4u);
}

// When the base shares a factor with N, the classical gcd shortcut returns it
// without any quantum work.
TEST(Shor, ClassicalShortcutWhenNotCoprime) {
    auto [p, q] = scratch::shor_factor(6, 15, 4, 4, 100);  // gcd(6, 15) = 3
    EXPECT_EQ(p * q, 15u);
    const std::uint64_t lo = (p < q) ? p : q;
    EXPECT_EQ(lo, 3u);
}

// The full algorithm factors 15 into 3 and 5.
TEST(Shor, FactorsFifteen) {
    auto [p, q] = scratch::shor_factor(7, 15, 4, 4, 2000);
    EXPECT_EQ(p * q, 15u);
    EXPECT_GT(p, 1u);
    EXPECT_LT(p, 15u);
    const std::uint64_t lo = (p < q) ? p : q;
    const std::uint64_t hi = (p < q) ? q : p;
    EXPECT_EQ(lo, 3u);
    EXPECT_EQ(hi, 5u);
}
