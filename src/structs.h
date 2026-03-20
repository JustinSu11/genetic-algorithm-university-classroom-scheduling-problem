#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>
#include <string>

struct Class {
    int classId;
    int enrollment;
    unsigned int days; // string to bitmask that is found in csvparser.cpp
    int startSlot;
    int length;
};

struct Room {
    int roomId;
    int capacity;
    std::string building;
    int x;
    int y;
};

struct Chromosome {
    std::vector<int> chromosome; // room index for each class
    double fitness;
};

#endif  // STRUCTS_H
