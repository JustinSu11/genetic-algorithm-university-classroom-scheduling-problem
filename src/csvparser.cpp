#include <iostream>
#include "organizer.h"
#include "csv.h"

int csvparser(std::string filename, std::string filename2, std::vector<Room> &rooms, std::vector<Class> &classes)
{
    unsigned int daysbm = 0; // days (bitmask, is unsigned to make it easier)
    // io::CSVREADER<> is a class btw, room and classes are our custom objects

    try
    { // try catch combo to handle errors better
        // for roompool csv
        // csv reader that reads 5 columns cuz roompool csv has 5, trims spaces for values, and ' is the separator but " isnt cuz of building
        io::CSVReader<5, io::trim_chars<' '>, io::double_quote_escape<',', '"'>> room(filename);
        room.read_header(io::ignore_extra_column, "RoomID", "Capacity", "Building", "X", "Y"); // template from
        int roomid;                                                                            // from the
        int capacity;                                                                          // fast cpp csvparser
        std::string building;                                                                  // github
        int x;
        int y;

        // while reading:
        while (room.read_row(roomid, capacity, building, x, y))
        {
            Room r;
            r.roomId = roomid;
            r.capacity = capacity;
            r.building = building;
            r.x = x;
            r.y = y;
            rooms.push_back(r);
        }

        // for class demand csv
        // simpler csv reader header cuz just integers in this csv
        io::CSVReader<5> classReader(filename2);
        classReader.read_header(io::ignore_extra_column, "ClassID", "Enrollment", "Days", "StartSlot", "Length");
        int classid;
        int enrollment;
        std::string days;
        int startslot;
        int length;

        // while reading:
        while (classReader.read_row(classid, enrollment, days, startslot, length))
        {
            Class c;
            c.classId = classid;
            c.enrollment = enrollment;
            // conversion to string to unsigned bitmask, also typecasting string to unsigned long to unsigned int
            daysbm = (unsigned int)std::stoul(days, nullptr, 2);
            c.days = daysbm;
            c.startSlot = startslot;
            c.length = length;
            classes.push_back(c);
        }

        // error report here:
    }
    catch (const std::exception &err)
    {
        std::cerr << "ERROR: " << err.what() << std::endl;
        return 1;
    }

    return 0;
}
