#include <gtest/gtest.h>

#include "framework_demo.hpp"

// The shared circuit yields four equally likely outcomes at 0.25 each: the Bell
// correlation on q0/q1 (00 or 11) times the even split on q2 (0 or 1).
TEST(Frameworks, SharedCircuitProbabilities) {
    auto probs = scratch::outcome_probs();
    EXPECT_EQ(probs.size(), 4u);
    for (const char* bits : {"000", "001", "110", "111"}) {
        ASSERT_TRUE(probs.count(bits) == 1) << bits;
        EXPECT_NEAR(probs[bits], 0.25, 1e-9) << bits;
    }
}
