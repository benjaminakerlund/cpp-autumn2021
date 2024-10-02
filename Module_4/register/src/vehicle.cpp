#include "vehicle.hpp"
//TODO: implement Vehicle's members


/* constructor
    * Initializes the corresponing members from the parameters.
*/
Vehicle::Vehicle(std::string register_number, std::string owner) : 
    register_number_(register_number), owner_(owner) {}

//Already constructed in the header file?
//Vehicle::~Vehicle() {};

/* GetRegisterNumber
    * Returns the register number.
*/
std::string Vehicle::GetRegisterNumber() const{
    return register_number_;
}

/* GetOwner
    * Returns the owner.
*/
std::string Vehicle::GetOwner() const{
    return owner_;
}

