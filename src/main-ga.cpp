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

return 0;
}
