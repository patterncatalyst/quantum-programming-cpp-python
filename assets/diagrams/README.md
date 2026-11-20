# Diagram catalogue

Paired figures: `<name>.svg` is embedded in the site, `<name>.excalidraw` is the
editable source. Regenerate both with `python3 -I scripts/make_diagrams.py` from
the repo root.

| Name | Figure | Used in |
|---|---|---|
| `bell-circuit` | H then CNOT: the Bell pair | Chapter 3, Chapter 6 |
| `coin-flip-circuit` | The quantum coin flip (H then measure) | Chapter 4 |
| `weighted-coin-circuit` | The weighted coin (RY then measure) | Chapter 5 |
| `teleportation-circuit` | Quantum teleportation | Chapter 6 |
| `deutsch-jozsa-circuit` | Deutsch-Jozsa: the Hadamard sandwich | Chapter 7 |
| `grover-circuit` | Grover's search: oracle plus diffusion | Chapter 8 |
| `phase-estimation-circuit` | Phase estimation: controlled powers + inverse QFT | Chapter 9 |
| `shor-circuit` | Shor's algorithm: order-finding + gcd | Chapter 10 |
