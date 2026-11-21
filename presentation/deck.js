// deck.js — companion deck for "Quantum Programming in C++ and Python".
// Build:  npm install && node deck.js   (pptxgenjs is a local dependency)
"use strict";

const H = require("./deck-helpers.js");
const {
  COLOR, FONT, W, ASSETS,
  newDeck, addFooter, addContentTitle, addBullets, addTwoColBullets,
  addStatusTable, addCaption, addCodeSlide, addSectionDivider, addNotes,
} = H;

const OUT = "quantum-programming-cpp-python-deck-r09.0.pptx";
const REV = "r09.0";

const pres = newDeck();
// Public-repo metadata: name the project, not the machine or its owner.
pres.title = "Quantum Programming in C++ and Python";
pres.subject = "Companion deck";
pres.author = "Pattern Catalyst";
pres.company = "Red Hat";
pres.revision = REV;
let pageNum = 0;

function S() {
  const s = pres.addSlide(); pageNum += 1; addFooter(s, pageNum); return s;
}
function divider(code, title, subtitle, notes) {
  const s = pres.addSlide(); pageNum += 1; addSectionDivider(s, code, title, subtitle); addNotes(s, notes);
}

// ---- Cover -------------------------------------------------------------------
{
  const s = pres.addSlide();
  pageNum += 1;
  s.background = { color: COLOR.white };
  try { s.addImage({ path: `${ASSETS}/cover-panel.png`, x: 0, y: 0, w: W, h: 7.5 }); } catch (e) {}
  s.addText("QUANTUM PROGRAMMING", { x: 6.00, y: 1.98, w: 6.90, h: 0.34,
    fontFace: FONT.title, fontSize: 14, bold: true, color: COLOR.red, charSpacing: 6, align: "left", valign: "middle" });
  s.addText([{ text: "Quantum Programming", options: { breakLine: true } }, { text: "in C++ and Python" }], {
    x: 5.95, y: 2.42, w: 6.95, h: 2.00, fontFace: FONT.title, fontSize: 46, bold: true, color: COLOR.ink, align: "left", valign: "top" });
  s.addText("A hands-on, CPU-only tour, and why it matters to your business and your cryptography.", {
    x: 6.00, y: 4.70, w: 6.70, h: 0.95, fontFace: FONT.body, fontSize: 17, italic: true, color: COLOR.caption, align: "left", valign: "top" });
  s.addText(REV, { x: 11.85, y: 5.85, w: 0.95, h: 0.30, fontFace: FONT.mono, fontSize: 11, color: COLOR.caption, align: "right", valign: "middle" });
  try { s.addImage({ path: `${ASSETS}/logo-candidate-2.png`, x: 11.10, y: 6.80, w: 1.55, h: 0.37 }); } catch (e) {}
  addNotes(s, "This is the companion deck to the book 'Quantum Programming in C++ and Python'. The book teaches quantum programming with a primary C++ track (Quantum++) and a Python cross-check (Qiskit), CPU-only and container-first. This talk does three things: introduce what quantum programming actually is, show where it realistically meets business processes, and draw the line to post-quantum cryptography in RHEL, which is a different subject that the same mathematics motivates. Keep the framing honest throughout: no hype, just what runs today and what it means.");
}

// ---- Agenda ------------------------------------------------------------------
{
  const s = S();
  addContentTitle(s, "COMPANION DECK · AGENDA", "What we'll cover");
  addBullets(s, [
    "Introduction: what quantum programming actually is, and what the book teaches you to run.",
    "Relevancy: where quantum computing realistically meets your business processes, and where it does not yet.",
    "The post-quantum intersection: why RHEL already ships the defense, and what to do about it now.",
  ], { fontSize: 18 });
  addNotes(s, "Three sections. The first grounds the audience in the mechanics so the rest lands. The second is the honest business case: what is real today versus research. The third is the part most audiences conflate with quantum computing and should not: post-quantum cryptography. Tell them up front that the third section is the one with an action item they can take this quarter.");
}

// ---- Section 1 ---------------------------------------------------------------
divider("01", "Introduction", "What quantum programming is, and what the book teaches.",
  "Set up the fundamentals quickly. The audience does not need the physics; they need enough of the model to follow the business and cryptography arguments later.");

{
  const s = S();
  addContentTitle(s, "INTRODUCTION · FUNDAMENTALS", "Qubits, superposition, measurement");
  addBullets(s, [
    "A qubit holds a superposition of 0 and 1; measuring it collapses it to one outcome, with a probability set by the state.",
    "Gates are reversible operations on qubits, and a circuit is just an ordered sequence of them.",
    "On real hardware you never read the state; you run the circuit many times and count the outcomes.",
    "The book reports every result as measured counts over a stated number of shots, checked against the analytic expectation.",
  ], { fontSize: 17 });
  addNotes(s, "The one mental model to leave with: a quantum program is a circuit you run, not a state you read. Superposition and entanglement are the resources; measurement is how you get classical answers out, as a distribution you estimate by sampling. The book's discipline, counts over shots checked against theory, is exactly how you keep yourself honest, because a circuit that runs without error but produces the wrong distribution is still broken.");
}

