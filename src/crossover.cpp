#include "organizer.h"

// One-point crossover
// Pick a random split point, take genes 0..point-1 from parent1
// and genes point..n-1 from parent2
// we use parent1.size() since the 2 parents should be the same size
std::vector<int> crossover(const std::vector<int> parent1, const std::vector<int> parent2)
{
    int point = rand() % parent1.size();  // Random split point in [0, n-1]
    
    std::vector<int> child(parent1.size());
    //Here we iterate through the child array which and copy the genes from parent 1 if the index is less than the randomly generated point.
    for (int i = 0; i < parent1.size(); i++) {
        if (i < point) {
            child[i] = parent1[i];
        } else {
            child[i] = parent2[i];
        };
    }
    
    return child;
}