#!/usr/bin/env python3
"""Generate the circuit diagrams for Part 2 (First Programs).

Each quantum circuit is drawn as a left-to-right flow of gate boxes connected by
arrows, in the site's house style. Run from the repo root:

    python3 -I scripts/make_diagrams.py
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import generate_diagram as g  # noqa: E402

g.OUT = "assets/diagrams"

WIRE_Y = 70
BOX_Y = 44
BOX_H = 52


def box(x, w, lines, style="box"):
    return {"x": x, "y": BOX_Y, "w": w, "h": BOX_H, "style": style, "lines": lines}


def wire(x1, x2):
    # A plain left-to-right connector between two gate boxes.
    return {"x1": x1, "y1": WIRE_Y, "x2": x2, "y2": WIRE_Y}


# --- Coin flip: |0> -> H -> measure -> bit ---------------------------------
g.emit(
    "coin-flip-circuit", 640, 150,
    nodes=[
        box(40, 70, ["|0>"], "sub"),
        box(190, 60, ["H"], "accent"),
        box(330, 110, ["measure"], "ink"),
        box(510, 90, ["bit 0/1"], "sub"),
    ],
    edges=[wire(110, 190), wire(250, 330), wire(440, 510)],
    notes=[{"x": 320, "y": 130, "text": "one qubit, measured to one classical bit",
            "anchor": "middle", "size": 12, "color": "#1d1d1d"}],
)

# --- Weighted coin: |0> -> RY(theta) -> measure -> bit ---------------------
g.emit(
    "weighted-coin-circuit", 660, 150,
    nodes=[
        box(40, 70, ["|0>"], "sub"),
        box(190, 90, ["RY(theta)"], "accent"),
        box(360, 110, ["measure"], "ink"),
        box(540, 90, ["bit 0/1"], "sub"),
    ],
    edges=[wire(110, 190), wire(280, 360), wire(470, 540)],
    notes=[{"x": 330, "y": 130, "text": "RY tilts the odds: P(1) = sin^2(theta/2)",
            "anchor": "middle", "size": 12, "color": "#1d1d1d"}],
)

# --- Bell pair: H on q0, CNOT to q1, measure both --------------------------
g.emit(
    "bell-circuit", 680, 230,
    nodes=[
        {"x": 40, "y": 44, "w": 70, "h": 52, "style": "sub", "lines": ["|0>"]},
        {"x": 40, "y": 134, "w": 70, "h": 52, "style": "sub", "lines": ["|0>"]},
        {"x": 190, "y": 44, "w": 60, "h": 52, "style": "accent", "lines": ["H"]},
        {"x": 330, "y": 44, "w": 120, "h": 142, "style": "box",
         "lines": ["CNOT", "control q0", "target q1"]},
        {"x": 510, "y": 44, "w": 110, "h": 52, "style": "ink", "lines": ["measure"]},
        {"x": 510, "y": 134, "w": 110, "h": 52, "style": "ink", "lines": ["measure"]},
    ],
    edges=[
        {"x1": 110, "y1": 70, "x2": 190, "y2": 70},
        {"x1": 250, "y1": 70, "x2": 330, "y2": 70},
        {"x1": 110, "y1": 160, "x2": 330, "y2": 160},
        {"x1": 450, "y1": 70, "x2": 510, "y2": 70},
        {"x1": 450, "y1": 160, "x2": 510, "y2": 160},
    ],
    notes=[{"x": 340, "y": 215, "text": "outcomes only 00 or 11, never 01 or 10",
            "anchor": "middle", "size": 12, "color": "#1d1d1d"}],
)

# --- Teleportation: Bell measure on q0,q1; corrections on q2 ---------------
g.emit(
    "teleportation-circuit", 820, 320,
    nodes=[
        {"x": 30, "y": 40, "w": 110, "h": 50, "style": "accent",
         "lines": ["RY(theta)"]},
        {"x": 30, "y": 130, "w": 110, "h": 50, "style": "sub", "lines": ["q1 = |0>"]},
        {"x": 30, "y": 220, "w": 110, "h": 50, "style": "sub", "lines": ["q2 = |0>"]},
        {"x": 180, "y": 130, "w": 150, "h": 140, "style": "box",
         "lines": ["Bell pair", "H q1", "CNOT q1->q2"]},
        {"x": 370, "y": 40, "w": 160, "h": 140, "style": "box",
         "lines": ["Bell measure", "CNOT q0->q1", "H q0, measure"]},
        {"x": 580, "y": 220, "w": 190, "h": 50, "style": "ink",
         "lines": ["X / Z corrections"]},
    ],
    edges=[
        {"x1": 140, "y1": 65, "x2": 370, "y2": 65},
        {"x1": 140, "y1": 155, "x2": 180, "y2": 155},
        {"x1": 140, "y1": 245, "x2": 180, "y2": 245},
        {"x1": 330, "y1": 170, "x2": 370, "y2": 150},
        {"x1": 330, "y1": 245, "x2": 580, "y2": 245},
        {"x1": 450, "y1": 180, "x2": 540, "y2": 220, "label": "2 classical bits",
         "amber": True, "dashed": True, "ly": -4},
    ],
    notes=[{"x": 410, "y": 300,
            "text": "two classical bits steer the corrections; q2 ends in the sent state",
            "anchor": "middle", "size": 12, "color": "#1d1d1d"}],
)

# --- Deutsch-Jozsa: Hadamard sandwich around an oracle ---------------------
g.emit(
    "deutsch-jozsa-circuit", 820, 240,
    nodes=[
        {"x": 30, "y": 44, "w": 90, "h": 52, "style": "sub", "lines": ["|0...0>"]},
        {"x": 30, "y": 150, "w": 90, "h": 52, "style": "sub", "lines": ["|0>"]},
        {"x": 170, "y": 44, "w": 80, "h": 52, "style": "accent", "lines": ["H (all)"]},
        {"x": 170, "y": 150, "w": 80, "h": 52, "style": "sub", "lines": ["X, H", "(|->)"]},
        {"x": 300, "y": 44, "w": 150, "h": 158, "style": "box",
         "lines": ["oracle U_f", "|x>|y> ->", "|x>|y xor f(x)>"]},
        {"x": 500, "y": 44, "w": 80, "h": 52, "style": "accent", "lines": ["H (all)"]},
        {"x": 630, "y": 44, "w": 110, "h": 52, "style": "ink", "lines": ["measure"]},
    ],
    edges=[
        {"x1": 120, "y1": 70, "x2": 170, "y2": 70},
        {"x1": 250, "y1": 70, "x2": 300, "y2": 70},
        {"x1": 120, "y1": 176, "x2": 170, "y2": 176},
        {"x1": 250, "y1": 176, "x2": 300, "y2": 176},
        {"x1": 450, "y1": 70, "x2": 500, "y2": 70},
        {"x1": 580, "y1": 70, "x2": 630, "y2": 70},
    ],
    notes=[{"x": 400, "y": 228,
            "text": "constant => inputs read all zeros; balanced => never",
            "anchor": "middle", "size": 12, "color": "#1d1d1d"}],
)

# --- Grover: uniform superposition, then repeat oracle + diffusion ----------
g.emit(
    "grover-circuit", 860, 190,
    nodes=[
        box(30, 90, ["|0>^n"], "sub"),
        box(170, 80, ["H (all)"], "accent"),
        box(300, 130, ["oracle", "mark |w>"], "box"),
        box(480, 140, ["diffusion", "reflect"], "box"),
        box(680, 110, ["measure"], "ink"),
    ],
    edges=[
        wire(120, 170),
        wire(250, 300),
        wire(430, 480),
        wire(620, 680),
        {"x1": 550, "y1": 28, "x2": 365, "y2": 28, "label": "x (pi/4) sqrt(2^n)",
         "amber": True, "dashed": True, "ly": -6},
    ],
    notes=[{"x": 430, "y": 170,
            "text": "each round rotates amplitude onto the marked item",
            "anchor": "middle", "size": 12, "color": "#1d1d1d"}],
)

# --- Phase estimation: counting register + eigenstate ----------------------
g.emit(
    "phase-estimation-circuit", 860, 240,
    nodes=[
        {"x": 30, "y": 44, "w": 100, "h": 52, "style": "sub", "lines": ["|0>^t", "counting"]},
        {"x": 30, "y": 150, "w": 100, "h": 52, "style": "sub", "lines": ["|psi>", "eigenstate"]},
        {"x": 170, "y": 44, "w": 80, "h": 52, "style": "accent", "lines": ["H (all)"]},
        {"x": 300, "y": 44, "w": 150, "h": 158, "style": "box",
         "lines": ["controlled", "U^(2^j)", "qubit j -> U"]},
        {"x": 500, "y": 44, "w": 120, "h": 52, "style": "box", "lines": ["inverse QFT"]},
        {"x": 670, "y": 44, "w": 110, "h": 52, "style": "ink", "lines": ["measure"]},
    ],
    edges=[
        {"x1": 130, "y1": 70, "x2": 170, "y2": 70},
        {"x1": 250, "y1": 70, "x2": 300, "y2": 70},
        {"x1": 130, "y1": 176, "x2": 300, "y2": 176},
        {"x1": 450, "y1": 70, "x2": 500, "y2": 70},
        {"x1": 620, "y1": 70, "x2": 670, "y2": 70},
    ],
    notes=[{"x": 420, "y": 228,
            "text": "the inverse QFT reads the eigenphase into the counting register",
            "anchor": "middle", "size": 12, "color": "#1d1d1d"}],
)

# --- Shor: order-finding (QPE on U_a) then classical post-processing --------
g.emit(
    "shor-circuit", 940, 240,
    nodes=[
        {"x": 30, "y": 44, "w": 100, "h": 52, "style": "sub", "lines": ["|0>^t", "counting"]},
        {"x": 30, "y": 150, "w": 100, "h": 52, "style": "sub", "lines": ["|1>", "target"]},
        {"x": 170, "y": 44, "w": 80, "h": 52, "style": "accent", "lines": ["H (all)"]},
        {"x": 300, "y": 44, "w": 150, "h": 158, "style": "box",
         "lines": ["controlled", "U_a^(2^j)", "y -> a*y mod N"]},
        {"x": 500, "y": 44, "w": 110, "h": 52, "style": "box", "lines": ["inverse QFT"]},
        {"x": 660, "y": 44, "w": 90, "h": 52, "style": "ink", "lines": ["measure"]},
        {"x": 800, "y": 44, "w": 120, "h": 52, "style": "accent",
         "lines": ["cont. fraction", "+ gcd"]},
    ],
    edges=[
        {"x1": 130, "y1": 70, "x2": 170, "y2": 70},
        {"x1": 250, "y1": 70, "x2": 300, "y2": 70},
        {"x1": 130, "y1": 176, "x2": 300, "y2": 176},
        {"x1": 450, "y1": 70, "x2": 500, "y2": 70},
        {"x1": 610, "y1": 70, "x2": 660, "y2": 70},
        {"x1": 750, "y1": 70, "x2": 800, "y2": 70, "amber": True, "label": "s/r"},
    ],
    notes=[{"x": 470, "y": 228,
            "text": "quantum order-finding, then a classical gcd splits N",
            "anchor": "middle", "size": 12, "color": "#1d1d1d"}],
)

# --- VQE: the quantum-classical optimization loop --------------------------
g.emit(
    "vqe-loop", 760, 220,
    nodes=[
        {"x": 40, "y": 70, "w": 170, "h": 64, "style": "accent",
         "lines": ["classical optimizer", "propose theta"]},
        {"x": 300, "y": 70, "w": 160, "h": 64, "style": "box",
         "lines": ["quantum ansatz", "|psi(theta)>"]},
        {"x": 550, "y": 70, "w": 170, "h": 64, "style": "ink",
         "lines": ["measure energy", "<psi|H|psi>"]},
    ],
    edges=[
        {"x1": 210, "y1": 102, "x2": 300, "y2": 102, "label": "theta"},
        {"x1": 460, "y1": 102, "x2": 550, "y2": 102},
        {"x1": 635, "y1": 134, "x2": 125, "y2": 134, "amber": True, "dashed": True,
         "label": "lower energy -> new theta", "ly": 14},
    ],
    notes=[{"x": 380, "y": 200,
            "text": "repeat until the energy stops dropping: the ground-state estimate",
            "anchor": "middle", "size": 12, "color": "#1d1d1d"}],
)

# --- QAOA: cost + mixer layers with a classical tuning loop -----------------
g.emit(
    "qaoa-circuit", 920, 220,
    nodes=[
        box(30, 90, ["|0>^n"], "sub"),
        box(160, 70, ["H (all)"], "accent"),
        box(280, 120, ["cost layer", "ZZ per edge"], "box"),
        box(450, 120, ["mixer", "RX per qubit"], "box"),
        box(640, 90, ["measure"], "ink"),
        {"x": 770, "y": 44, "w": 120, "h": 52, "style": "accent",
         "lines": ["optimizer", "tune gamma, beta"]},
    ],
    edges=[
        wire(120, 160),
        wire(250, 280),
        wire(400, 450),
        wire(570, 640),
        wire(730, 770),
        {"x1": 830, "y1": 130, "x2": 340, "y2": 130, "amber": True, "dashed": True,
         "label": "new angles", "ly": -6},
    ],
    notes=[{"x": 460, "y": 200,
            "text": "tune the two angles to maximize the cut, then read the answer",
            "anchor": "middle", "size": 12, "color": "#1d1d1d"}],
)

print("wrote 10 diagram pairs to assets/diagrams/")