{
  const s = S();
  addContentTitle(s, "INTRODUCTION · THE BOOK", "C++ first, Python alongside, CPU only");
  addBullets(s, [
    "Primary track: C++23 with Quantum++, a header-only library, built with CMake and Conan.",
    "Secondary track: Python with Qiskit and Aer, used as a cross-check and a test harness.",
    "Everything runs in Docker containers on a plain Fedora workstation: no GPU, and no cloud account.",
    "Five parts and sixteen chapters, plus two appendices, with every example runnable and tested.",
  ], { fontSize: 17 });
  addNotes(s, "Why C++ first: most books teach quantum computing in Python only. The teams with the most to gain often run C++, so the book leads in C++ with Quantum++ and uses Python as the cross-check. Running the same algorithm two ways is also a correctness check: when an independent C++ and Python implementation agree on the distribution, you trust the result. CPU-only and container-first means anyone can run all of it on a laptop, which matters for adoption.");
}

{
  const s = S();
  addCodeSlide(s, "INTRODUCTION · A TASTE", "The same circuit, two languages", "C++ (Quantum++) · Python (Qiskit)",
    [
      "// C++ with Quantum++",
      "QCircuit qc{2, 2};",
      "qc.gate(gt.H, 0);          // superpose qubit 0",
      "qc.CTRL(gt.X, 0, 1);       // entangle qubit 1 with it",
      "qc.measure(0, 0); qc.measure(1, 1);",
      "",
      "# Python with Qiskit",
      "qc = QuantumCircuit(2, 2)",
      "qc.h(0); qc.cx(0, 1)",
      "qc.measure([0, 1], [0, 1])",
      "# both runs measure only 00 and 11 — never 01 or 10",
    ],
    "A Bell pair: the two qubits are perfectly correlated in both languages.");
  addNotes(s, "This is the 'hello world' of entanglement and it is the whole book in miniature: a short circuit, run in both languages, giving the same measured distribution. A Hadamard puts the first qubit in superposition; the controlled-NOT entangles the second; measuring many times yields only 00 and 11, the signature of entanglement. Point out that the two code blocks are the same circuit, so the choice of language is about fit, not correctness.");
}

{
  const s = S();
  addContentTitle(s, "INTRODUCTION · THE ARC", "The algorithms you build");
  addStatusTable(s, [
    { code: "Ch7", name: "Deutsch-Jozsa / BV", purpose: "Decide a global property, or recover a hidden string, in a single query." },
    { code: "Ch8", name: "Grover", purpose: "Search an unstructured space in about the square root of its size." },
    { code: "Ch9", name: "QFT / phase est.", purpose: "Read the phase of a gate's eigenvalue into a counting register." },
    { code: "Ch10", name: "Shor", purpose: "Factor by order-finding; the reason post-quantum cryptography exists." },
    { code: "Ch11-12", name: "VQE / QAOA", purpose: "Hybrid, near-term methods for chemistry and for optimization." },
  ], { colW: [1.45, 3.15, 7.49] });
  addNotes(s, "This is the payload of the book, and every one of these is built and verified on a CPU simulator. Deutsch-Jozsa and Bernstein-Vazirani are the clean first wins. Grover is the general quadratic speed-up. The Quantum Fourier Transform and phase estimation are the engine inside Shor. Shor is the headline, and the bridge to the cryptography section. VQE and QAOA are the hybrid methods most likely to matter on near-term hardware. You do not need to teach each here; you are showing the scope and setting up Shor and the variational methods for the next sections.");
}

// ---- Section 2 ---------------------------------------------------------------
divider("02", "Relevancy to your business", "Where quantum computing realistically meets your processes.",
  "Shift from mechanics to value. The goal of this section is an honest map: what is real today, what is near term, and what is still research, so the audience can plan rather than react to headlines.");

{
  const s = S();
  addContentTitle(s, "RELEVANCY · WHERE IT FITS", "Three honest categories");
  addBullets(s, [
    "Optimization with QAOA: scheduling, routing, and portfolio selection, framed as maximizing a count.",
    "Simulation of quantum systems with VQE: chemistry and materials, where the problem is itself quantum.",
    "Search and number theory with Grover and Shor: quadratic speed-ups, and the cryptographic stakes of factoring.",
    "Most other claims are, for now, research; knowing which category a use case is in is the point.",
  ], { fontSize: 17 });
  addNotes(s, "Resist the urge to promise everything. Three categories cover the credible near-term value: optimization, quantum simulation, and the search and number-theory results. Each maps to a chapter the audience can run. The honest fourth category is 'research', and being able to place a proposed use case into the right bucket is exactly the literacy this book gives a team. That literacy is worth more than any single algorithm.");
}

