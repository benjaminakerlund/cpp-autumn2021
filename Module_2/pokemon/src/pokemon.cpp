#include "pokemon.hpp"
#include <iostream>


bool srtbyid(std::pair <std::string, size_t> &a, std::pair <std::string, size_t> &b){
    return (a.second < b.second);
}

PokemonCollection::PokemonCollection(PokemonCollection collection, PokemonCollection collection2){
    collection.pokemons_.list::merge(collection2.pokemons_);
    collection.pokemons_.list::sort(); //c++ built in algo
    collection.pokemons_.list::unique(); //c++ build in algo for removing duplicates

    pokemons_ = collection.pokemons_;
}

void PokemonCollection::Add(const std::string& name, size_t id){
    std::pair<std::string, size_t> pair;
    pair.first = name;
    pair.second = id;

    pokemons_.push_back(pair);
}

bool PokemonCollection::Remove(const std::string& name, size_t id){
    std::pair<std::string, size_t> pair;
    pair.first = name;
    pair.second = id;

    int oldSize = pokemons_.size();

    pokemons_.remove(pair);
    int newSize = pokemons_.size(); //Get size after removal of pair
    
    if(oldSize == newSize){ //comparison
        return false;
    }
    else{
        return true;
    }
}

void PokemonCollection::Print() const{    
     /*for (auto it = pokemons_.begin(); it != pokemons_.end(); it++) {
        std::cout << "id: " << it.second << ", name: " << it.first << std::endl;
    }*/
    for (auto it : pokemons_) {
        std::cout << "id: " << it.second << ", name: " << it.first << std::endl;
    }
}
   

void PokemonCollection::SortByName(){
    pokemons_.list::sort(); //Utilize the already existing c++ algo
}

void PokemonCollection::SortById(){
    pokemons_.list::sort(srtbyid); //again c++ algo
}
