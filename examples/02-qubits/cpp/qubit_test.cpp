#include <gtest/gtest.h>

#include "qubit.hpp"

TEST(Qubit, HadamardOnZeroGivesEqualProbabilities) {
    using namespace scratch;
    Qubit psi = apply_gate(hadamard(), ket0);
    EXPECT_NEAR(prob0(psi), 0.5, 1e-12);
    EXPECT_NEAR(prob1(psi), 0.5, 1e-12);
}

TEST(Qubit, XFlipsZeroToOne) {
    using namespace scratch;
    Qubit psi = apply_gate(X, ket0);
    EXPECT_NEAR(prob0(psi), 0.0, 1e-12);
    EXPECT_NEAR(prob1(psi), 1.0, 1e-12);
}

// A non-symmetric matrix pins the row/column convention: a transposed apply_gate
// would give {23, 28} instead of {17, 39}.
TEST(Qubit, ApplyGateIsRowMajor) {
    using namespace scratch;
    const Gate m = {{{{Complex{1, 0}, Complex{2, 0}}}, {{Complex{3, 0}, Complex{4, 0}}}}};
    const Qubit s = {Complex{5, 0}, Complex{6, 0}};
    const Qubit r = apply_gate(m, s);
    EXPECT_NEAR(r[0].real(), 17.0, 1e-12);  // 1*5 + 2*6
    EXPECT_NEAR(r[1].real(), 39.0, 1e-12);  // 3*5 + 4*6
}
