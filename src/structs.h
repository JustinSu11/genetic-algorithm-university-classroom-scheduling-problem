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

struct ChromosomeStruct {

    std::vector<int> chromosome; // room index for each class
    double fitness;
    int H; // hard penalty
    double S; // soft penalty
};

struct Children {
std::vector<int> child1; //struct so i can return child1 and child2 in crossover.cpp
std::vector<int> child2;
};

#endif  // STRUCTS_H
