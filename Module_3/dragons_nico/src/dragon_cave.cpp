#include "dragon_cave.hpp"

// Define DragonCave's methods here
const list<Dragon*> DragonCave::GetDragons() const {
    return dragons_;
}

void DragonCave::Accommodate(Dragon *dragon) {
    dragons_.push_back(dragon);
}

void DragonCave::Evict(const string& name) {
     if (dragons_.size() != 0) {
         auto iter = dragons_.begin();
         while (iter != dragons_.end()) {
             Dragon* b = *iter;
             if (b->GetName() == name) {
                 iter = dragons_.erase(iter);
                 iter--;
             }
             iter++;
         }
     }
}

ostream& operator<<(ostream& os, const DragonCave& d)
{
    os << "DragonCave dwellers:" << endl;
    for (const auto &iter : d.GetDragons()) {
        os << endl;
        os << *iter;
    }
    return os;
}