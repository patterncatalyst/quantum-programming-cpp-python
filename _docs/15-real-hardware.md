---
title: "Running on real hardware"
order: 15
part: "Going Further"
description: "An optional look at submitting a circuit to real IBM Quantum hardware on the free tier, with the local simulator as the noiseless reference, in Quantum++ and Qiskit."
duration: 20 minutes
---

## Learning objectives

By the end of this chapter you can:

- Describe what changes when a circuit runs on hardware instead of a simulator.
- Submit a circuit to a real IBM Quantum device on the free tier (optional).
- Compare a noisy hardware result against the noiseless simulator reference.

## Why this matters

Everything so far ran on a simulator, which is noiseless and exact. Real devices are
neither: qubits decohere, gates are imperfect, and readout misfires. Seeing a circuit
you understand run on real hardware, and seeing where the result differs from the ideal,
is the best way to make the gap concrete. This chapter is optional and needs a free IBM
Quantum account; nothing else in the book requires one.

## The noiseless reference

{% include excalidraw.html file="hardware-vs-sim" alt="A Bell circuit feeding both a simulator (ideal 00 and 11) and IBM hardware (noisy, a few 01 and 10), then a compare step that reads the error rate" %}

Quantum++ is a simulator with no hardware backend, so its role here is to provide the
ideal distribution that a device is measured against: a Bell state with only 00 and 11.

```text
[cpp]$ ./bell_reference
>> Noiseless Bell reference (Quantum++), 1000 shots
  00: 516
  11: 484
```

On a real device you would see these two peaks plus a handful of counts on 01 and 10
that should not exist. Those stray counts are the device's error rate made visible.

## Submitting to IBM Quantum

Hardware access goes through Qiskit and the `qiskit-ibm-runtime` package. It is not a
dependency of this project and is not run in the test suite; the local simulator path is
what the tests cover. Set up a free account once, saving the token (the older
`ibm_quantum` channel was retired in 2025, so use `ibm_quantum_platform`):

```python
from qiskit_ibm_runtime import QiskitRuntimeService
QiskitRuntimeService.save_account(channel="ibm_quantum_platform", token="<YOUR_TOKEN>")
```

Then submit the same Bell circuit to the least-busy real device:

```python
from qiskit_ibm_runtime import QiskitRuntimeService, SamplerV2

service = QiskitRuntimeService()
backend = service.least_busy(operational=True, simulator=False)
result = SamplerV2(backend).run([bell_circuit()], shots=1000).result()
counts = result[0].data.c.get_counts()
```

The local, account-free path runs the identical circuit on the simulator so you can see
the shape of the answer before spending real queue time:

```text
[py]$ python real_hardware.py
>> Bell state on the local simulator (account-free), 1000 shots
  00: 508
  11: 492
```

## Reading a hardware result

Compare the device's counts against the noiseless reference. The ratio of the "forbidden"
01 and 10 counts to the total is a rough read on the device's combined gate and readout
error. A result that is still clearly two-peaked is a good device; one where the stray
outcomes rival the real ones is telling you the circuit is too deep for its coherence time.

## What you learned

Real hardware returns the same distribution as the simulator plus noise: the forbidden
outcomes that appear are the error rate made visible. Quantum++ gives the noiseless
reference to compare against; Qiskit, with a free IBM Quantum account, submits the circuit
to a real device. Keeping circuits shallow is what keeps the noise from drowning the
signal.

## Verification status

Verified on a Fedora 45 workstation: the tests cover the account-free paths, asserting the
noiseless Bell reference has only 00 and 11 outcomes in both GoogleTest and pytest. The
IBM Quantum submission is reference material and is not run in CI.

## For deeper coverage

- [IBM Quantum](https://quantum.ibm.com/) — the free-tier account and available devices.
- [qiskit-ibm-runtime](https://docs.quantum.ibm.com/api/qiskit-ibm-runtime) — the Sampler
  primitive and submission workflow.
