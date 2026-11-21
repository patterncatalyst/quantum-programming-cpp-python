// Measure the exponential wall: state-vector memory and GHZ simulation time as the
// qubit count climbs. The memory column doubles with every added qubit.
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>

#include "simulator_limits.hpp"

int main() {
    std::cout << ">> State-vector cost by qubit count (GHZ, 200 shots)\n";
    std::cout << "qubits   amplitudes        memory       sim time\n";
    for (int n : {4, 8, 12, 16, 20}) {
        const auto start = std::chrono::steady_clock::now();
        auto counts = scratch::ghz_counts(n, 200);
        const auto end = std::chrono::steady_clock::now();
        const double ms =
            std::chrono::duration<double, std::milli>(end - start).count();

        const double mib =
            static_cast<double>(scratch::statevector_bytes(n)) / (1024.0 * 1024.0);
        std::cout << std::setw(4) << n << "   " << std::setw(12)
                  << scratch::statevector_dim(n) << "   " << std::setw(10)
                  << std::fixed << std::setprecision(3) << mib << " MiB   "
                  << std::setw(8) << ms << " ms   (outcomes: " << counts.size()
                  << ")\n";
    }
    std::cout << "\nEach qubit doubles the memory: 30 qubits already needs ~16 GiB.\n";
    return 0;
}
