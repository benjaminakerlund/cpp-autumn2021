#include "to_string.hpp"
#include <iostream>
#include <set>

int main() {
    std::string s = "foobar";
    std::cout << "ToString(s) = " << ToString<std::string>(s) << std::endl;
    std::cout << "ToString(s.begin(), s.end()) = " << ToString(s.begin(), s.end()) << std::endl;
    std::set<double> v;
    v.insert(1.23);
    v.insert(4.56);
    v.insert(7.89);
    std::cout << "ToString(v) = " << ToString(v) << std::endl;
    std::cout << "ToString(v.begin(), v.end()) = " << ToString(v.begin(), v.end()) << std::endl;

    //own
    std::string a = "dg[PNK:gB>;`8kLlS^iZ=Xr:G";
    std::cout << "ToString(a) = " << ToString(a) << std::endl;

    std::string s2 = "foobar";
    std::cout << "ToString(s2) = " << ToString(s2) << std::endl;
 
}

