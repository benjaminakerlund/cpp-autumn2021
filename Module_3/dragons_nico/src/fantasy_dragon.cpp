#include "fantasy_dragon.hpp"

// Define FantasyDragon's methods here

using namespace std;

FantasyDragon::FantasyDragon(const string& name, size_t age, size_t size)
    : Dragon(name,age,size) {
    }

void FantasyDragon::Eat(list<Food>& f) {
    auto a = People;
    auto b = PeopleFood;
    if (f.size() != 0) {
         auto iter = f.begin();
         while (iter != f.end()) {
             Food fo = *iter;
             if (fo.type == a || fo.type == b) {
                cout << "Fantasy dragon ate: " << fo.name << endl;
                size_ += 1;
                f.erase(iter);
             }
             iter++;
         }
     }
}



void FantasyDragon::Hoard(list<Treasure>& t) {
    auto a = Jewellery;
    if (t.size() != 0) {
         auto iter = t.begin();
         while (iter != t.end()) {
             Treasure to = *iter;
             if (to.type == a) {
                cout << "Fantasy dragon received: " << to.name << endl;
                treasures_.push_back(to);
                t.erase(iter);
             }
             iter++;
         }
     }
}