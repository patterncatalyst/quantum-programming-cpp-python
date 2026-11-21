# Companion deck

`quantum-programming-cpp-python-deck-r09.0.pptx` is the companion slide deck for the
book. Its arc: an introduction to quantum programming, the relevance to business
processes, and the intersection with post-quantum cryptography in RHEL.

## Build

The deck is generated from `deck.js` with [pptxgenjs](https://gitbrent.github.io/PptxGenJS/):

```bash
cd presentation
npm install        # once, installs pptxgenjs locally
node deck.js       # writes the .pptx in this directory
```

House style helpers live in `deck-helpers.js` and the brand assets in `assets/`
(from the `lgtm-presentation` skill). `node_modules/` and QA renders are git-ignored;
the committed `.pptx` is the deliverable.
