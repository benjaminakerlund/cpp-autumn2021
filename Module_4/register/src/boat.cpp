#include "boat.hpp"
//TODO: implement Boat's members
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
/* constructor
    * Initializes the corresponing members from the parameters.
*/
Boat::Boat(std::string register_number, 
    std::string owner, 
    std::string name, 
    double draft, 
    double power)

    : Vehicle(register_number, owner) {
        name_ = name;
        draft_ = draft;
        power_ = power;
    }


/* Write
    * Writes the vehicle to the stream given as a parameter in the serialized format.
    * Format for Boat:
B;<register number>;<owner>;<name>;<draft>;<power>\n
*/
void Boat::Write(std::ostream& stream) {
    stream << "B;" << GetRegisterNumber() << ";" << GetOwner();
    stream << ";" << name_ << ";" << draft_ << ";" << power_ << std::endl;
}

/* Print
    * Writes the vehicle to the standard output in the serialized format (See Write).
*/
void Boat::Print() {
    std::cout << "B;" << GetRegisterNumber() << ";" << GetOwner();
    std::cout << ";" << name_ << ";" << draft_ << ";" << power_ << std::endl;
}

/* Read
    * Reads a Boat from the stream given as parameter, assuming that the vehicle
    * is stored in the serialized format (See Write) and starts immediately from 
    * the current position of the stream.
    * If the vehicle type (the first character) is wrong, returns NULL.
    * If the read was succesful, returns a pointer to a new Boat contructed with 
    * the data read. 
*/
Boat* Boat::Read(std::istream& stream) {
    std::string line;
    std::getline(stream, line);
    std::stringstream ss(line);
    std::vector<std::string> vec;

    while(ss.good()) {
        std::string str;
        std::getline(ss, str, ';');
        vec.push_back(str);
    }
    if (vec[0] != "B") {
        return NULL;
    }
    return new Boat(vec[1], vec[2], vec[3], std::stod(vec[4]), std::stod(vec[5]));
}




