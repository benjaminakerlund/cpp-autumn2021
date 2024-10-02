#include "magic_dragon.hpp"

// Define MagicDragon's methods here

MagicDragon::MagicDragon(const std::string& name, size_t age, size_t size) 
: Dragon(name, age, size) {
}

void MagicDragon::Eat(std::list<Food>& f) {
    if (f.size() != 0) {
        for (auto it = f.begin(); it != f.end(); it++) {
            Food fooditem = *it;
            if (fooditem.type == Herbs) {
                std::cout << "Magic dragon ate: " << fooditem.name << std::endl;
                size_ += 1;
                f.erase(it);
            }
        }
    }
}

void MagicDragon::Hoard(std::list<Treasure>& t) {
    if (t.size() != 0) {
        for (auto it = t.begin(); it != t.end(); it++) {
            Treasure treasitem = *it;
            if (treasitem.type == Potions) {
                std::cout << "Magic dragon received: " << treasitem.name << std::endl;
                treasures_.push_back(treasitem);
                t.erase(it);
            }
        }
    }
}