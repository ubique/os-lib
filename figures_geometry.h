#ifndef OS_FIND_FIGURES_GEOMETRY_H
#include "point_geometry.h"
#include <vector>

long double triangle_square(point const& a, point const& b, point const& c);


long double triangle_oriented_square(point const& a, point const& b, point const& c);


long double polygon_square(std::vector <point> const& poly, point p = point(0, 0));

bool is_point_in_polygon(std::vector <point> const& poly, point const& p);

#define OS_FIND_FIGURES_GEOMETRY_H

#endif //OS_FIND_FIGURES_GEOMETRY_H
