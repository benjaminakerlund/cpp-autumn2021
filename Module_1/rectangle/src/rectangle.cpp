#include "rectangle.hpp"

#include <iostream>

// Write you function here and test it with the main.

void Rectangle() {
    double width;
    double height;
    std::cout << "Please enter width and height" << std::endl;
    std::cin >> width >> height;

    double area = width*height;
    double circ = 2*width + 2*height;

    std::cout << "Area: " << area << std::endl;
    std::cout << "Circumference: " << circ << std::endl; 

}

