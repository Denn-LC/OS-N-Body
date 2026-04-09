# CLAUDE.md

## Who I Am
I am learning C for the first time, coming from Python. This project is how I am learning — so explanations matter as much as the code itself. Treat me like a strong beginner: I can handle real concepts but need them explained with intuition first, heavy math second.

## What This Project Is
An N-body gravitational simulator written in C. It simulates bodies attracting each other under Newtonian gravity and outputs their positions each step. Eventually it will connect to a friend's graphics API to render visually.

This is a **learning project first**, a simulator second.

## Target Environment
- Runs inside a custom OS — treat this as a constrained embedded-like environment
- Only standard C libraries allowed: `stdio.h`, `math.h`, `stdlib.h`, `time.h`
- No external libraries, no dynamic memory (no malloc/free)
- Must be lightweight, portable, and self-contained
- Keep everything in one or a few files

## Current State
- Structs defined: `vec2_t` (x/y pair), `body_t` (pos, vel, acc, mass)
- Four scenarios: two-body orbit, three-body system, figure-8, entropymaxxing (random)
- Physics loop: compute forces → integrate → energy check → print state
- Euler integration (known limitation: energy drift over time)
- Energy conservation check with 1% threshold (disabled for entropymaxxing)

## Roadmap
1. [x] Array refactor — store bodies in structs, nested loop, scales to 10 bodies
2. [ ] Clean I/O output — parseable format for graphics API
3. [ ] Graphics API integration — coordinate with friend

## How to Explain Things to Me
- Lead with intuition and analogy, not equations
- Use Python comparisons where helpful (classes vs structs, etc.)
- Explain *why* something works, not just *what* to write
- When pointing out bugs, explain what would actually go wrong at runtime
- Keep explanations short and practical — I will ask follow up questions

## Coding Style
- K&R brace style
- Small, readable functions
- Simple and explicit over clever
- Beginner-intermediate level — no advanced C tricks

## Physics Rules
- Newtonian gravity, G = 1.0 (fictional units)
- Small timestep (DT = 0.01)
- Double precision throughout
- No need to optimise — correctness and clarity first

## Behaviour Rules
- Always explain changes before making them
- Prefer the smallest working change
- Do not rewrite large parts of the code unless explicitly asked
- If something has a bug, explain what would go wrong before fixing it
- Do not add features, abstractions, or error handling beyond what is asked
