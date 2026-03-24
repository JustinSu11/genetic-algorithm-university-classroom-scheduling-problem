#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "structs.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>

int csvparser(std::string filename, std::string filename2, std::vector<Room>& rooms, std::vector<Class>& classes);
void readRooms(std::vector<Room>& rooms);
void readClasses(std::vector<Class>& classes);

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


void elite(std::vector<ChromosomeStruct> &chromofitness);

#endif
