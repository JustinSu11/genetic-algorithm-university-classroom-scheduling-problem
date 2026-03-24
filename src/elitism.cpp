#include "organizer.h"
#include <iostream>

/* 
main-ga -> csvparser -> main-ga -> chromosome -> fitness -> chromosome -> main-ga -> elitism 

TODOs:

create function to take population vector (the one in main-ga)
for loop to iterate population[i].fitness
if condition to find the largest fitness
seperate array to hold the elite (vector)
maybe some other stuff but for now this will do

*/ 
//chromofitness[i].fitness is an alias for mainpop[i].fitness
void elite(std::vector<ChromosomeStruct> &chromofitness) {
 std::vector<double> theBest; // vector to hold the best of the best
 double largest = chromofitness[0].fitness;
 int index = 0;  
for(size_t i = 0 + 1; i < chromofitness.size(); i++){
 if(largest < chromofitness[i].fitness){
    largest = chromofitness[i].fitness;
    index = i; 
}
}

//debug print
for(size_t i = 0; i < chromofitness.size(); i++){
 std::cout << "index: " << i << ": " << chromofitness[i].fitness << std::endl; 
} 
std::cout << "Largest: " << largest << " at index: " << index << std::endl;
  theBest.push_back(largest); // put largest into theBest vector
  chromofitness.erase(chromofitness.begin() + index); // remove current largest from the chromosome pool

std::cout << "updated array: " << std::endl;
//debug print
for(size_t i = 0; i < chromofitness.size(); i++){
 std::cout << "index: " << i << ": " << chromofitness[i].fitness << std::endl;
}

}

