#include "register.hpp"

//TODO: implement Register's members
#include "boat.hpp"
#include "aircraft.hpp"
#include "vehicle.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>





//Destructor
Register::~Register() {
    for (auto it : vehicles_) {
        delete it;
    }
}

/* Add
    * Adds the parameter to the vehicle vector
*/
void Register::Add(Vehicle* v){
    vehicles_.push_back(v);
}

/* Save
    * Saves the vehicles to the file named by the parameter with each vehicle on its
    * own line in the serialized format.
*/
void Register::Save(const std::string& filename) const{
    /* The idea here:
        * Open up a file stream based on the file name (create new file!)
        * Iterate through the vehicles_ vector
        * Call on each objects (vehicle, boat or aircraft) read() method
        * Call on each objects Write method
        * go on to the next object
        * 
        * Maybe each objects Write() method can internally call Save()
    */
    std::ofstream out(filename);
    for (auto it : vehicles_) {
        it->Write(out);
    }
}

/* ReadLine
    * Reads a vehicle from the stream given as a parameter assuming a seralized format, and 
    * adds it to the register. Reads a whole line from the stream whether or not constructing 
    * the vehicle was succesful.
    * Returns true if a vehicle was added, false otherwise.
std::istringstream iss("2 3 4 1 3.65 1 0.1 0 2.0");
*/
bool Register::ReadLine(std::istream& stream){
    std::string line;
    std::string delimiter = ";";

    std::getline(stream, line);
    std::string Vtype = line.substr(0, line.find(delimiter));
    std::string rest = line.substr(line.find(delimiter) +1, line.size()); //move away from delim
    
    std::string Register = rest.substr(0, rest.find(delimiter)); //Common for both Vehicle types
    rest = rest.substr(rest.find(delimiter) +1, rest.size()); 
    std::string Owner = rest.substr(0, rest.find(delimiter)); //Common for both Vehicle types
    rest = rest.substr(rest.find(delimiter) +1, rest.size()); 

    std::string Field1 = rest.substr(0, rest.find(delimiter)); //name or model
    rest = rest.substr(rest.find(delimiter) +1, rest.size()); 

    std::string Field2 = rest.substr(0, rest.find(delimiter)); //draft or wingspan
    rest = rest.substr(rest.find(delimiter) +1, rest.size()); 

    std::string Field3 = rest.substr(0, rest.find(delimiter)); //power or cruise speed

    if (Vtype == "A") {
        /* String Manipulations:
            * stod --> double
            * stoul --> unsigned int
            * 
        */
        Add(new Aircraft(Register, Owner, Field1, stod(Field2), stoul(Field3)));
        return true;
    }

    else if (Vtype == "B") {
        Add(new Boat(Register, Owner, Field1, stod(Field2), stod(Field3)));
        return true;
    }
    return false;
}

/* Load
    * Reads all vehicles from a file and adds them to the register.
    * Each vehicle is on a different line. On an error the line is discarded and reading is
    * continued from the next line.
    * Returns the number of vehicles added.
    * If file opening fails, the return value should be -1.
*/
int Register::Load(const std::string& filename){
    int counter = 0;
    std::ifstream istr(filename);
    if (istr.rdstate() && (istr.failbit || istr.badbit)) {
        return -1;
    }
    else {
        while (!istr.eof()) {
            if(ReadLine(istr)) {
                counter += 1;
            }
        }
    }
    return counter;
}

/* Print
    * Prints all the vehicles in the register to the standard output each on a different line
    * in the serialized format.
*/
void Register::Print() { 
    //First we will need to overload the << operator in the Vehicle files? NOOO
    //std::cout << "Inside the register::Print method, trying to print each vehicle in vehicles_ vector." << std::endl;
    for ( auto it : vehicles_) {
        it->Print();
    }
    //std::cout << std::endl;
}


/* Size
    * Returns the number of vehicles in the register.
*/
size_t Register::Size() const{
    return vehicles_.size();
}


