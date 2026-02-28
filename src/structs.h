#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

struct Class {
    int classId;
    int enrollment;
    int days;
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

#endif  // STRUCTS_H