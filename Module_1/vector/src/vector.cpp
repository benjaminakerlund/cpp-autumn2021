#include "vector.hpp"
#include "iostream"

#include <vector>

int GetMin(std::vector<int> v) {
    //std::cout << "Inside GetMin function!" << std::endl;
    int smallest = v[0];
    for (unsigned int a = 0; a < v.size(); a++) {
        if (v[a] < smallest) {
            smallest = v[a];
        }
    }
    //std::cout << "Smallest element of vector: " << smallest << std::endl;
    return smallest; 
}

int GetMax(std::vector<int> v) {
    int largest = v[0];
    for (unsigned int a = 0; a < v.size(); a++) {
        if (v[a] > largest) {
            largest = v[a];
        }
    }

    return largest; 
}

double GetAvg(std::vector<int> v) {
    double sum = 0;
    int counter = 0;
    for (unsigned int a = 0; a < v.size(); a++) {
        sum += v[a];
        counter += 1;
    }

    double average = sum / counter;

    //std::cout << "The sum of all vector elements is: " <<  sum << std::endl;
    //std::cout << "The amount of elements is: " << counter << ".\n And the average is: " << average << std::endl;
    return average; 
}
