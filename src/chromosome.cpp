#include "organizer.h"
#include "structs.h"

std::vector<int> generateRandomChromosome(int numClasses, int numRooms) {
    std::vector<int> chromosome(numClasses);
    for (int i = 0; i < numClasses; i++) {
        chromosome[i] = rand() % numRooms;  //generate random chromosomes for generating population below
    }
    return chromosome;
}

std::vector<ChromosomeStruct> generatePopulation(int popSize, int numClasses, int numRooms, const std::vector<Room>& rooms, const std::vector<Class>& classes) {
    std::vector<ChromosomeStruct> population(popSize);
    for (int i = 0; i < popSize; i++) {
        population[i].chromosome = generateRandomChromosome(numClasses, numRooms);    // <-
        population[i].fitness = computeFitness(population[i].chromosome, classes, rooms);  // <- assign fitness to the chromosomes in the population
    }
    return population;
}
