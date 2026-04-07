#include "organizer.h"

std::vector<int> mutate(const std::vector<int> &chromosome, int numRooms) {
    // gives a float from 0 to 1 and scales it by 0.02 then shifts by .01 and maps it to between .01 and .03, drawn once for each chromosome for slight different rates between chromosomes in the same generation.
    double mutationRate = 0.01 + (rand() / (double)RAND_MAX) * 0.02; 
    //copy the chromosome to modify without affecting original
    std::vector<int> mutatedChromosome = chromosome;
    for (int i = 0; i < mutatedChromosome.size(); i++) {
        double possibility = rand() / double(RAND_MAX); // gives a float from 0 to 1
        if (possibility < mutationRate) { //1% to 3% chance to mutate each gene based off the range of mutation rates the professor gave us.
            //mutate this gene by assigning it a random room number between 0 and numRooms-1
            mutatedChromosome[i] = rand() % numRooms;
        }
    }
    return mutatedChromosome;
}