 #include <string>
 #include <iostream>
 
 class Car {
 public:
     Car(const std::string& registration_number); // construct a brand new car
     void Drive(double distance);
 
     /* 'const' that follows the function definition tells that the
    function is not going to modify the state of the object (i.e.
    its member variables) */
    const std::string& GetRegistrationNumber() const;
    double GetDistance() const;

private:
    std::string registration_number_;
    double distance_;  // distance the car has travelled
};

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




int main() {

    Car toyota("ABC-313");  // invoke constructor to build a car
    Car mazda("XXX-666");

    toyota.Drive(10.5);  // drive a bit
    toyota.Drive(4.1);  // drive some more
    mazda.Drive(2.4);

    std::cout << toyota.GetRegistrationNumber() << " has driven "
        << toyota.GetDistance() << " km" << std::endl;
    std::cout << mazda.GetRegistrationNumber() << " has driven "
        << mazda.GetDistance() << " km" << std::endl;

    return 0;
}