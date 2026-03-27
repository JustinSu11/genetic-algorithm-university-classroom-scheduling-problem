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


return 0;
}
