// A single qubit built from scratch: a two-element complex vector and the gates
// as 2x2 matrices, with no quantum library involved. This is the mechanism the
// frameworks hide.
#pragma once

#include <array>
#include <cmath>
#include <complex>

namespace scratch {

using Complex = std::complex<double>;
using Qubit = std::array<Complex, 2>;             // amplitudes of |0> and |1>
using Gate = std::array<std::array<Complex, 2>, 2>;

inline Qubit apply_gate(const Gate& g, const Qubit& s) {
    return {g[0][0] * s[0] + g[0][1] * s[1], g[1][0] * s[0] + g[1][1] * s[1]};
}

inline double prob0(const Qubit& s) { return std::norm(s[0]); }
inline double prob1(const Qubit& s) { return std::norm(s[1]); }

inline const Qubit ket0 = {Complex{1, 0}, Complex{0, 0}};
inline const Qubit ket1 = {Complex{0, 0}, Complex{1, 0}};

inline const Gate X = {{{{Complex{0, 0}, Complex{1, 0}}}, {{Complex{1, 0}, Complex{0, 0}}}}};

inline Gate hadamard() {
    const double s = 1.0 / std::sqrt(2.0);
    return Gate{{{{Complex{s, 0}, Complex{s, 0}}}, {{Complex{s, 0}, Complex{-s, 0}}}}};
}

}  // namespace scratch
