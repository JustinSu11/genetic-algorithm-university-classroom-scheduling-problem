#include <iostream>
#include "organizer.h"

int main(){

std::string file = "../csv-files/rooms_pool.csv";  //csv files
std::string file2 = "../csv-files/classes_demand.csv";
std::vector<Room> rooms; //vectors to hold the data from csv files
std::vector<Class> classes;
csvparser(file, file2, rooms, classes); //begin parsing

// Seed RNG and generate initial population
srand(time(nullptr));  // Seed random number generator with current time
int numClasses = classes.size();
int numRooms = rooms.size();
int popSize = 100;

// population variable in main
std::vector<ChromosomeStruct> mainpop = generatePopulation(popSize, numClasses, numRooms, rooms, classes);  
std::cout << "Generated " << mainpop.size() << " chromosomes, each with " << mainpop[0].chromosome.size() << " genes." << std::endl;
std::cout << "Fitness: " << mainpop[0].fitness << ", H= " << computeH(mainpop[0].chromosome, classes, rooms) << std::endl;

//passing vector struct mainpop to elite
std::vector<double> elitechromo = elite(mainpop);
//displaying elite array
std::cout << "Elite Array:\n";
for(size_t i = 0; i < elitechromo.size(); i++){
    std::cout << elitechromo[i] << std::endl;
}

// Test tournament selection
std::cout << "\n--- Testing Tournament Selection ---" << std::endl;

// Perform 3 tournament selections to demonstrate
//Uncomment code below to test tournament selection
for (int t = 0; t < 3; t++) {
    int selectedIdx = tournamentSelection(mainpop, 5);
    std::cout << "Tournament " << (t+1) << " selected index " << selectedIdx 
              << " with fitness " << mainpop[selectedIdx].fitness 
              << ", H= " << computeH(mainpop[selectedIdx].chromosome, classes, rooms) << std::endl;
}

//testing crossover
// Uncomment the below code to test the crossover function
// std::cout << "\n--- Testing Crossover ---" << std::endl;
// ChromosomeStruct parent1 = mainpop[tournamentSelection(mainpop, 5)];
// ChromosomeStruct parent2 = mainpop[tournamentSelection(mainpop, 5)];
// ChromosomeStruct child1, child2;
// std::tie(child1.chromosome, child2.chromosome) = crossover(parent1.chromosome, parent2.chromosome);
// child1.fitness = computeFitness(child1.chromosome, classes, rooms);
// child2.fitness = computeFitness(child2.chromosome, classes, rooms);
// std::cout << "Parent 1: " << std::endl;
// for (int i = 0; i < parent1.chromosome.size(); i++) {
//     std::cout << parent1.chromosome[i] << " ";
// }
// std::cout << std::endl;
// std::cout << "Parent 2: " << std::endl;
// for (int i = 0; i < parent2.chromosome.size(); i++) {
//     std::cout << parent2.chromosome[i] << " ";
// }
// std::cout << std::endl;
// std::cout << "Child1: " << std::endl;
// for (int i = 0; i < child1.chromosome.size(); i++) {
//     std::cout << child1.chromosome[i] << " ";
// }
// std::cout << std::endl;
// std::cout << "Child2: " << std::endl;
// for (int i = 0; i < child2.chromosome.size(); i++) {
//     std::cout << child2.chromosome[i] << " ";
// }
// std::cout << std::endl;

return 0;
}
