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
  
//inital setup ends here
//start of loop
// vector to hold the populations
std::vector<std::vector<ChromosomeStruct>> GenerationalRun; 

// 500 generations in the making
for(int i = 0; i < 500; i++){
//passing vector struct mainpop to elite
std::vector<double> elitechromo = elite(mainpop);
//2 parents breeding each time so we do it 50 times so we get 100 kids
for(int j = 0; j < 50; j++){ 
int idx1 = tournamentSelection(mainpop, 5); //tournament selection
int idx2 = tournamentSelection(mainpop, 5); //tournament selection
ChromosomeStruct parent1 = mainpop[idx1];
ChromosomeStruct parent2 = mainpop[idx2];
ChromosomeStruct child1, child2;
Children youngsters = crossover(parent1.chromosome, parent2.chromosome); //crossover happens here
child1.chromosome = youngsters.child1;  // copy youngster struct and map it to the child1 and child2 struct that was made above
child2.chromosome = youngsters.child2;
child1.fitness = computeFitness(child1.chromosome, classes, rooms);  // compute fitness for child1 and child2
child2.fitness = computeFitness(child2.chromosome, classes, rooms);
}

}


return 0;
}
