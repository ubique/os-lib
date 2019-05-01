#ifndef OS_FIND_INTERSECTIONS_H
#define OS_FIND_INTERSECTIONS_H
#include "point_geometry.h"

bool intersects(point const& a, point const& b, point const& c, point const& d);

std::pair<bool, point> get_intersection_point(point const& a, point const& b, point const& c, point const& d);
#endif //OS_FIND_INTERSECTIONS_H
