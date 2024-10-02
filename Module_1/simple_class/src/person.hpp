#ifndef AALTO_ELEC_CPP_PERSON
#define AALTO_ELEC_CPP_PERSON
#include <string>

// define your Person class here
class Person {
public:
    Person(std::string name, int birthyear); //Constructor for class Person

    std::string& GetName();

    int GetAge(int year);

private:
    std::string name_;
    int birthyear_;
};

#endif