// Variational quantum eigensolver (VQE) with Quantum++: find the lowest eigenvalue
// of a Hamiltonian by preparing a parameterized state |psi(theta)>, measuring its
// energy <psi(theta)|H|psi(theta)>, and letting a classical optimizer minimize that
// energy. We use a one-qubit Hamiltonian H = c1 X + c2 Z with the ansatz RY(theta),
// so the exact ground energy is known (-sqrt(c1^2 + c2^2)) and the result checkable.
// Real VQE targets many-qubit molecular Hamiltonians the same way.
#pragma once

#include <numbers>
#include <utility>

#include <Eigen/Eigenvalues>
#include <qpp/qpp.hpp>

namespace scratch {

// Single-qubit Hamiltonian c1 * X + c2 * Z.
inline qpp::cmat hamiltonian(double c1, double c2) {
    using namespace qpp;
    return c1 * gt.X + c2 * gt.Z;
}

// Energy of the ansatz RY(theta)|0> under H. On a simulator this expectation is read
// straight from the state vector; on hardware it is estimated from many shots.
inline double energy(double theta, const qpp::cmat& H) {
    using namespace qpp;
    ket psi = apply(0_ket, gt.RY(theta), {0});
    return std::real((psi.adjoint() * H * psi)(0, 0));
}

// Sweep the single parameter over a grid and return {best_theta, min_energy}. A
// real VQE uses a gradient-based optimizer over many parameters; one parameter is
// small enough to minimize by scanning.
inline std::pair<double, double> vqe_minimize(const qpp::cmat& H, int grid) {
    double best_theta = 0.0;
    double best_energy = energy(0.0, H);
    for (int i = 1; i <= grid; ++i) {
        const double theta = 2.0 * std::numbers::pi * i / grid;
        const double e = energy(theta, H);
        if (e < best_energy) {
            best_energy = e;
            best_theta = theta;
        }
    }
    return {best_theta, best_energy};
}

// Exact smallest eigenvalue of H, for comparison.
inline double ground_energy(const qpp::cmat& H) {
    Eigen::SelfAdjointEigenSolver<qpp::cmat> solver(H);
    return solver.eigenvalues()(0);
}

}  // namespace scratch
