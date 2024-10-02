#include "dragon.hpp"
#include <string>
#include <list>
#include <iostream>
using namespace std;

Dragon::Dragon(const string& name, size_t age, size_t size)
    : name_(name), age_(age), size_(size) {
    }

const string& Dragon::GetName() const {
    return name_;
}

size_t Dragon::GetAge() const {
    return age_;
}

size_t Dragon::GetSize() const {
    return size_;
}

const list<Treasure>& Dragon::GetTreasures() const {
    return treasures_;
}

ostream& operator<<(ostream& os, const Dragon& d)
{
    os << "Dragon named: " << d.GetName() << ", age: " << d.GetAge() << ", size: " << d.GetSize() << endl;
    os << "Treasures:" << endl;
    for (const auto &iter : d.GetTreasures()) {
        os << iter.name << endl;
    }
    
    return os;
}
