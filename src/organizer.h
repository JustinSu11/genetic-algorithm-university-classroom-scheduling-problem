#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "structs.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <utility>

int csvparser(std::string filename, std::string filename2, std::vector<Room>& rooms, std::vector<Class>& classes);

// Generate a single random chromosome: phi[i] = room index for class i
std::vector<int> generateRandomChromosome(int numClasses, int numRooms);

// Generate a population of random chromosomes
std::vector<ChromosomeStruct> generatePopulation(int popSize, int numClasses, int numRooms, const std::vector<Room>& rooms, const std::vector<Class>& classes);

// Compute hard penalty H: room conflicts + capacity violations
int computeH(const std::vector<int>& phi,
             const std::vector<Class>& classes,
             const std::vector<Room>& rooms);

// Compute soft penalty S: per-day sorted travel distance (enrollment * euclidean dist)
double computeS(const std::vector<int>& phi,
                const std::vector<Class>& classes,
                const std::vector<Room>& rooms);

// Compute fitness f = 1 / (1 + wh*H + ws*S)
double computeFitness(const std::vector<int>& phi,
                      const std::vector<Class>& classes,
                      const std::vector<Room>& rooms);

// moving the best chromosomes based on fitness to an elite array to skip tourney
std::vector<double> elite(std::vector<ChromosomeStruct> &chromofitness);

// Tournament selection: pick k random individuals, return index of the best
// k=5 per spec, but configurable
int tournamentSelection(const std::vector<ChromosomeStruct>& population, int k = 5);

// one-point crossover
Children crossover(const std::vector<int> &parent1, const std::vector<int> &parent2);

#endif
