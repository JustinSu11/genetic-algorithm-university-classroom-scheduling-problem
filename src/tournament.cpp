#include "organizer.h"

// ---------------------------------------------------------------------------
// tournamentSelection — select a parent via tournament selection
//
// Strategy:
//   1. Randomly pick k individuals from the population
//   2. Return the index of the one with the highest fitness
//
// Parameters:
//   population — the current population of chromosomes
//   fitness    — precomputed fitness scores (fitness[i] for population[i])
//   k          — tournament size (default = 5 per spec)
//
// Returns: index of the selected individual in the population
// ---------------------------------------------------------------------------
int tournamentSelection(const std::vector<std::vector<int>>& population,
                        const std::vector<double>& fitness,
                        int k)
{
    int popSize = (int)population.size();
    
    // Pick first random individual
    int bestIdx = rand() % popSize;
    double bestFit = fitness[bestIdx];
    
    // Pick k-1 more and track the best
    for (int i = 1; i < k; i++) {
        int idx = rand() % popSize;
        if (fitness[idx] > bestFit) {
            bestIdx = idx;
            bestFit = fitness[idx];
        }
    }
    
    return bestIdx;
}
