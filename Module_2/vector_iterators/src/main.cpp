#include <iostream>
#include "vector_it.hpp"

int main(void) {
    
    std::cout << "Hello World! \n";
    
    auto v = ReadVector();
    
    PrintSum1(v);
    PrintSum2(v);
    return 0;


}
