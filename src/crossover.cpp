#include "organizer.h"

// One-point crossover
// Pick a random split point, take genes 0..point-1 from parent1
// and genes point..n-1 from parent2
// we use parent1.size() since the 2 parents should be the same size

Children crossover(const std::vector<int> &parent1, const std::vector<int> &parent2) // added & so we dont make useless copies for the generation loop
{   
    Children kid; 
    kid.child1.resize(parent1.size()); //calloc but for vectors aka allocating memory based on parent size 
    kid.child2.resize(parent2.size());
 
    int point = rand() % parent1.size();  // Random split point in [0, n-1]
    
    //Here we iterate through the child array which and copy the genes from parent 1 if the index is less than the randomly generated point.
    for (int i = 0; i < parent1.size(); i++) {
        if (i < point) {
            kid.child1[i] = parent1[i];
            kid.child2[i] = parent2[i];
        } else {
            kid.child1[i] = parent2[i];
            kid.child2[i] = parent1[i];
        }
    }
    
    return kid;
}
