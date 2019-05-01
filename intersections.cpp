#include "intersections.h"
#include "point_geometry.h"

int sign(long double x) {
    if (greater(x, 0)) return 1;
    if (less(x, 0)) return -1;
    return 0;
}

bool intersects(point const& a, point const& b, point const& c, point const& d) {
    bool l = sign(vector_product(b - a, c - a)) * sign(vector_product(b - a, d - a)) <= 0;
    bool r = sign(vector_product(d - c, a - c)) * sign(vector_product(d - c, b - c)) <= 0;
    return (l && r);
}

std::pair<bool, point> get_intersection_point(point const& A, point const& p, point const& B, point const& q) {
    if (!intersects(A, p, B, q)) {
        return {false, point(0, 0)};
    } else {
        point a = p - A;
        point b = q - B;
        if (equal(vector_product(a, b), 0)) {
            return {false, point(0, 0)};
        }
        long double k = (vector_product(B, b) - vector_product(A, b)) / vector_product(a, b);
        return {true, A + a * k};
    }
}
