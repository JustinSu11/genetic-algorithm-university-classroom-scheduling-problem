#include <iostream>
#include "organizer.h"

int main(){

std::string file = "../csv-files/rooms_pool.csv";  //csv files
std::string file2 = "../csv-files/classes_demand.csv";
std::vector<Room> rooms; //vectors to hold the data from csv files
std::vector<Class> classes;
csvparser(file, file2, rooms, classes); //begin parsing

// Seed RNG and generate initial population
srand(42);  // Seed random number generator with current time
int numClasses = classes.size();
int numRooms = rooms.size();
int popSize = 100;

// population variable in main
std::vector<ChromosomeStruct> mainpop = generatePopulation(popSize, numClasses, numRooms, rooms, classes);
  
//inital setup ends here
//start of loop
// vector to hold the populations
std::vector<std::vector<ChromosomeStruct>> GenerationalRun; 
GenerationalRun.reserve(500);//reserve space for 500 elements for easier mem alloc
// 500 generations in the making
for(int i = 0; i < 500; i++){
std::vector<ChromosomeStruct> genchild; //use to hold the children during the breeding process
genchild.reserve(100);
//passing vector struct mainpop to elite
std::vector<ChromosomeStruct> elitechromo = elite(mainpop);
//pushing the individual elite structs onto the genchild vector cuz genchild cant fit a vector only ChromosomeStruct
for(int e = 0; e < elitechromo.size(); e++){
genchild.push_back(elitechromo[e]); 
}
//2 parents breeding each time so we do it 48 times so we get 96 kids (we will already have 4 elites in the next population) 
for(int j = 0; j < 48; j++){ 
int idx1 = tournamentSelection(mainpop, 5); //tournament selection
int idx2 = tournamentSelection(mainpop, 5); //tournament selection
ChromosomeStruct parent1 = mainpop[idx1];
ChromosomeStruct parent2 = mainpop[idx2];
ChromosomeStruct child1, child2;
Children youngsters = crossover(parent1.chromosome, parent2.chromosome); //crossover happens here
child1.chromosome = youngsters.child1;  // copy youngster struct and map it to the child1 and child2 struct that was made above
child2.chromosome = youngsters.child2;
child1.chromosome = mutate(child1.chromosome, numRooms); //mutate child1
child2.chromosome = mutate(child2.chromosome, numRooms); //mutate child2
child1.fitness = computeFitness(child1.chromosome, classes, rooms);  // compute fitness for child1 and child2
child2.fitness = computeFitness(child2.chromosome, classes, rooms);
genchild.push_back(child1);
genchild.push_back(child2); // adding both childs into the array 
}
 mainpop = genchild; //cycle out the old population with the one collected from genchild vector
 GenerationalRun.push_back(mainpop); //add current iteration of mainpop into the generation pool
}
exportSchedule(GenerationalRun, classes, rooms);
exportConvergence(GenerationalRun);


return 0;
}
