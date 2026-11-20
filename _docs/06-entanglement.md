---
title: "Entanglement: Bell, GHZ, and teleportation"
order: 6
part: "First Programs"
description: "Correlations no classical system can reproduce, read from measured counts: the Bell pair, the GHZ state, and quantum teleportation, in Quantum++ and Qiskit."
duration: 25 minutes
---

## Learning objectives

By the end of this chapter you can:

- Read entanglement off measured counts: correlated outcomes, no mixed ones.
- Extend a Bell pair to a three-qubit GHZ state.
- Follow a teleportation circuit and verify it moved a state exactly.

## Why this matters

Entanglement is the resource that makes quantum computing more than fast classical
arithmetic. [Chapter 3]({{ '/docs/03-gates/' | relative_url }}) showed the Bell
state as a state vector; this chapter shows it as counts, where the correlation is
impossible to miss, then builds on it twice: GHZ stretches the correlation across
three qubits, and teleportation uses an entangled pair to move a quantum state
across the register using only two classical bits.

## The Bell pair, in counts

A Hadamard and a CNOT entangle two qubits. Measured over many shots, only the
matching outcomes appear:

{% include excalidraw.html file="bell-circuit" alt="Two qubit wires: the top through a Hadamard then a control dot connected to a target on the bottom wire, both ending in measurement meters" %}

```cpp
QCircuit qc{2, 2};
qc.gate(gt.H, 0);
qc.CTRL(gt.X, 0, 1);
qc.measure(0, 0, false);
qc.measure(1, 1, false);
```

```text
[cpp]$ ./entanglement
>> Bell pair (H, CNOT), 1000 shots
  00: 513
  11: 487
```

The outcomes `01` and `10` never appear. The two qubits are perfectly correlated:
measure one and you know the other, even though neither had a definite value before
the measurement.

## GHZ: correlation across three qubits

Adding a second CNOT spreads the entanglement to a third qubit. The GHZ state is all
three qubits agreeing, so only `000` and `111` show up:

```cpp
qc.gate(gt.H, 0);
qc.CTRL(gt.X, 0, 1);
qc.CTRL(gt.X, 1, 2);
```

```text
>> GHZ state (3 qubits), 1000 shots
  000: 510
  111: 490
```

## Teleportation

Teleportation moves the state of one qubit onto another using a shared Bell pair and
two classical bits. The sender entangles the payload qubit with her half of the
pair, measures both, and sends the two result bits to the receiver, who applies an
`X` and a `Z` correction conditioned on those bits.

{% include excalidraw.html file="teleportation-circuit" alt="Three qubit wires: the payload and the sender half go through a CNOT and Hadamard into measurements, whose classical bits condition X and Z corrections on the receiver qubit" %}

The corrections are classically controlled gates, `cCTRL` in Quantum++, that fire
based on the mid-circuit measurement outcomes:

```cpp
qc.measure(0, 0, false);   // Bell-measure the payload and sender qubits
qc.measure(1, 1, false);
qc.cCTRL(gt.X, 1, 2);      // receiver correction: X if bit 1 set
qc.cCTRL(gt.Z, 0, 2);      // receiver correction: Z if bit 0 set
```

To check the state arrived intact, teleport a known state `RY(pi/3)|0>` and then
undo that preparation on the receiver. If teleportation is exact, the receiver
collapses to `|0>` on every shot, whatever the two random measurement outcomes were:

```text
>> Teleportation of RY(pi/3)|0>, 1000 shots
  target returns to |0> after undo: 1000/1000
```

All 1000 shots return 0: the state was moved exactly.

## The same circuits in Qiskit

Qiskit expresses the classical conditioning with `if_test` blocks instead of
`cCTRL`, and Aer gives the same counts:

```python
with qc.if_test((c1, 1)):
    qc.x(2)
with qc.if_test((c0, 1)):
    qc.z(2)
```

```text
[py]$ python entanglement.py
>> Bell pair (H, CNOT), 1000 shots
  00: 537
  11: 463
>> GHZ state (3 qubits), 1000 shots
  000: 494
  111: 506
>> Teleportation of RY(pi/3)|0>, 1000 shots
  target returns to |0> after undo: 1000/1000
```

## Cross-check

Both libraries show the Bell pair collapsing only to `00`/`11`, GHZ only to
`000`/`111`, and teleportation returning the receiver to `|0>` on all 1000 shots.
The counts differ run to run, but the structure, which outcomes are allowed and
which are forbidden, is identical, and teleportation is exact in both.

## What you learned

Entanglement shows up in counts as correlations with forbidden outcomes: a Bell pair
never lands on `01` or `10`, and GHZ never lands on anything but all-zeros or
all-ones. Teleportation puts that correlation to work, moving a state across the
register with a Bell pair and two classical bits, and the undo-and-measure test
confirms the move is exact. These are the building blocks the algorithms ahead rely
on.

## Verification status

Verified on a Fedora 45 workstation: the Bell and GHZ tests assert only the
correlated outcomes appear and both are well populated; the teleportation test
asserts the receiver returns 0 on every one of 2000 shots, in both GoogleTest and
pytest.

## For deeper coverage

- [Quantum teleportation](https://en.wikipedia.org/wiki/Quantum_teleportation) — the
  protocol and the role of the classical bits.
- [Qiskit dynamic circuits (`if_test`)](https://docs.quantum.ibm.com/guides/classical-feedforward-and-control-flow)
  — mid-circuit measurement and classically conditioned gates.
