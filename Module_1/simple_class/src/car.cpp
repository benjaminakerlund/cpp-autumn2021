#include "car.hpp"
 
 Car::Car(const std::string& registration_number)
         : registration_number_(registration_number), distance_(0) {
 }
 
 void Car::Drive(double distance) {
     distance_ += distance;
 }

const std::string& Car::GetRegistrationNumber() const {
    return registration_number_;
}

double Car::GetDistance() const {
    return distance_;
}