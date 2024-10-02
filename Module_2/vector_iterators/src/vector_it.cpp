#include <iostream>
#include <vector>
#include "vector_it.hpp"
// Implement the functions here
/*ReadVector:  std::vector<int> ReadVector();
that will read numbers from user and stores them as integer 
vector that is returned by the function. 
The function stops reading when a non-numeric value is given 
by the user.*/
std::vector<int> ReadVector(){
    std::vector<int> numbers;
    //const char newline = '\n' ;
    int input ;
    std::cout << "Please enter each integer to add to vector (or just enter to quit): " ;
    while( std::cin && std::cin >> input )
    {
        numbers.push_back(input);
        //std::cin.ignore( 1000000, '\n' ) ; // ignore the newline followin the entered integer
        std::cout << "Please enter another integer (or just enter to quit): " ;
    }
    /*while (std::cin >> input) {
        numbers.push_back(input);
        std::cout << "Please enter another integer (or just enter to quit): " ;
    }*/
    return numbers;
}
/* PrintSum1() caculates the sums of pairs of numbers in the vector and prints them.
Eg. input = 1, 2, 3, 4 and output = 3, 5, 7
The input vector is not to be modified...*/
void PrintSum1(const std::vector<int>& input){
    std::vector<int> temp = input; //Vector that we can modify
    std::vector<int> numbers2;
    int sum = 0;
    int first = temp.at(0);
    int second;
    for (std::vector<int>::const_iterator it = temp.begin(); it != temp.end(); it++) {
        if (*it == first) {
            continue;
        }
        second = *it;
        sum = first + second;
        numbers2.push_back(sum);
        first = second;
    }
    // Finally printing out the sums stored in the result vector.
    for (std::vector<int>::const_iterator it = numbers2.begin(); it != numbers2.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
void PrintSum2(const std::vector<int>& input){
    std::vector<int> temp = input; //Vector that we can modify
    
    int first = temp.at(0);
    int size = temp.size();
    int last = temp.at(size - 1);
    for (int i = 0; i < size / 2 ; i++) {
        first = temp.at(i);
        last = temp.at(size - 1 - i);
        std::cout << first + last << " "; 
    }
    std::cout << std::endl;
}