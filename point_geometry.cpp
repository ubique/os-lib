#include <tgmath.h>
#include "point_geometry.h"

int point::precision = 0;
long double point::eps = 1;

point point::operator+(point const &other) const {
    return point(x + other.x, y + other.y);
}

point point::operator-(point const &other) const {
    return point(x - other.x, y - other.y);
}

point point::operator*(long double const &k) const {
    return point(x * k, y * k);
}

point point::operator/(long double const &k) const {
    return point(x / k, y / k);
}

long double point::scalar_product(point const &other) const {
    return x * other.x + y * other.y;
}

long double point::vector_product(point const &other) const {
    return x * other.y - y * other.x;
}

long double scalar_product(point const& a, point const& b) {
    return a.scalar_product(b);
}
long double vector_product(point const& a, point const& b) {
    return a.vector_product(b);
}

long double point::len() const {
    return sqrtl(x * x + y * y);
}

std::istream& operator >> (std::istream& in, point & p) {
    return (in >> p.x >> p.y);
}

std::ostream& operator << (std::ostream& out, point const& p) {
    return (out << p.x << ' ' << p.y);
}

bool less(long double const& a, long double const& b) {
    return (b - a > point::eps);
}
bool greater(long double const& a, long double const& b) {
    return (a - b > point::eps);
}
bool equal(long double const& a, long double const& b) {
    return !less(a, b) && !greater(a, b);
}

void set_geometry_precision(int p) {
    point::precision = p;
    point::eps = pow(10, -p);
}
//
// Created by qrort on 4/30/19.
//

