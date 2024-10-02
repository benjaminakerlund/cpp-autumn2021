#ifndef AALTO_ELEC_CPP_DRAGON_CLASS
#define AALTO_ELEC_CPP_DRAGON_CLASS

#include "creature.hpp"

class Dragon : public Creature {
public:
    Dragon(std::string const& name, int hp);
};

#endif


