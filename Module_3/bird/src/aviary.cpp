#include "aviary.hpp"



void Aviary::Add(Bird* bird) {
    if (bird == NULL) {
        throw std::logic_error("Error, the bird pointer is null.");
    }
    else {
        birds_.push_back(bird);

    }
}

void Aviary::SpeakAll(std::ostream& stream) const {
    int size = birds_.size();
    for (int it = 0; it < size ; it++) {
        birds_[it]->Speak(stream);
    }
}

size_t Aviary::Size() const {
    return birds_.size();
}

const Bird* Aviary::operator[](size_t size) const {
    /*if (index >= size) {
        cout << "Array index out of bound, exiting";
        exit(0);
    }
    return ptr[index];*/
    return birds_[size];
  
}

Bird* Aviary::operator[](size_t size) {
    /*if (index >= size) {
        cout << "Array index out of bound, exiting";
        exit(0);
    }
    return ptr[index];*/
    return birds_[size];
  
}

/* Destructor */
Aviary::~Aviary() {
    for (auto it : birds_) {
        std::cout << "Deleting " << it->GetName() << std::endl;
        delete it;
    }
}