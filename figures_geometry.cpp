#include "point_geometry.h"
#include "figures_geometry.h"
#include <tgmath.h>

long double triangle_oriented_square(point const& a, point const& b, point const& c) {
    return vector_product(b - a, c - a) / 2;
}

long double triangle_square(point const& a, point const& b, point const& c) {
    return fabsl(triangle_oriented_square(a, b, c));
}

long double polygon_square(std::vector <point> const& poly, point p) {
    long double res = 0;
    for (size_t i = 0; i + 1 < poly.size(); i++) {
        res += triangle_oriented_square(p, poly[i], poly[i + 1]);
    }
    res += triangle_oriented_square(p, poly[poly.size() - 1], poly[0]);
    return fabsl(res);
}

bool is_point_in_polygon(std::vector <point> const& poly, point const& p) {
    return equal(polygon_square(poly), polygon_square(poly, p));
}
