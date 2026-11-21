---
title: "Appendix B: Post-quantum cryptography is not quantum computing"
order: 17
part: "Appendices"
appendix: "B"
description: "Clearing up a common confusion: post-quantum cryptography secures today's classical systems against future quantum attacks, and is a different subject from programming a quantum computer."
---

"Post-quantum" and "quantum computing" sound like the same topic and are not. This
book is about programming a quantum computer. Post-quantum cryptography is about
defending ordinary, classical systems against one. The names collide; the subjects do
not. This appendix draws the line, because the two come up together often, especially
around Red Hat Enterprise Linux.

## Two different things

**Quantum computing** is what the rest of this book covers: writing circuits that run
on quantum hardware (or a simulator) to compute things a classical machine cannot do
efficiently. **Post-quantum cryptography (PQC)** is classical cryptography, running on
ordinary CPUs, designed to stay secure even against an attacker who has a large quantum
computer. PQC never touches a qubit. It is a response to quantum computing, not an
instance of it.

## Why post-quantum cryptography exists

[Chapter 10]({{ '/docs/10-shor/' | relative_url }}) is the reason. Shor's algorithm
factors large numbers and computes discrete logarithms efficiently on a quantum
computer, and the security of RSA and elliptic-curve cryptography, the backbone of
today's TLS, SSH, and code signing, rests on exactly those problems being hard. A
large, fault-tolerant quantum computer would break them. No such machine exists yet,
but the fix has to be in place before one does.

PQC replaces the vulnerable algorithms with ones based on mathematical problems that
no known quantum algorithm solves efficiently, mostly structured-lattice problems. In
2024 NIST standardized the first set: **ML-KEM** (key encapsulation, FIPS 203, formerly
Kyber) and **ML-DSA** (digital signatures, FIPS 204, formerly Dilithium). These are the
algorithms now appearing in TLS libraries and operating systems.

## The "harvest now, decrypt later" clock

The migration is urgent for a reason that does not wait for the hardware. An adversary
can record encrypted traffic today and store it until a quantum computer can decrypt it.
Any data whose secrecy must outlast the arrival of quantum computers, long-lived
records, state secrets, health data, is effectively at risk the moment it is sent, not
the moment the hardware exists. That is why standards bodies and vendors are moving now,
years ahead of a working code-breaking machine.

## Where RHEL fits

Red Hat Enterprise Linux 10 and the Universal Base Images built on it ship PQC support
through OpenSSL 3.5, which implements ML-KEM and ML-DSA. That lets applications negotiate
quantum-resistant key exchange and signatures without application changes in many cases.
This is a classical-software capability: it hardens the systems you already run. It has
nothing to do with the quantum programming in this book, beyond sharing the word
"quantum" and being motivated by the same Shor's algorithm.

## The one-sentence version

If you are protecting data, you want post-quantum cryptography, which runs on the
classical machines you already have. If you are computing with qubits, that is quantum
programming, which is the rest of this book. Shor's algorithm is the thread that connects
them: it is why the first subject needs to exist, and an example of what the second can do.

## For deeper coverage

- [NIST post-quantum cryptography](https://csrc.nist.gov/projects/post-quantum-cryptography)
  — the standardization project and the FIPS 203/204 standards.
- [Red Hat on post-quantum cryptography](https://www.redhat.com/en/blog/post-quantum-cryptography-red-hat-enterprise-linux-10)
  — how PQC is being adopted in RHEL.
