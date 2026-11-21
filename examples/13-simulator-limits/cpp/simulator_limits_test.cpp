#include <cstdint>

#include <gtest/gtest.h>

#include "simulator_limits.hpp"

// The state vector has 2^n amplitudes and its memory doubles with each qubit.
TEST(SimulatorLimits, StateVectorGrowsExponentially) {
    EXPECT_EQ(scratch::statevector_dim(10), 1024u);
    EXPECT_EQ(scratch::statevector_dim(20), 1048576u);
    // 16 bytes per complex<double> amplitude.
    EXPECT_EQ(scratch::statevector_bytes(10), 1024u * 16u);
    // Each added qubit exactly doubles the memory.
    for (int n = 1; n < 24; ++n) {
        EXPECT_EQ(scratch::statevector_bytes(n), 2u * scratch::statevector_bytes(n - 1));
    }
}

// GHZ stays a two-outcome distribution however many qubits it spans.
TEST(SimulatorLimits, GhzHasTwoOutcomesAtAnySize) {
    auto counts = scratch::ghz_counts(14, 2000);
    EXPECT_EQ(counts.size(), 2u);
    EXPECT_EQ(counts[std::string(14, '0')] + counts[std::string(14, '1')], 2000);
}
