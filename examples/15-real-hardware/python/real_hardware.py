"""Running on real quantum hardware (optional).

The local path here runs a Bell circuit on the Aer simulator and is what the tests
cover. `run_on_ibm` shows how to submit the same circuit to real IBM Quantum hardware
on the free tier; it needs a free account and the `qiskit-ibm-runtime` package, so it
is NOT run in CI and is not a dependency of this project. On a real device you will see
the two Bell peaks plus a few counts on 01 and 10 from noise.
"""

from __future__ import annotations

from qiskit import QuantumCircuit
from qiskit_aer import AerSimulator


def bell_circuit() -> QuantumCircuit:
    qc = QuantumCircuit(2, 2)
    qc.h(0)
    qc.cx(0, 1)
    qc.measure([0, 1], [0, 1])
    return qc


def bell_counts_local(shots: int) -> dict[str, int]:
    """Noiseless Bell counts on the Aer simulator (the tested, account-free path)."""
    return dict(AerSimulator().run(bell_circuit(), shots=shots).result().get_counts())


def run_on_ibm(shots: int = 1000, backend_name: str | None = None) -> dict[str, int]:
    """Submit the Bell circuit to real IBM Quantum hardware (free tier).

    Reference only: requires a saved IBM Quantum token and `qiskit-ibm-runtime`.
    Set up once with (the ibm_quantum channel was retired in 2025; use
    ibm_quantum_platform):
        from qiskit_ibm_runtime import QiskitRuntimeService
        QiskitRuntimeService.save_account(
            channel="ibm_quantum_platform", token="<YOUR_TOKEN>")
    """
    try:
        from qiskit_ibm_runtime import QiskitRuntimeService, SamplerV2
    except ImportError as exc:  # package not installed in this project
        raise RuntimeError(
            "install qiskit-ibm-runtime and save a free IBM Quantum token to run this"
        ) from exc

    service = QiskitRuntimeService()
    backend = (
        service.backend(backend_name)
        if backend_name
        else service.least_busy(operational=True, simulator=False)
    )
    circuit = bell_circuit()
    transpiled = circuit  # transpile(circuit, backend=backend) in practice
    result = SamplerV2(backend).run([transpiled], shots=shots).result()
    return dict(result[0].data.c.get_counts())


def main() -> None:
    print(">> Bell state on the local simulator (account-free), 1000 shots")
    for bits, count in sorted(bell_counts_local(1000).items()):
        print(f"  {bits}: {count}")
    print("\nTo run on real hardware, see run_on_ibm (needs a free IBM Quantum account).")


if __name__ == "__main__":
    main()
