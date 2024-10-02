#include "magic_dragon.hpp"
using namespace std;
// Define MagicDragon's methods here

MagicDragon::MagicDragon(const string& name, size_t age, size_t size)
    : Dragon(name,age,size) {
    }

void MagicDragon::Eat(list<Food>& f) {
    auto a = Herbs;
    if (f.size() != 0) {
         auto iter = f.begin();
         while (iter != f.end()) {
             Food fo = *iter;
             if (fo.type == a) {
                cout << "Magic dragon ate: " << fo.name << endl;
                size_ += 1;
                f.erase(iter);
             }
             iter++;
         }
     }
}
void MagicDragon::Hoard(list<Treasure>& t) {
    auto a = Potions;
    if (t.size() != 0) {
         auto iter = t.begin();
         while (iter != t.end()) {
             Treasure to = *iter;
             if (to.type == a) {
                cout << "Magic dragon received: " << to.name << endl;
                treasures_.push_back(to);
                t.erase(iter);
             }
             iter++;
         }
     }
}