#include "geomvector.hpp"

// Implement operators here


GeomVector GeomVector::operator+(const GeomVector& a) {
    return GeomVector(a.x_ + x_, a.y_ + y_, a.z_ + z_);
}

GeomVector operator*(double a, const GeomVector& b) {
    return GeomVector(a * b.x_, a * b.y_, a * b.z_);
}

std::ostream &operator<<(std::ostream& out, const GeomVector& a) {
    out << "(" << a.x_ << ", " << a.y_ << ", " << a.z_ << ")";
    return out;
}

double GeomVector::Length() const {
    return sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2));
}

//Own implementations
GeomVector operator/(const GeomVector& a, double b) {
    return GeomVector(a.x_ / b, a.y_ / b, a.z_ / b);
}


bool GeomVector::operator>(const GeomVector& a) {
    if (this->Length() > a.Length()){
        return true;
    }
    else { return false; }
}

bool GeomVector::operator<(const GeomVector& a) {
    if (this->Length() > a.Length()){
        return false;
    }
    else { return true; }
}

bool GeomVector::operator==(const GeomVector& a) {
    if (this->x_ == a.x_ && this->y_ == a.y_ && this->z_ == a.z_) {
        return true;
    }
    else { return false; }
}
bool GeomVector::operator!=(const GeomVector& a) {
    if (this->x_ == a.x_ && this->y_ == a.y_ && this->z_ == a.z_) {
        return false;
    }
    else { return true; }
}