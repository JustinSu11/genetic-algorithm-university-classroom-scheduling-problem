#include <iostream>
#include "organizer.h"

int main(){

std::string file = "../csv-files/rooms_pool.csv";  //csv files
std::string file2 = "../csv-files/classes_demand.csv";
std::vector<Room> rooms; //vectors to hold the data from csv files
std::vector<Class> classes;
csvparser(file, file2, rooms, classes); //begin parsing

// Seed RNG and generate initial population
srand(time(nullptr));
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

// Compute fitness for all chromosomes
for (int i = 0; i < mainpop.size(); i++) {
    mainpop[i].fitness = computeFitness(mainpop[i].chromosome, classes, rooms);
}

// Test tournament selection
std::cout << "\n--- Testing Tournament Selection ---" << std::endl;
std::cout << "First 5 fitness scores: ";
for (int i = 0; i < 5; i++) {
    std::cout << mainpop[i].fitness << " ";
}
std::cout << std::endl;

// Perform 3 tournament selections to demonstrate
for (int t = 0; t < 3; t++) {
    int selectedIdx = tournamentSelection(mainpop, 5);
    std::cout << "Tournament " << (t+1) << " selected index " << selectedIdx 
              << " with fitness " << mainpop[selectedIdx].fitness 
              << ", H= " << computeH(mainpop[selectedIdx].chromosome, classes, rooms) << std::endl;
}

return 0;
}
