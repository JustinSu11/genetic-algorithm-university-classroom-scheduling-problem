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
return 0;
}
