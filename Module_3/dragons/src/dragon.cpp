#include "dragon.hpp"

/* Constructor implemented in .cpp*/
Dragon::Dragon(const std::string& name, size_t age, size_t size) 
    : name_(name), age_(age), size_(size) { 
    }


/* Member functions */ 
const std::string& Dragon::GetName() const {
    return name_;
}

size_t Dragon::GetAge() const {
    return age_;
}

size_t Dragon::GetSize() const {
    return size_;
}

const std::list<Treasure> Dragon::GetTreasures() const {
    return treasures_;
}

/* Virtual functions not implemented*/

/* Operator overload << */
std::ostream& operator<<(std::ostream& os, const Dragon& drake) {
    os << "Dragon named: " << drake.GetName() << ", age: " << drake.GetAge() << ", size: " << drake.GetSize() 
    << std::endl << "Treasures:" << std::endl;
    for (const auto &it : drake.GetTreasures()) {
        os << it.name << std::endl;
    }
    return os;
}

