#include <iostream>
#include "organizer.h"

int main(){

std::string file = "rooms_pool.csv";  //csv files
std::string file2 = "classes_demand.csv";
csvparser(file, file2); //begin parsing

return 0;
}
