#include <iostream>
#include <vector>

#include "vector.hpp"


int main(void) {
    std::cout << "Please enter the integer values. When you are finished, write something else." << std::endl;

    int i;
    std::vector<int> v;
    while (std::cin >> i)
        v.push_back(i);

    std::cout << "min: " << GetMin(v) << " max: " << GetMax(v) << " avg: " << GetAvg(v) << std::endl;

    return 0;
}


/*
#include <string>

int main(void) {
    std::string s1 = "Hello";
    std::string s2;
    std::string s3;

    s2 = "World";
    s3 = s1 + " " + s2;
    std::cout << s3 << std::endl;

    return 0;
}


#include <vector>
#include <iostream>

int main(void) {
    std::vector<int> numbers;

    numbers.push_back(5);
    numbers.push_back(7);

    std::cout << "Size: " << numbers.size() << std::endl;
    std::cout << numbers[0] << numbers[1] << std::endl;

    return 0;
}
*/
