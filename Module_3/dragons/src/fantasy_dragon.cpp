#include "fantasy_dragon.hpp"

// Define FantasyDragon's methods here

FantasyDragon::FantasyDragon(const std::string& name, size_t age, size_t size) 
: Dragon(name, age, size) {
}

void FantasyDragon::Eat(std::list<Food>& f) {
    if (f.size() != 0) {
        for (auto it = f.begin(); it != f.end(); it++) {
            Food fooditem = *it;
            if (fooditem.type == People || fooditem.type == PeopleFood) {
                std::cout << "Fantasy dragon ate: " << fooditem.name << std::endl;
                size_ += 1;
                f.erase(it);
            }
        }
    }
}

void FantasyDragon::Hoard(std::list<Treasure>& t) {
    if (t.size() != 0) {
        for (auto it = t.begin(); it != t.end(); it++) {
            Treasure treasitem = *it;
            if (treasitem.type == Jewellery) {
                std::cout << "Fantasy dragon received: " << treasitem.name << std::endl;
                treasures_.push_back(treasitem);
                t.erase(it);
            }
        }
    }
}