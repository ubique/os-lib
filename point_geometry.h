#ifndef OS_FIND_POINT_GEOMETRY_H
#define OS_FIND_POINT_GEOMETRY_H
#include <iostream>
struct point {
    static long double eps;
    static int precision;
    long double x, y;
    point() : x(0), y(0) {}
    point(long double const& xx, long double const& yy) : x(xx), y(yy) {}
    point(point const& other) = default;
    point& operator = (point const& other) = default;
    ~point() = default;
    point operator + (point const& other) const;
    point operator - (point const& other) const;
    point operator * (long double const& k) const;
    point operator / (long double const& k) const;
    long double scalar_product(point const& other) const;
    long double vector_product(point const& other) const;
    long double len() const;
};

long double scalar_product(point const& a, point const& b);
long double vector_product(point const& a, point const& b);

std::istream& operator >> (std::istream& in, point & p);
std::ostream& operator << (std::ostream& out, point const& p);

bool less(long double const& a, long double const& b);
bool equal(long double const& a, long double const& b);
bool greater(long double const& a, long double const& b);

void set_geometry_precision(int p);
#endif //OS_FIND_POINT_GEOMETRY_H
