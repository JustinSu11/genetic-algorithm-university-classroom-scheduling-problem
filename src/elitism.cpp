#include "organizer.h"
#include <iostream>

//chromofitness[i].fitness is an alias for mainpop[i].fitness
std::vector<double> elite(std::vector<ChromosomeStruct> &chromofitness) {
 std::vector<double> theBest; // vector to hold the best of the best
 int numofelite = 5; // number of elites that get to move to the elite array
 int count = 0;
while(count < numofelite){  // run for loop # of times depending on numofelite
 double largest = chromofitness[0].fitness;
 int index = 0;
for(int i = 0 + 1; i < chromofitness.size(); i++){
 if(largest < chromofitness[i].fitness){
    largest = chromofitness[i].fitness;  // largest comparison
    index = i; 
}
}
  theBest.push_back(largest); // put largest into theBest vector
  chromofitness.erase(chromofitness.begin() + index); // remove current largest from the chromosome pool
  count++;
}
return theBest;
 
}

