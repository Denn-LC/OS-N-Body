# CLAUDE.md

## Context
This is a simple N-body simulation written in C, targeting a custom OS environment.

Target environment:
- Runs inside a custom OS environment (confirmed: supports doubles, stdio, math)
- Only standard C libraries allowed (stdio, math)
- No fancy external libraries
- Keep everything lightweight and portable


## Goals
- Refactor to arrays of bodies (up to 10 bodies max)
- Implement O(n²) nested loop for force calculations
- Output body positions each step in a clean format for graphics API integration
- Eventually integrate with a graphics API
- Prioritize correctness and clarity over performance — no optimizations needed at 10 bodies

## Roadmap
1. [ ] Array refactor — store bodies in arrays, nested loop, scales to 10 bodies
2. [ ] Clean I/O output — one line per step, all body positions, parseable by graphics API
3. [ ] Graphics API integration

## Coding Style
- Use K&R brace style
- Keep functions small and readable
- Prefer simple, explicit code
- Avoid clever tricks or overly compact code
- Keep everything beginner-intermediate level

## Constraints
- Do NOT use dynamic memory (no malloc/free)
- Do NOT introduce complex abstractions
- Do NOT use advanced libraries or frameworks
- Do NOT overengineer the physics
- Keep everything in one or a few files

## Physics Rules
- Use Newtonian gravity
- Use a constant G (e.g. G = 1.0)
- Use a small timestep (dt)
- Include a small softening factor to avoid division by zero
- Use double precision

## Behaviour Rules
- Always explain changes clearly
- Prefer the smallest working solution
- Do not rewrite large parts of the code unless asked
- If improving code, explain why

## Teaching Style
- Explain like I am a strong beginner
- Focus on intuition over heavy math
- Keep explanations practical and relevant