{
  const s = S();
  addContentTitle(s, "RELEVANCY · THE TIMELINE", "What is real today, and what is not");
  addBullets(s, [
    "Today: simulators reach about 25 to 30 qubits on a workstation, enough to learn and prototype every algorithm in the book.",
    "Near term: noisy hardware runs shallow circuits, and results carry visible error you have to reason about.",
    "Later: fault-tolerant machines large enough to threaten today's cryptography do not exist yet.",
    "What to do now: build the skills and identify the use cases, so you are ready rather than surprised.",
  ], { fontSize: 17 });
  addNotes(s, "The memory wall is the honest limit of simulation: the state vector doubles with every qubit, so a workstation tops out near thirty. That is still enough to learn everything. On real hardware, noise dominates once circuits get deep, which is why the near-term methods are shallow. The fault-tolerant machine that breaks RSA is not here, and that is the thread into the cryptography section: you have time, but not unlimited time, and the preparation starts now.");
}

{
  const s = S();
  addContentTitle(s, "RELEVANCY · WHY C++", "Why a C++-first path matters");
  addBullets(s, [
    "Quantum++ is header-only and links against Eigen, so it drops into an existing C++ codebase with no runtime.",
    "The sectors with the most to gain already run C++: aerospace, financial services, and capital markets.",
    "A C++-first path lets those teams prototype quantum ideas in the language their systems are written in.",
    "Python stays in the loop for ecosystem and hardware access; the two tracks are complementary, not rivals.",
  ], { fontSize: 17 });
  addNotes(s, "This is the differentiator of the book and the reason it leads in C++. Latency-sensitive, C++-heavy industries are exactly the ones where optimization and simulation could pay off, and a header-only library that links into their existing code lowers the barrier to experimenting. Make the point generically: the value is that a team can prototype in its own language. Python is not the enemy; it is the ecosystem and the path to hardware. Keep this about capability fit, and do not single out named organizations.");
}

// ---- Section 3 ---------------------------------------------------------------
divider("03", "The post-quantum intersection", "Why RHEL already ships the defense, and what it means.",
  "This is the section with the concrete action item. The most common confusion in the room will be that post-quantum cryptography is a kind of quantum computing. Clear that up first, then make the business case.");

{
  const s = S();
  addContentTitle(s, "POST-QUANTUM · THE DISTINCTION", "Post-quantum is not quantum computing");
  addBullets(s, [
    "Quantum computing is programming qubits to compute, which is the subject of the book.",
    "Post-quantum cryptography is classical cryptography, on ordinary CPUs, built to survive a quantum attacker.",
    "It never touches a qubit; it is a response to quantum computing, not an instance of it.",
    "The names collide, the subjects do not, and conflating them leads to the wrong roadmap.",
  ], { fontSize: 17 });
  addNotes(s, "Lead with the distinction because almost everyone gets it wrong. Post-quantum cryptography runs on the classical machines you already own; it is new math for key exchange and signatures, not a quantum program. The reason it shares the word 'quantum' is that a quantum computer is the thing it defends against. If a team thinks they need a quantum computer to be secure, they will do nothing and stay exposed; the truth is the opposite, the fix is classical and available now.");
}

{
  const s = S();
  addContentTitle(s, "POST-QUANTUM · THE THREAT", "Shor's algorithm is why");
  addBullets(s, [
    "RSA and elliptic-curve security rest on factoring and discrete logarithms being hard.",
    "Shor's algorithm, which the book builds, solves both efficiently on a large enough quantum computer.",
    "No such machine exists yet, but the data you protect today has to outlast the one that eventually will.",
    "Post-quantum cryptography replaces the vulnerable math with lattice-based schemes no known quantum algorithm breaks.",
  ], { fontSize: 17 });
  addNotes(s, "This is why the book spends a chapter on Shor beyond its fame: it is the direct link to the cryptography the audience depends on. Shor turns factoring from exponentially hard into tractable on a quantum computer, and RSA and ECC are built on factoring and discrete logs being hard. The mitigation is already standardized and is lattice-based, a different hard problem with no known quantum shortcut. The point is continuity: the same algorithm you can run on a simulator today is the one driving a global cryptographic migration.");
}

