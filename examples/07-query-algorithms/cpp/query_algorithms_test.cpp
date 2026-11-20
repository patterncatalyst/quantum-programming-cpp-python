#include <gtest/gtest.h>

#include "bernstein_vazirani.hpp"
#include "deutsch_jozsa.hpp"

// A constant function must yield the all-zero input register on every shot; a
// balanced function must never yield it.
TEST(DeutschJozsa, ConstantIsAlwaysAllZero) {
    const qpp::idx n = 3;
    const qpp::idx shots = 1000;
    EXPECT_EQ(scratch::deutsch_jozsa_all_zero_count(scratch::Oracle::Constant0, n, shots),
              shots);
    EXPECT_EQ(scratch::deutsch_jozsa_all_zero_count(scratch::Oracle::Constant1, n, shots),
              shots);
}

TEST(DeutschJozsa, BalancedIsNeverAllZero) {
    const qpp::idx n = 3;
    const qpp::idx shots = 1000;
    EXPECT_EQ(scratch::deutsch_jozsa_all_zero_count(scratch::Oracle::Balanced, n, shots),
              0);
}

// Bernstein-Vazirani recovers the hidden string exactly.
TEST(BernsteinVazirani, RecoversHiddenString) {
    const qpp::idx shots = 1000;
    EXPECT_EQ(scratch::bernstein_vazirani_recover("1011", shots), "1011");
    EXPECT_EQ(scratch::bernstein_vazirani_recover("0000", shots), "0000");
    EXPECT_EQ(scratch::bernstein_vazirani_recover("111", shots), "111");
}
