#include "list.hpp"
#include <iostream>
//my includes
#include <sstream>
#include <string>

// Implement the functions here

/** Read all lines from the stream into the list. Newline characters are not
 * stored in the list. Returns the stream. **/
std::istream& GetLines(std::istream& is, std::list<std::string>& list) {

    if (!list.empty()) { // Check if list is empty and clear if needed.
        std::cerr << "Error, passed list is not empty: " << std::endl;
        list.clear();
    }

    //Segment to view iostream (file) and read lines into list.
    //Utilizing the std::getline() function we save each line into the "line" string and then push into our list
    std::string line;
    while (std::getline(is, line)) {
        list.push_back(line);        
    }

    return is; //Returns the iostream.
}

/** Print the list, with a newline after each entry. **/
void Print(const std::list<std::string>& list) {
    //std::cout << "List size: " << list.size() << std::endl; //line used for debugging
    for (auto pt = list.begin(); pt != list.end(); pt++) {
        std::cout << *pt << std::endl;
    }

}

/** Sort the list and remove all duplicate entries. **/
void SortAndUnique(std::list<std::string>& list) {
    list.sort(); //Lol this feels too easy...
    list.unique(); //same here...
}
