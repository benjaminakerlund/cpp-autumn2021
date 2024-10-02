#include "aircraft.hpp"
//TODO: implement Aircraft's members
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


/* constructor
    * Initializes the corresponing members from the parameters.
*/
Aircraft::Aircraft(std::string register_number, 
    std::string owner, 
    std::string model, 
    double wingspan, 
    unsigned int cruise_speed) 

    : Vehicle(register_number, owner) {
        model_ = model;
        wingspan_ = wingspan;
        cruise_speed_ = cruise_speed;
    }



/* Write
    * Writes the vehicle to the stream given as a parameter in the serialized format.
    * Format for AirCraft:
A;<register number>;<owner>;<model>;<wingspan>;<cruise_speed>\n
*/
void Aircraft::Write(std::ostream& stream) {
    stream << "A;" << GetRegisterNumber() << ";" << GetOwner();
    stream << ";" << model_ << ";" << wingspan_ << ";" << cruise_speed_ << std::endl;
}

/* Print
    * Writes the vehicle to the standard output in the serialized format (See Write).
*/
void Aircraft::Print() {
    std::cout << "A;" << GetRegisterNumber() << ";" << GetOwner() << ";";
    std::cout << model_ << ";" << wingspan_ << ";" << cruise_speed_ << std::endl;
}

/* Read
    * Reads an Aircraft from the stream given as parameter, assuming that the vehicle
    * is stored in the serialized format (See Write) and starts immediately from 
    * the current position of the stream.
    * If the vehicle type (the first character) is wrong, returns NULL.
    * If the read was succesful, returns a pointer to a new Aircraft contructed with 
    * the data read. 
*/
Aircraft* Aircraft::Read(std::istream& stream) {
    /*The smart way to do all of this would have been to call on this method in the 
    ReadLine() of register.cpp. This is very annoying to finally understand when the 
    assignment is actually done... Since this method is unused for the most part of this program....*/
    std::string line;
    std::getline(stream, line);
    std::stringstream ss(line);
    std::vector<std::string> vec;

    while(ss.good()) {
        std::string str;
        std::getline(ss, str, ';');
        vec.push_back(str);
    }
    if (vec[0] != "A") {
        return NULL;
    }
    return new Aircraft(vec[1], vec[2], vec[3], std::stod(vec[4]), std::stoul(vec[5]));
}


