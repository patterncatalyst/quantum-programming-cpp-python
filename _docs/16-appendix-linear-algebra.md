---
title: "Appendix A: The linear algebra you need"
order: 16
part: "Appendices"
appendix: "A"
description: "A compact reference for the linear algebra this book uses: complex numbers, state vectors, inner products, unitary matrices, tensor products, and eigenvalues."
---

This appendix collects the linear algebra the chapters lean on, in one place and at
the depth the book actually needs. It is a reference, not a course: each idea is
stated, shown on a small example, and tied to where the book uses it.

## Complex numbers

A complex number is $z = a + bi$ with $i^2 = -1$. Its **conjugate** is $z^* = a - bi$,
and its **magnitude** is $|z| = \sqrt{a^2 + b^2}$, so $|z|^2 = z^* z = a^2 + b^2$. The
book uses $|z|^2$ constantly: it is how an amplitude becomes a probability.

## State vectors (kets)

The state of a qubit is a length-2 column vector of complex numbers, written
$|\psi\rangle$ (a *ket*). The two basis states are

$$|0\rangle = \begin{pmatrix} 1 \\ 0 \end{pmatrix}, \qquad
  |1\rangle = \begin{pmatrix} 0 \\ 1 \end{pmatrix}.$$

A general qubit is $|\psi\rangle = \alpha|0\rangle + \beta|1\rangle$ with
$|\alpha|^2 + |\beta|^2 = 1$. That normalization is what makes the measurement
probabilities, $|\alpha|^2$ and $|\beta|^2$, sum to one. For $n$ qubits the vector has
$2^n$ entries, which is the exponential cost Chapter 13 runs into.

## Inner products and the bra

The **bra** $\langle\psi|$ is the conjugate transpose of the ket $|\psi\rangle$. The
inner product $\langle\phi|\psi\rangle$ is a single complex number that measures overlap:
it is 1 for identical states and 0 for distinguishable ones. Basis states are
*orthonormal*: $\langle 0|0\rangle = \langle 1|1\rangle = 1$ and
$\langle 0|1\rangle = 0$. Chapter 11 writes an energy as $\langle\psi|H|\psi\rangle$, an
inner product of $|\psi\rangle$ with $H|\psi\rangle$.

## Matrices and gates

A quantum gate on one qubit is a $2\times2$ matrix acting on the state vector. The
gates the book uses most:

$$X = \begin{pmatrix} 0 & 1 \\ 1 & 0 \end{pmatrix}, \quad
  Z = \begin{pmatrix} 1 & 0 \\ 0 & -1 \end{pmatrix}, \quad
  H = \tfrac{1}{\sqrt 2}\begin{pmatrix} 1 & 1 \\ 1 & -1 \end{pmatrix}.$$

Applying a gate is matrix-times-vector: $X|0\rangle = |1\rangle$. Chapter 2 does exactly
this multiplication by hand before the frameworks take over.

## Unitary matrices

Every quantum gate is **unitary**: $U^\dagger U = I$, where $U^\dagger$ is the conjugate
transpose. Unitary matrices preserve the length of a vector, which is why a gate keeps
total probability at one and why quantum operations are reversible. Checking
$U^\dagger U = I$ is the quickest test that a matrix is a legal gate.

## Tensor products

Two qubits combine with the **tensor product** $\otimes$. The four basis states of a
two-qubit system are $|00\rangle, |01\rangle, |10\rangle, |11\rangle$, and a two-qubit
gate is a $4\times4$ matrix. For example,

$$|0\rangle \otimes |0\rangle = |00\rangle = \begin{pmatrix} 1 \\ 0 \\ 0 \\ 0 \end{pmatrix}.$$

The tensor product is why $n$ qubits need $2^n$ amplitudes, and entanglement (Chapter 6)
is exactly a two-qubit state that cannot be written as one such product.

## Eigenvalues and eigenvectors

For a matrix $A$, a nonzero vector $|v\rangle$ with $A|v\rangle = \lambda|v\rangle$ is an
**eigenvector** and $\lambda$ its **eigenvalue**. Two chapters turn on this: phase
estimation (Chapter 9) reads the eigenvalue's phase of a gate, and VQE (Chapter 11)
finds the smallest eigenvalue of a Hamiltonian. For a Hamiltonian (a Hermitian matrix,
$H^\dagger = H$) the eigenvalues are real, which is why they stand in for energies.

## Where to go deeper

The [bibliography]({{ '/bibliography/' | relative_url }}) lists full treatments. Nielsen
and Chuang's text, in particular, has a self-contained linear-algebra chapter pitched at
exactly this material.
