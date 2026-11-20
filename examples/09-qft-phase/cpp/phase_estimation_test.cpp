#include <cstdint>

#include <gtest/gtest.h>

#include "phase_estimation.hpp"

// Phases that are exact multiples of 1/8 are recovered exactly with 3 counting
// qubits: the estimate value / 2^t equals phi on every shot.
TEST(PhaseEstimation, RecoversExactPhases) {
    const qpp::idx t = 3;
    const qpp::idx shots = 1000;
    EXPECT_EQ(scratch::phase_estimate_value(0.125, t, shots), 1u);  // 0.001
    EXPECT_EQ(scratch::phase_estimate_value(0.25, t, shots), 2u);   // 0.010
    EXPECT_EQ(scratch::phase_estimate_value(0.375, t, shots), 3u);  // 0.011
    EXPECT_EQ(scratch::phase_estimate_value(0.5, t, shots), 4u);    // 0.100
}
