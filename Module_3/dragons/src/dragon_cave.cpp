#include "dragon_cave.hpp"

// Define DragonCave's methods here
/* Destructor */
DragonCave::~DragonCave() { 
    for (auto it : dragons_) {
        std::cout << "Deleting: " << it->GetName() << std::endl;
        delete it;
    }
}



/* Member functions */
const std::list<Dragon*> DragonCave::GetDragons() const {
    return dragons_;
}

void DragonCave::Accommodate(Dragon* drake) {
    dragons_.push_back(drake);
}

void DragonCave::Evict(const std::string& name) {
    if (dragons_.size() != 0) {
        for (auto it = dragons_.begin(); it != dragons_.end(); it++) {
            Dragon* b = *it;
            if (b->GetName() == name) {
                it = dragons_.erase(it);
                it--;
            }
        }
    }
}

/* Overloaded << operator */
 std::ostream& operator<<(std::ostream& os, const DragonCave& d) {
     os << "DragonCave dwellers:" << std::endl;
     for (const auto &it : d.GetDragons()) {
         os << std::endl << *it;
     }
     return os;
 }
