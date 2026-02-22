#include <iostream>
#include "organizer.h"
#include "csv.h"

int csvparser(std::string filename, std::string filename2){

// io::CSVREADER<> is a class btw, room and classes are our custom objects

try{ //try catch combo to handle errors better
  // for roompool csv
  //csv reader that reads 5 columns cuz roompool csv has 5, trims spaces for values, and ' is the separator but " isnt cuz of building 
  io::CSVReader<5, io::trim_chars<' '>, io::double_quote_escape<',', '"'>> room(filename);  
  room.read_header(io::ignore_extra_column, "RoomID", "Capacity", "Building", "X", "Y");    //template from 
  int roomid;                                                                      //from the 
  int capacity;                                                                    //fast cpp csvparser
  std::string building;                                                                    //github
  int x;                                                                                                                      
  int y;
  
  //while reading, print:
  while(room.read_row(roomid, capacity, building, x, y)){
    std::cout << roomid << " , " << capacity << " , " << building << " , " << x << " , " << y << std::endl;
  }

  std::cout << "\n\n\n\n\n";
  // for class demand csv
  //simpler csv reader header cuz just integers in this csv
  io::CSVReader<5> classes(filename2);
  classes.read_header(io::ignore_extra_column, "ClassID", "Enrollment", "Days", "StartSlot", "Length");
  int classid;
  int enrollment;
  int days;
  int startslot;
  int length;
  
  //while reading, print:
  while(classes.read_row(classid, enrollment, days, startslot, length)){
    std::cout << classid << " , " << enrollment << " , " << days << " , " << startslot << " , " << length << std::endl;
  }


  //error report here:
} catch (const std::exception& err){
 std::cerr << "ERROR: " << err.what() << std::endl;
 return 1;
}

return 0; 

}
