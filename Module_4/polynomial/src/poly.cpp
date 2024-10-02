#include "poly.hpp"

#include <sstream>

//own includes
#include <iostream>
//#include <iosfwd>
//#include <map>
#include <fstream>

int Poly::operator[](int exp) const {
    auto it = values_.find(exp);
    return it == values_.end() ? 0 : it->second;
}





// TODO: implement the following operators in poly.cpp
Poly& Poly::operator+=(const Poly& b) {
    for (auto it = b.values_.begin(); it != b.values_.end(); it++) {
        values_[it->first] += it->second;
    }
    return *this;
}
Poly& Poly::operator-=(const Poly& b) {
    for (auto it = b.values_.begin(); it != b.values_.end(); it++) {
            values_[it->first] -= it->second;
        }
    return *this;
}


// TODO: implement all of the following in poly.cpp
/* 
    * These operators are declared in the .hpp file outside of the class definition. 
    * Therefore they don't have the Polly:: prefix before operator...
*/
std::istream& operator>>(std::istream& is, Poly& p) {
    std::string a;
    std::string b;
    char c;
    while( ! is.eof()) {
        std::getline(is, a, 'x');
        while( is.peek() != EOF && is.peek() != '+' && is.peek() != '-') {
            is.get(c);
            b += c;
        }
        p[stoi(b)] = stoi(a); //converting to integer
        b = "";
    }
    return is;
}
std::ostream& operator<<(std::ostream& os, const Poly& p) {
    for (auto it = p.rbegin(); it != p.rend();) {
            if (it->second != 0) {
                os << it->second << "x" << it->first;
            }
            it++;
            if (it != p.rend() ) {
                if (it->second > 0) {
                    os << "+";
                }
            }
        }
    return os;
}

Poly operator+(const Poly& a, const Poly& b) {
    return Poly (a) += b;
}
Poly operator-(const Poly& a, const Poly& b) {
    return Poly (a) -= b;
}
Poly operator-(const Poly& p) {
    Poly po;
    for (auto it = p.cbegin(); it != p.cend(); it++) {
        po[it->first] = -(it->second);
    }
    return po;
}

bool operator<(const Poly& a, const Poly& b) {
    int ab = 0;
    int ba = 0;
    if (a.cbegin() == a.cend() && b.cbegin() == b.cend()) {
        return true;
    }
    else if (a.cbegin() != a.cend() && b.cbegin() == b.cend()) {
        return false;
    }
    for (auto it = a.cbegin(); it != a.cend(); it++ ) {
        ab++;
    }
    for (auto it = b.cbegin(); it != b.cend(); it++ ) {
        ba++;
    }
    return ab < ba;
}
bool operator==(const Poly& a, const Poly& b) {
    if ( ! (a<b) && ! (b<a) ) {
        return true;
    }
    return false;
}
bool operator>(const Poly& a, const Poly& b) {
    return (b<a);
}
bool operator!=(const Poly& a, const Poly& b) {
    return ! (a==b);
}