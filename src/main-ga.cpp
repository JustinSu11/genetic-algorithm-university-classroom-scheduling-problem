#include <iostream>
#include "organizer.h"

int main(){

std::string file = "../csv-files/rooms_pool.csv";  //csv files
std::string file2 = "../csv-files/classes_demand.csv";
std::vector<Room> rooms; //vectors to hold the data from csv files
std::vector<Class> classes;
csvparser(file, file2, rooms, classes); //begin parsing

// Seed RNG and generate initial population
srand(42);
int numClasses = classes.size();
int numRooms = rooms.size();
int popSize = 100;

std::vector<Chromosome> population = generatePopulation(popSize, numClasses, numRooms, rooms, classes);  
std::cout << "Generated " << population.size() << " chromosomes, each with " << population[0].chromosome.size() << " genes." << std::endl;

std::cout << "Fitness: " << population[0].fitness << ", H= " << computeH(population[0].chromosome, classes, rooms) << std::endl;
return 0;
}
