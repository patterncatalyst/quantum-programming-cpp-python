#include <gtest/gtest.h>

#include "bell_reference.hpp"

// The noiseless reference has only the correlated outcomes: 00 and 11, no 01 or 10.
TEST(RealHardware, NoiselessBellReference) {
    auto counts = scratch::bell_reference_counts(2000);
    EXPECT_EQ(counts.size(), 2u);
    EXPECT_EQ(counts["00"] + counts["11"], 2000);
    EXPECT_EQ(counts.count("01"), 0u);
    EXPECT_EQ(counts.count("10"), 0u);
}
