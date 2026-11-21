# Demo walkthrough: speaker runbook

Speaker-only runbook for the live demo that accompanies the companion deck
(`quantum-programming-cpp-python-deck-r09.0.pptx`). This file stays with the deck
and is excluded from the published site. The reader-facing version of the same
demo is Appendix D in the book.

The demo runs four commands and tells one story: a quantum program is a circuit
you run, entanglement is real and measurable, the speed-ups are real, and Shor is
the bridge to the cryptography your audience already depends on. Total runtime is
about 6 to 8 minutes of talking over roughly 2 minutes of command output, once the
images are built.

**Golden rule:** build the images *before* you walk on stage. Step 1 takes minutes
on a cold cache and should not be done live.

---

## Pre-flight (do this before the session)

Run every command once, in order, on the machine you will present from. If all
four steps print what this runbook says, you are ready.

```bash
cd quantum-programming-cpp-python
docker compose build                                   # ~minutes, do it now
docker build -t quantum-cpp-build --target build -f containers/cpp/Containerfile .
```

Checklist:

- [ ] `docker compose build` finished clean (both test suites passed).
- [ ] `quantum-cpp-build` image exists (`docker images | grep quantum-cpp-build`).
- [ ] Bell, Grover, and Shor each run and print the expected output below.
- [ ] Terminal font is large enough for the back row; dark-on-light or your usual.
- [ ] Deck open to the **"A taste: the same circuit, two languages"** slide, which
      is where you cut to the terminal.

Keep the commands in a scratch file you can paste from. Do not type them live.

---

## The arc, mapped to the deck

| Demo step | Cut from this slide | Makes the point that |
|---|---|---|
| 1. Build | "The book: C++ first, Python alongside" | tests gate the image; the correctness check is mechanical |
| 2. Bell | "A taste: the same circuit, two languages" | entanglement is real and measurable |
| 3. Grover | "Relevancy: where it fits" (search) | the speed-up is real, not a slogan |
| 4. Shor | "The threat: Shor's algorithm is why" | the simulator algorithm is the cryptographic threat |
| 5. Close | "What it means: two tracks, start both now" | two timelines, managed in parallel |

---

## Step 1: Build both toolchains

Show this only if the room is technical and wants to see the discipline; otherwise
mention it was done in pre-flight and skip to Step 2.

```bash
docker compose build
```

**Expected (tail):** both stages finish without error. The C++ stage runs `ctest`
and the Python stage runs `pytest` inside the build.

**What to say:** "Each image is a multi-stage build whose test stage runs the full
suite. If the tests fail, the image fails. The book's rule is that a circuit which
runs without error but gives the wrong distribution is still broken, so correctness
is checked against theory, not assumed. That rule is baked into the build."

---

## Step 2: A Bell pair, in two languages

This is the heart of the demo. It mirrors the two code blocks on the "A taste"
slide.

```bash
docker compose run --rm cpp
```

```text
>> Bell state |psi> = (|00> + |11>)/sqrt(2)
...
  |00>: 499  (p=0.5)
  |11>: 499  (p=0.5)
```

```bash
docker compose run --rm python
```

```text
>> Bell state measured counts (Qiskit Aer):
  |00>: 474
  |11>: 526
```

**What to say:** "Same circuit, two languages. A Hadamard superposes the first
qubit, a controlled-NOT entangles the second. Run it a thousand times and you get
only `00` and `11`, never `01` or `10`. The qubits are perfectly correlated, and
that is entanglement. Notice the counts differ run to run and language to language:
a quantum program returns a distribution you sample, not a number you read. When an
independent C++ and Python run agree on the distribution, we trust the result."

**Watch for:** someone asking why the two counts are not identical. That is the
teachable moment, not a bug: it is sampling noise over 1000 shots.

---

## Step 3: Grover's search

```bash
docker run --rm quantum-cpp-build /work/examples/build/08-grover/cpp/grover
```

```text
>> Grover search for 101 among 8 items, 1000 shots
iterations: 2
most measured: 101  fraction = 0.953
```

Optional Python mirror (skip for time):

```bash
docker run --rm --entrypoint uv quantum-python \
  run --no-sync python examples/08-grover/python/grover.py
```

**What to say:** "We hid the item `101` in a space of eight and asked Grover to
find it. Two iterations put about 95 percent of the probability on the answer.
Classically, an unstructured search has no better plan than checking items one by
one. Grover is a real quadratic speed-up, and it generalizes to anything you can
phrase as marking the item you want. This is the 'search' row on the relevancy
slide."

---

## Step 4: Shor factors 15

This is the pivot from "neat" to "this concerns your cryptography." Run it, then
turn back to the deck.

```bash
docker run --rm quantum-cpp-build /work/examples/build/10-shor/cpp/shor
```

```text
>> Shor's algorithm: factor 15 with base a = 7
phase-estimation outcomes (value/16):
  0/16  count=474
  4/16  count=526
  8/16  count=498
  12/16  count=502
15 = 3 x 5
```

**What to say:** "Shor factors by finding a period, which phase estimation does on
a quantum computer. Here it factors 15. The four peaks at 0, 4, 8, and 12 reveal
the order, and a classical step turns that into 3 and 5. This is a toy size on a
simulator, but it is the real algorithm. RSA and elliptic-curve cryptography rest
on factoring and discrete logs being hard. Shor makes them tractable on a large
enough machine. No such machine exists yet, but data captured today can be
decrypted once one does. That is harvest-now, decrypt-later, and it is why the
clock has already started."

Then advance the deck to the post-quantum section and land the RHEL and two-tracks
slides.

---

## Step 5: The close (no command)

Stay on the **"two tracks, start both now"** slide.

**What to say:** "Two timelines. One is offense: learn quantum programming on
simulators now, for essentially no cost, and find where it could pay off. The other
is defense, and it is urgent: inventory your long-lived secrets and turn on the
post-quantum algorithms RHEL already ships. Post-quantum cryptography is classical
software that resists a quantum attacker. It never touches a qubit. One action to
leave with: start the cryptographic inventory this quarter. Everything you watched
runs on a laptop, from the companion repository."

---

## Troubleshooting

| Symptom | Cause | Fix |
|---|---|---|
| `docker compose build` is slow | Cold cache, compiling Quantum++ | Build in pre-flight, never live |
| `quantum-cpp-build` not found | Build-stage image not built | Re-run the `docker build --target build` line |
| `grover`/`shor` "no such file" | Runtime image used by mistake | These binaries live in `quantum-cpp-build`, not `quantum-cpp` |
| Counts differ from this file | Sampling noise over shots | Expected; say so, it reinforces the distribution point |
| No network on stage | Images already pulled | The demo runs fully offline once built |

## One-paragraph version (if the demo slot is cut)

"Everything in the book runs on a laptop in Docker, CPU only. A Bell pair in C++
and Python gives only `00` and `11`, which is entanglement you can measure. Grover
finds a marked item among eight in two steps, a real quadratic speed-up. Shor
factors 15 on the simulator using the same algorithm that threatens RSA, which is
why post-quantum cryptography exists and why RHEL already ships it. Two timelines:
learn the programming, and adopt the cryptography now."
