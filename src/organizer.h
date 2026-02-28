#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "structs.h"
#include <vector>
#include <string>

int csvparser(std::string filename, std::string filename2, std::vector<Room>& rooms, std::vector<Class>& classes);
void readRooms(std::vector<Room>& rooms);
void readClasses(std::vector<Class>& classes);

#endif
