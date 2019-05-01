#include <iostream>
#include <iomanip>
#include <dlfcn.h>

#include "intersections.h"
#include "point_geometry.h"
#include "figures_geometry.h"

using namespace std;

void* get_function_ptr(void* library, const char* name) {
    void* ptr = dlsym(library, name);
    if (!ptr) {
        cerr << "Could not provide pointer for function " << name << ": " << dlerror() << '\n';
        return nullptr;
    }
    return ptr;
}

const char* MANGLED_FUNCTION_NAME = "_Z22get_intersection_pointRK5pointS1_S1_S1_";

int main() {
    int precision;
    cout << "This is a sample executable presenting basic geometry static/dynamic libraries\n";
    cout << "Enter geometry precision (number of digits after the comma):\n";
    cin >> precision;
    set_geometry_precision(precision);
    cout << fixed << setprecision(point::precision);
    //Static lib
    cout << "Enter two vectors [x1, y1, x2, y2]:\n";
    point a, b;
    cin >> a >> b;
    cout << "sum: " << a + b << '\n';
    cout << "subtract: " << a - b << '\n';
    cout << "length: " << a.len() << ' ' << b.len() << '\n';
    //Dynamic lib
    cout << "Enter three vertexes of a triangle:\n";
    point c, p;
    cin >> a >> b >> c;
    cout << "Enter one more point:\n";
    cin >> p;
    cout << "Square of the triangle is " << triangle_square(a, b, c) << '\n';
    (is_point_in_polygon({a, b, c}, p)) ? cout << "Point is in the triangle\n" : cout << "Point is not in the triangle\n";
    //Dynamic lib loading in runtime

    void *libintersections = dlopen("libintersections.so", RTLD_LAZY | RTLD_GLOBAL);
    if (!libintersections) {
        cerr << "Couldn't open libintersections.so: " << dlerror() << '\n';
        return 0;
    }
    pair <bool, point> (*get_intersection_point)(point const&, point const&, point const&, point const&);
    *(void **) (&get_intersection_point) = get_function_ptr(libintersections, MANGLED_FUNCTION_NAME);

    if (get_intersection_point) {
        cout << "Enter two R^2 segments [x1 y1 x2 y2 x3 y3 x4 y4]:\n";
        point d;
        cin >> a >> b >> c >> d;
        auto i = get_intersection_point(a, b, c, d);
        if (i.first) {
            cout << "Segments intersection point is " << i.second << '\n';
        } else {
            cout << "Segments have zero or more than one common points\n";
        }
    }
    return 0;
}