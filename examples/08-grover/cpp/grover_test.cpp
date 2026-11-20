#include <gtest/gtest.h>

#include "grover.hpp"

// Two iterations on three qubits put over 90% of the probability on the marked
// item, and the most-measured outcome is the target.
TEST(Grover, FindsMarkedItemWithHighProbability) {
    const qpp::idx shots = 2000;
    auto [found, fraction] = scratch::grover_search("101", shots);
    EXPECT_EQ(found, "101");
    EXPECT_GT(fraction, 0.90);
}

TEST(Grover, WorksForADifferentTarget) {
    const qpp::idx shots = 2000;
    auto [found, fraction] = scratch::grover_search("011", shots);
    EXPECT_EQ(found, "011");
    EXPECT_GT(fraction, 0.90);
}

// The optimal iteration count for 8 items is 2.
TEST(Grover, IterationCountForThreeQubits) {
    EXPECT_EQ(scratch::grover_iterations(3), 2);
}