{
  const s = S();
  addContentTitle(s, "POST-QUANTUM · THE CLOCK", "Harvest now, decrypt later");
  addBullets(s, [
    "An adversary can record encrypted traffic today and store it until a quantum computer can read it.",
    "Any secret that must stay secret for years is effectively at risk the moment it is sent.",
    "That is why standards bodies and vendors are migrating now, ahead of the hardware.",
    "The clock started without the machine; waiting for the machine is waiting too long.",
  ], { fontSize: 17 });
  addNotes(s, "This is the argument that makes the timeline urgent despite the hardware not existing. Encrypted data captured today can be decrypted later, so the exposure is set by the lifetime of your secrets, not by the arrival date of a quantum computer. For long-lived data, regulated records, health data, state secrets, intellectual property, the risk is effectively present tense. This is the slide that turns 'interesting someday' into 'act this year'.");
}

{
  const s = S();
  addContentTitle(s, "POST-QUANTUM · RHEL TODAY", "RHEL already ships the defense");
  addBullets(s, [
    "NIST standardized the first post-quantum algorithms in 2024: ML-KEM (FIPS 203) and ML-DSA (FIPS 204).",
    "RHEL 10 and the Universal Base Images ship them through OpenSSL 3.5.",
    "Applications can negotiate quantum-resistant key exchange and signatures, often without code changes.",
    "This is a classical-software capability you can adopt now, on the systems you already run.",
  ], { fontSize: 17 });
  addNotes(s, "Here is the concrete, available-today part. The algorithms are standardized, not experimental, and they are in the platform: RHEL 10 and UBI carry them via OpenSSL 3.5. Because much of the protection is at the TLS and signing layer, many applications gain it without code changes. The message to leadership: this is not a quantum project, it is a platform upgrade and a migration plan, and the building blocks are already in the operating system.");
}

{
  const s = S();
  addContentTitle(s, "POST-QUANTUM · WHAT IT MEANS", "Two tracks, start both now");
  addTwoColBullets(s,
    [
      { text: "Learn quantum programming", options: { bullet: false, bold: true, color: COLOR.red } },
      "Prototype on CPU simulators today, no hardware needed.",
      "Find where optimization or simulation could pay off.",
      "Build in-house skills before the hardware matters.",
    ],
    [
      { text: "Adopt post-quantum crypto", options: { bullet: false, bold: true, color: COLOR.red } },
      "Inventory long-lived secrets and where they travel.",
      "Enable post-quantum crypto in RHEL 10 and UBI.",
      "Plan the migration now, not after a breakthrough.",
    ],
    { fontSize: 16 });
  addNotes(s, "The takeaway slide: these are two separate timelines a technology leader manages in parallel. The quantum-programming track is about skills and opportunity, low cost and no hardware, starting on simulators. The post-quantum-crypto track is about risk and is urgent now because of harvest-now-decrypt-later. One is offense, the other defense; neither waits on a working code-breaking machine. If the audience leaves with one action, it is: start the cryptographic inventory and enable post-quantum crypto where the platform already supports it.");
}

// ---- References & closing ----------------------------------------------------
{
  const s = S();
  addContentTitle(s, "REFERENCES", "Sources and further reading");
  addBullets(s, [
    "Nielsen & Chuang, Quantum Computation and Quantum Information (Cambridge University Press, 2010).",
    "Gheorghiu, Quantum++: A modern C++ quantum computing library (PLOS ONE, 2018).",
    "Johnston, Harrigan & Gimeno-Segovia, Programming Quantum Computers (O'Reilly, 2019).",
    "NIST FIPS 203 (ML-KEM) and FIPS 204 (ML-DSA); Red Hat, post-quantum cryptography in RHEL 10.",
  ], { fontSize: 16 });
  addCaption(s, "Full bibliography on the companion site. Ideas are credited; nothing is copied.");
  addNotes(s, "Credit the works the book and this talk lean on. Nielsen and Chuang is the standard text. The Quantum++ paper is the C++ library the primary track uses. Programming Quantum Computers is the code-first tour. The NIST FIPS standards and Red Hat's guidance back the post-quantum section. The full bibliography lives on the companion site; the rule is that ideas are paraphrased and attributed, never copied.");
}

{
  const s = S();
  addContentTitle(s, "CLOSING", "Where to go next");
  addBullets(s, [
    "Read and run the book: every chapter ships C++ and Python examples with tests.",
    "Start on a simulator today: no GPU, no cloud account, and no special hardware.",
    "Manage quantum programming and post-quantum cryptography as two timelines, in parallel.",
  ], { fontSize: 17 });
  addCaption(s, "patterncatalyst.github.io/quantum-programming-cpp-python");
  addNotes(s, "Close on the two-timelines message and point them at the book. The barrier to starting is essentially zero: it all runs on a laptop in containers. The defensive track has a real deadline driven by the lifetime of their data. Leave the site URL on the screen. If there is time, offer to walk through the Bell example or the Shor chapter live from the companion repo.");
}

pres.writeFile({ fileName: OUT })
  .then(p => console.log("WROTE", p, "slides:", pageNum))
  .catch(e => { console.error(e); process.exit(1); });
