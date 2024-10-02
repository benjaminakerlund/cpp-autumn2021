#include <string>
 
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