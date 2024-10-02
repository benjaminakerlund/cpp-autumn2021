#include "person.hpp"

// define your Person class' functions here
Person::Person(std::string name, int birthyear){
    name_ = name;
    birthyear_ = birthyear;
}


std::string& Person::GetName(){
    return name_;
}

int Person::GetAge(int year) {
    int age = year - birthyear_;
    return age;
}

