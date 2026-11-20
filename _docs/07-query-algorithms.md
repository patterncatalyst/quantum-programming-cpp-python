---
title: "Query algorithms: Deutsch-Jozsa and Bernstein-Vazirani"
order: 7
part: "Algorithms"
description: "Two algorithms that answer in a single query what a classical computer needs many queries for: Deutsch-Jozsa decides constant-versus-balanced, and Bernstein-Vazirani recovers a hidden string."
duration: 25 minutes
---

## Learning objectives

By the end of this chapter you can:

- Explain what an oracle is and how phase kickback turns it into useful interference.
- Run Deutsch-Jozsa to tell a constant function from a balanced one in one query.
- Run Bernstein-Vazirani to recover a hidden bit-string in one query.

## Why this matters

These are the first algorithms where a quantum computer provably beats a classical
one, and they are small enough to read end to end. Both call a function you are only
allowed to query as a black box, an **oracle**, and both extract a global property of
that function in a single call where a classical program would need many. The trick
is the same one the harder algorithms reuse: put the input in superposition, let the
oracle stamp its answer into the phases, and interfere those phases so the answer
lands in the measurement.

## The oracle and phase kickback

An oracle for a function $f$ acts as $|x\rangle|y\rangle \to |x\rangle|y \oplus
f(x)\rangle$. Put the output qubit in the state $|-\rangle$ (an `X` then an `H`) and
the XOR turns into a sign: the oracle multiplies $|x\rangle$ by $(-1)^{f(x)}$ without
changing the output qubit at all. That sign on the input register, **phase
kickback**, is what the final Hadamards turn back into a measurable bit pattern.

## Deutsch-Jozsa

$f$ is promised to be either **constant** (the same value for every input) or
**balanced** (0 on exactly half the inputs, 1 on the other half). Deutsch-Jozsa
decides which in one query: Hadamard the inputs, call the oracle, Hadamard again, and
measure. A constant function leaves the inputs at all-zeros; a balanced one never does.

{% include excalidraw.html file="deutsch-jozsa-circuit" alt="n input qubits and one output qubit: the output is set to the minus state, all qubits pass through Hadamards into the oracle, the inputs get a second layer of Hadamards and are then measured" %}

```cpp
qc.gate(gt.X, out);                   // output qubit to |1>, then H -> |->
for (idx i = 0; i <= n; ++i) qc.gate(gt.H, i);
// oracle: nothing for constant 0; CNOT each input->output for balanced
for (idx i = 0; i < n; ++i) qc.gate(gt.H, i);   // Hadamard the inputs again
```

```text
[cpp]$ ./query_algorithms
>> Deutsch-Jozsa on 3 input qubits, 1000 shots
constant oracle: all-zero outcomes = 1000/1000  (constant => all 1000)
balanced oracle: all-zero outcomes = 0/1000  (balanced => 0)
```

The result is deterministic: every shot of the constant oracle reads `000`, and not
one shot of the balanced oracle does. One query settles a question that classically
needs up to $2^{n-1}+1$ of them.

## Bernstein-Vazirani

Now $f(x) = s \cdot x \bmod 2$ for a hidden string $s$, and the goal is to find $s$.
The circuit is the same Hadamard sandwich; the oracle applies a CNOT from input bit
$i$ to the output exactly where $s_i = 1$. Phase kickback writes $s$ straight into the
input register, so measuring returns it:

```cpp
for (idx i = 0; i < n; ++i)
    if (secret[i] == '1') qc.CTRL(gt.X, i, out);   // CNOT where s has a 1
```

```text
>> Bernstein-Vazirani, hidden string 1011
recovered: 1011
```

Classically, learning an $n$-bit $s$ takes $n$ queries, one per bit. Bernstein-Vazirani
takes exactly one.

## The same algorithms in Qiskit

Qiskit expresses the identical circuits; `h(range(n))` Hadamards a register at once,
and `cx(i, n)` is the oracle's CNOT:

```python
qc.h(range(n + 1))
for i in range(n):
    qc.cx(i, n)        # balanced DJ oracle, or BV where the secret bit is 1
qc.h(range(n))
```

```text
[py]$ python query_algorithms.py
>> Deutsch-Jozsa on 3 input qubits, 1000 shots
constant oracle: all-zero outcomes = 1000/1000
balanced oracle: all-zero outcomes = 0/1000

>> Bernstein-Vazirani, hidden string 1011
recovered: 1011
```

## Cross-check

Both libraries give the identical, deterministic answers: constant reads all-zeros on
every shot, balanced never does, and Bernstein-Vazirani returns `1011` exactly. The
two implementations build the same oracle and the same Hadamard sandwich, so they
agree outcome for outcome, not just on average.

## What you learned

An oracle plus phase kickback turns a function's values into signs on a superposition,
and a layer of Hadamards turns those signs into a measurable answer. Deutsch-Jozsa
reads one global bit (constant or balanced) in a single query; Bernstein-Vazirani
reads a whole hidden string in a single query. The next chapter uses the same
superpose-mark-interfere pattern to search.

## Verification status

Verified on a Fedora 45 workstation: the constant oracles are asserted to read
all-zeros on all 1000 shots and the balanced oracle on none, and Bernstein-Vazirani
is asserted to recover several hidden strings exactly, in both GoogleTest and pytest.

## For deeper coverage

- [Deutsch-Jozsa algorithm](https://en.wikipedia.org/wiki/Deutsch%E2%80%93Jozsa_algorithm)
  — the promise problem and the query-count separation.
- [Bernstein-Vazirani algorithm](https://en.wikipedia.org/wiki/Bernstein%E2%80%93Vazirani_algorithm)
  — recovering the hidden string and why one query suffices.
