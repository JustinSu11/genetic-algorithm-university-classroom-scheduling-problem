#include "organizer.h"


/* iterate through the entire population and pick like the 5 best chromosomes to move to the next round 
 vector struct generatepopulation function returns vector struct population to main (in chromosome.cpp)
(now in main-ga.cpp) it is stored in a vector struct population in main
 main prints population stuff

TODOs:

create function to take population vector (the one in main-ga)
for loop to iterate population[i].fitness
if condition to find the largest fitness
seperate array to hold the elite (will do memory alloc with new/delete)
maybe some other stuff but for now this will do

*/ 
