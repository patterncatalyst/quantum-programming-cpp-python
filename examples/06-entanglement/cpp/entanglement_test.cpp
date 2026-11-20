#include <numbers>

#include <gtest/gtest.h>

#include "entanglement.hpp"

// A Bell pair is perfectly correlated: every shot is "00" or "11", never "01"
// or "10", and the two allowed outcomes are roughly balanced.
TEST(Entanglement, BellPairIsCorrelated) {
    const qpp::idx shots = 2000;
    auto counts = scratch::bell_counts(shots);

    EXPECT_EQ(counts["00"] + counts["11"], shots);
    EXPECT_EQ(counts.count("01"), 0u);
    EXPECT_EQ(counts.count("10"), 0u);
    EXPECT_GT(counts["00"], 700);
    EXPECT_GT(counts["11"], 700);
}

// GHZ extends the correlation to three qubits: only "000" and "111" appear.
TEST(Entanglement, GhzIsAllOrNothing) {
    const qpp::idx shots = 2000;
    auto counts = scratch::ghz_counts(shots);

    EXPECT_EQ(counts["000"] + counts["111"], shots);
    EXPECT_EQ(counts.size(), 2u);
    EXPECT_GT(counts["000"], 700);
    EXPECT_GT(counts["111"], 700);
}

// Teleportation moves the prepared state to the target qubit. Undoing the
// preparation there collapses it back to |0> on every single shot.
TEST(Entanglement, TeleportationIsExact) {
    const qpp::idx shots = 2000;
    const double theta = std::numbers::pi / 3.0;
    EXPECT_EQ(scratch::teleport_zero_count(theta, shots), shots);
}
