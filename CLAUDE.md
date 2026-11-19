# CLAUDE.md — Quantum Programming in C++ and Python

## What this is
A chapter-based Jekyll tutorial and Leanpub book teaching quantum programming
with a **primary C++ track** and a **secondary Python track** used for contrast
and testing. CPU-only simulation, in the lgtm house style. Chapters in `_docs/`,
examples in `examples/`, containers in `containers/`, plans in `_plans/`.

Tracked as Plane FIELDCTONA-615. Notion PRD and the local planning files
(`proposal-prd.md`, `curriculum.md`, `dev-environment.md`) hold the full history.

## Hardware reality — do not drift
- CPU-only simulation. No GPU acceleration anywhere.
- Quantum GPU support is effectively NVIDIA/CUDA-only; the target machine has an
  Intel GPU, so it is not used. Say so plainly; never hint a GPU would help.
- CUDA-Q uses its CPU target (`qpp-cpu`); despite the name it needs no GPU.
- Qubit ceiling is about 25 to 30 on a workstation. Never write an example that
  exceeds what the box can run.

## Languages and frameworks
- **C++ is primary.** C++20/23, Clang, CMake. There is no C++21; never write it.
  - Primary C++ framework: **Quantum++ (qpp)**, header-only, MIT.
  - Second C++ option: **CUDA-Q** `qpp-cpu` CPU target, via its published image.
- **Python is secondary** (teaching contrast and the test harness). **Python 3.14**,
  managed by **uv**. Frameworks: Qiskit + Qiskit Aer (CPU), Cirq, PennyLane.
- Every algorithm chapter leads with C++; Python cross-checks the same measured
  distribution. Do not frame the two as co-equal and do not run a language shootout.

## Python version — pinned 3.14, not the host's 3.15
Fedora 45 ships Python 3.15 as the system interpreter; the host `python3` is never
touched. The book pins 3.14 because PennyLane-lightning has no 3.15 wheels
(upstream issue #1442) and CUDA-Q tops out at 3.14. Qiskit/Aer do publish 3.15.
Revisit 3.15 once both PennyLane-lightning and CUDA-Q ship 3.15 wheels.
- uv provides 3.14: `uv python install 3.14`, `uv venv --python 3.14`, `uv sync --locked`.
- The same uv steps run in the container build stage, so the image gets 3.14
  regardless of the base image's own Python.

## Everything runs in containers — Docker, multi-stage
- **Docker Engine + Docker Compose** (the lgtm stack approach). Not Podman.
- **Always multi-stage builds:** a build stage compiles, a test stage runs the
  checks, the runtime stage carries only what it needs. Tests run inside the build.
- **Base image: Fedora base** (fedora:44), fully qualified
  (`registry.fedoraproject.org/fedora:44`). Chosen for easy modern Clang 23 /
  CMake for C++23; uv supplies Python 3.14 on top.
- Examples mounted as a volume for edit-without-rebuild during authoring.
- No host-level pip installs in any chapter.

## Ground rules
- Fedora base, CPU only, no accounts (except the optional final real-QPU chapter
  on the free IBM Quantum tier).
- Code is `unverified` until actually run in the container here.
- Build/run success is a checkpoint, never the finish line. A circuit that runs
  without error but produces the wrong distribution is still broken. Verify the
  measured counts against the analytic expectation, not the exit code.
- Measured results are reported as counts over a stated number of shots.
- Circuits are shown as both a diagram and code, never code alone.

## Math rendering
One LaTeX source, both targets: MathJax 3 on the site (`_includes/mathjax.html`,
`braket` + `physics` extensions), native in the Markua build. Algebra annotates
code, never gates it: NumPy state vectors and concrete small gate matrices first,
derivations in skippable Markua asides. One "linear algebra you need" appendix.

## Skills to use
| Task                              | Skill                   |
|-----------------------------------|-------------------------|
| Scaffold or change the site       | lgtm-jekyll             |
| Write or revise a chapter         | lgtm-tutorial           |
| C++ toolchain / tests             | lgtm-cpp                |
| Container stack / compose         | lgtm-docker-stack       |
| Make a figure                     | lgtm-diagram-generator  |
| Build the conference deck         | lgtm-presentation       |
| Commits, releases, repo setup     | lgtm-github             |
| Plan then build then validate     | lgtm-relay              |

## Repo layout
    _config.yml / _parts/*.md / _docs/NN-*.md
    containers/cpp/Containerfile          multi-stage, Fedora base
    containers/python/Containerfile       multi-stage, uv provides 3.14
    compose.yaml                          the cpp + py pair
    examples/NN-name/{cpp,python}/ + README.md (behavioral verification)
    assets/diagrams/                      paired name.svg + name.excalidraw
    scripts/                              generate_diagram.py, check-prereqs.sh
    manuscript/                           Markua, generated, never hand-edited
    _plans/                               iteration-plan.md, spike-results.md

## Do the spike before chapter prose
Build both containers, confirm qiskit / qiskit-aer / cirq / pennylane on 3.14,
build a qpp Bell state (C++) and a matching Qiskit run (Python), benchmark the
qubit ceiling (time and RSS by qubit count). Record in `_plans/spike-results.md`.
3.14 framework availability is already confirmed on Linux x86_64; the open spike
item is the qpp and CUDA-Q builds in-container.

## Publishing rule — nothing identifies the machine or its owner
The repo is public. No tracked file may name the development machine, its owner,
an absolute home path, a hostname, a CPU model or a MAC/IP. Write `<repo>/...` or
`~/...`. Run lgtm-host-scrub before the first push and before committing any
captured log.

## Commits and releases
Conventional Commits, `type(scope): summary`, imperative, <= 72 chars. Scopes
`§N`, `demo-NN`, `rNN.x`. One `release/rNN` branch and PR per iteration, branched
from an updated main, squash-merged, branch deleted; tag `rNN.x` on main after
merge. Public repo; site deploys to GitHub Pages from main.

## Do not
- Do not suggest GPU acceleration; it does not apply here.
- Do not write an example that exceeds the measured qubit ceiling.
- Do not use Jupyter notebooks as the primary format; scripts and containers are
  the house format.
- Do not claim a simulated result models real hardware noise.
- Do not install against the host system Python (it is 3.15); use uv 3.14.
- Do not frame C++ and Python as co-equal; C++ leads, Python cross-checks.

## Post-quantum note
"Post-quantum" in RHEL 10 / UBI refers to post-quantum CRYPTOGRAPHY (ML-KEM,
ML-DSA), which secures today's systems against future quantum attacks. It is
unrelated to quantum computing and simulation. Planned teaching sidebar clears up
this common confusion.
