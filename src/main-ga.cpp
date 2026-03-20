#include <iostream>
#include "organizer.h"

int main(){

std::string file = "../csv-files/rooms_pool.csv";  //csv files
std::string file2 = "../csv-files/classes_demand.csv";
std::vector<Room> rooms; //vectors to hold the data from csv files
std::vector<Class> classes;
csvparser(file, file2, rooms, classes); //begin parsing

readClasses(classes);
readRooms(rooms);
// Seed RNG and generate initial population
srand(42);
int numClasses = classes.size();
int numRooms = rooms.size();
int popSize = 100;

std::vector<std::vector<int>> population = generatePopulation(popSize, numClasses, numRooms);  
std::cout << "Generated " << population.size() << " chromosomes, each with " << population[0].size() << " genes." << std::endl;

// Compute fitness for all chromosomes
std::vector<double> fitnessScores(popSize);
for (int i = 0; i < popSize; i++) {
    fitnessScores[i] = computeFitness(population[i], classes, rooms);
}

// Test tournament selection
std::cout << "\n--- Testing Tournament Selection ---" << std::endl;
std::cout << "First 5 fitness scores: ";
for (int i = 0; i < 5; i++) {
    std::cout << fitnessScores[i] << " ";
}
std::cout << std::endl;

// Perform 3 tournament selections to demonstrate
for (int t = 0; t < 3; t++) {
    int selectedIdx = tournamentSelection(population, fitnessScores, 5);
    std::cout << "Tournament " << (t+1) << " selected index " << selectedIdx 
              << " with fitness " << fitnessScores[selectedIdx] 
              << ", H= " << computeH(population[selectedIdx], classes, rooms) << std::endl;
}

return 0;
}
