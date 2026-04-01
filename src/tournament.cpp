#include "organizer.h"

// ---------------------------------------------------------------------------
// tournamentSelection — select a parent via tournament selection
//
// Strategy:
//   1. Randomly pick k individuals from the population
//   2. Return the index of the one with the highest fitness
//
// Parameters:
//   population — alias for mainpop
//   k          — tournament size (default = 5 per spec)
//   popSize    — size of the population (default = 100)
//
// Returns: index of the selected individual in the population
// ---------------------------------------------------------------------------
int tournamentSelection(const std::vector<ChromosomeStruct>& population, int k)
{
    // Pick first random individual
    int bestIdx = rand() % population.size();
    double bestFit = population[bestIdx].fitness;
    
    // Pick k-1 more and track the best
    for (int i = 1; i < k; i++) {
        int idx = rand() % population.size();
        if (population[idx].fitness > bestFit) {
            bestIdx = idx;
            bestFit = population[idx].fitness;
        }
    }
    
    return bestIdx;
}
