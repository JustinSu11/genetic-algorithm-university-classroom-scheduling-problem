#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "structs.h"
#include <vector>
#include <string>
#include <cstdlib>

int csvparser(std::string filename, std::string filename2, std::vector<Room>& rooms, std::vector<Class>& classes);

// Generate a single random chromosome: phi[i] = room index for class i
std::vector<int> generateRandomChromosome(int numClasses, int numRooms);

// Generate a population of random chromosomes
std::vector<std::vector<int>> generatePopulation(int popSize, int numClasses, int numRooms);

#endif
