#include "vector_strings.hpp"

#include <iostream>
#include <vector>



void Adder(std::vector<std::string>& names) {
    std::string name;
    
    //Asking user for name to add to vector
    std::cout << "Enter a name:" << std::endl;
    std::cin >> name;    

    //Adding user input to vector of names
    names.push_back(name);

    std::cout << "Number of names in the vector:\n" << names.size() << std::endl;
}

void Remover(std::vector<std::string>& names) {
    int last = names.size() - 1;
    std::cout << "Removing the last element:\n" << names[last] << std::endl;
    names.pop_back();
}


void Printer(std::vector<std::string>& names) {
    for (unsigned int i = 0; i < names.size(); i++) {
        std::cout << names[i] << std::endl;
    }
}



void CMDReader() {
    std::cout << "Commands: ADD, PRINT, REMOVE, QUIT" << std::endl;
    std::string com1 = "";
    std::vector<std::string> names; //empty vector to store names


    //Here we might need some error handling
    while (com1 != "QUIT") {
        std::cout << "Enter a command:" << std::endl;
        std::cin >> com1;


        //Different legal command cases
        if (com1 == "ADD") {
            Adder(names);

        } else if (com1 == "PRINT") {
            Printer(names);

        } else if (com1 == "REMOVE") {
            Remover(names);

        //This block is not really useful, 
        //however it allows handling of erroneous inputs in the next block.
        } else if (com1 == "QUIT") {
            break;

        //Illegal commands being used
        } else {
            std::cout <<  "Illegal command used!" << std::endl;
        }

    }
    
    //std::cout << "\nExiting program..." << std::endl;
    // Print the read command to the terminal

}

