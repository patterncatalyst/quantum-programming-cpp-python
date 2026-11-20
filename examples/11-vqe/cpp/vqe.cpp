// Find the ground-state energy of a one-qubit Hamiltonian with VQE and compare it
// to the exact smallest eigenvalue.
#include <iomanip>
#include <iostream>

#include "vqe.hpp"

int main() {
    const double c1 = 0.5;  // X coefficient
    const double c2 = 1.0;  // Z coefficient
    const qpp::cmat H = scratch::hamiltonian(c1, c2);

    auto [theta, e_vqe] = scratch::vqe_minimize(H, 2000);
    const double e_exact = scratch::ground_energy(H);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << ">> VQE for H = " << c1 << " X + " << c2 << " Z\n";
    std::cout << "best theta   = " << theta << "\n";
    std::cout << "VQE energy   = " << e_vqe << "\n";
    std::cout << "exact ground = " << e_exact << "\n";
    return 0;
}
