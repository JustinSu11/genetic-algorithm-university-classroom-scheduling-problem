# Genetic Algorithm — University Classroom Scheduling

**Course:** COSC4330.001 — Spring 2026
**Due:** April 27 | **Points:** 20
**Language:** C++ only

---

## The Problem

Assign **2,418 classes** to **221 rooms** with two hard rules and one soft goal:

1. No two classes share a room at overlapping times *(hard)*
2. No class exceeds the room's capacity *(hard)*
3. Minimize student travel between back-to-back classes *(soft)*

There are too many possible assignments to check by brute force (221^2418). A genetic algorithm searches the space by evolving better solutions over generations.

---

## The Data

**`classes_demand.csv`** — one row per class
- `ClassID` — class index
- `Enrollment` — number of students
- `Days` — 7-char bitmask string, e.g. `"1010100"` = Mon/Wed/Fri (M,T,W,Th,F,Sa,Su left to right)
- `StartSlot` — when the class begins
- `Length` — how many slots it lasts

**`rooms_pool.csv`** — one row per room
- `RoomID` — room identifier (not necessarily 0-indexed — build a map)
- `Capacity` — max students
- `X, Y` — building coordinates for travel distance

---

## The Chromosome

A solution is an array of 2,418 integers: `phi[i]` = the room assigned to class `i`.

That's it. One number per class. The GA evolves a population of these arrays toward better fitness scores.

---

## The Fitness Function

```
f(phi) = 1 / (1 + wh * H + ws * S)
```

Range is `(0, 1]`. Score of 1.0 = perfect. Every violation drags it toward 0.

**wh = 10,000 | ws = 1** — one hard violation is 10,000x worse than one unit of travel. The GA eliminates conflicts before it worries about walk distance.

### H — Hard Penalty
Count of: **(room conflicts) + (capacity violations)**

Two classes **conflict** if they share the same room AND:
1. **Share a day** — convert the days string to a 7-bit integer. Bitwise AND the two masks. If result ≠ 0, they share at least one day.
2. **Times overlap** — `max(start_a, start_b) < min(end_a, end_b)` where `end = start + length`

Both conditions must be true. A MWF class and a TTh class in the same room never actually conflict, even if their time slots would overlap.

### S — Soft Penalty (Travel Distance)
For each day, sort all classes meeting that day by start time. Sum up `enrollment × distance` for each consecutive pair, where distance is Euclidean between room coordinates.

---

## The GA Loop

1. **Initialize** — 100 random chromosomes (`srand(42)`)
2. **Score** — compute fitness for all
3. **Repeat 500+ generations:**
   - Copy the best chromosome directly into the next generation (elitism)
   - Fill remaining slots: tournament select 2 parents → one-point crossover → mutate
   - Re-score, track best seen
4. **Return** the best chromosome found

**Tournament selection** — pick 5 random individuals, take the best. Repeat for the second parent.

**One-point crossover** — split at a random index, take left half from parent 1 and right half from parent 2.

**Mutation** — each gene independently reassigned to a random room with probability `1/2418 ≈ 0.0004`.

---

## Key Parameters

| Parameter | Value |
|-----------|-------|
| Population size | 100 |
| Generations | 500+ |
| Tournament size | 5 |
| Crossover rate | 0.8 |
| Mutation rate | 1/N ≈ 0.0004 |
| Hard weight `wh` | 10,000 |
| Seed | `srand(42)` |

---

## Pitfalls

1. **RoomID ≠ array index** — build a `roomId → index` map at load time
2. **wh miscalibration** — print raw H and S from your first population; make sure one conflict is always worse than any feasible S
3. **Losing best solution** — elitism prevents this; always copy best into the next gen
4. **Bitmask indexing** — bit 6 = Monday (leftmost char). Double-check with a known class
5. **Off-by-one in overlap** — `end = start + len`, not `start + len - 1`

---

## Deliverables

| Item | Details |
|------|---------|
| C++ implementation | GA + random baseline, `srand(42)` |
| Fitness plot | Best fitness per generation (100+ gens) |
| Comparison table | Random baseline vs GA (H violations + fitness) |
| Written report | Chromosome design, fitness formulation, weight justification, results |
| Oral presentation | 10 min — scaling, demo, convergence |

### Grading
| Criterion | Weight |
|-----------|--------|
| Implementation | 40% |
| Written documentation | 25% |
| Oral presentation & Q&A | 20% |
| H = 0 achieved | 10% |
| Baseline vs GA analysis | 5% |

**Bonus (+10%):** elitism, adaptive mutation, heuristic init (big classes → big rooms first), visualizations

---

## Tasks

### Setup
- [ ] Read `classes_demand.csv` and `rooms_pool.csv` into structs
- [ ] Convert days strings to bitmask integers at load time
- [ ] Build `roomId → index` map (RoomIDs may not be 0-indexed)

### Core Implementation
- [ ] Implement random chromosome generator (`srand(42)`)
- [ ] Implement `computeH` — capacity violations + room conflict pairs
- [ ] Implement `computeS` — per-day sorted travel distance
- [ ] Implement fitness function `f = 1 / (1 + wh*H + ws*S)`
- [ ] Implement tournament selection (k=5)
- [ ] Implement one-point crossover
- [ ] Implement random resetting mutation (pm = 1/N)
- [ ] Implement elitism (copy best into each new generation)
- [ ] Wire up the full GA loop (500+ generations, population of 100)

### Baseline
- [ ] Implement random baseline — generate 100 random chromosomes, return the best
- [ ] Record baseline H violations and fitness score

### Tuning & Validation
- [ ] Print raw H and S from initial population — verify wh=10000 makes sense
- [ ] Verify conflict detection with a known overlapping pair
- [ ] Verify bitmask encoding against a known class's days string
- [ ] Run GA and confirm fitness improves each generation
- [ ] Achieve H = 0 (no hard violations)

### Deliverables
- [ ] Export fitness-per-generation data and plot it (Python/Excel/gnuplot)
- [ ] Build comparison table: random baseline vs GA final
- [ ] Write report (abstract, chromosome design, fitness formulation, weight justification, results)
- [ ] Prepare 10-min presentation (scaling, demo, convergence behavior)
