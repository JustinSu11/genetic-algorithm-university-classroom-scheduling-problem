#include "organizer.h"

std::vector<int> generateRandomChromosome(int numClasses, int numRooms) {
    std::vector<int> chromosome(numClasses);
    for (int i = 0; i < numClasses; i++) {
        chromosome[i] = rand() % numRooms;
    }
    return chromosome;
}

std::vector<std::vector<int>> generatePopulation(int popSize, int numClasses, int numRooms) {
    std::vector<std::vector<int>> population(popSize);
    for (int i = 0; i < popSize; i++) {
        population[i] = generateRandomChromosome(numClasses, numRooms);
    }
    return population;
}