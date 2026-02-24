#include <iostream>
#include "organizer.h"

void readRooms(std::vector<Room>& rooms) {
    // code to read rooms from csv and populate the rooms vector
    for (const Room& room : rooms) {
        std::cout << "Room ID: " << room.roomId << ", Capacity: " << room.capacity
                  << ", Building: " << room.building << ", X: " << room.x << ", Y: " << room.y << std::endl;
    }
}

void readClasses(std::vector<Class>& classes) {
    // code to read classes from csv and populate the classes vector
    for (const Class& c : classes) {
        std::cout << "Class ID: " << c.classId << ", Enrollment: " << c.enrollment
                  << ", Days: " << c.days << ", Start Slot: " << c.startSlot << ", Length: " << c.length << std::endl;
    }
}

int main(){

std::string file = "rooms_pool.csv";  //csv files
std::string file2 = "classes_demand.csv";
std::vector<Room> rooms; //vectors to hold the data from csv files
std::vector<Class> classes;
csvparser(file, file2, rooms, classes); //begin parsing

readClasses(classes);
readRooms(rooms);

return 0;
}
