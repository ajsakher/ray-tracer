#include <cmath>

#include <ray-tracer/spatial/Matrix.hpp>
#include <ray-tracer/spatial/Transform.hpp>

namespace RayTracer {
namespace Spatial {

Matrix translate(double x, double y, double z) {
    return Matrix({
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1},
    });
}

Matrix scale(double x, double y, double z) {
    return Matrix({
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1},
    });
}

Matrix rotate_x(double radians) {
    return Matrix({
        {1, 0, 0, 0},
        {0, std::cos(radians), -std::sin(radians), 0},
        {0, std::sin(radians), std::cos(radians), 0},
        {0, 0, 0, 1},
    });
}

Matrix rotate_y(double radians) {
    return Matrix({
        {std::cos(radians), 0, std::sin(radians), 0},
        {0, 1, 0, 0},
        {-std::sin(radians), 0, std::cos(radians), 0},
        {0, 0, 0, 1},
    });
}

Matrix rotate_z(double radians) {
    return Matrix({
        {std::cos(radians), -std::sin(radians), 0, 0},
        {std::sin(radians), std::cos(radians), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    });
}

Matrix shear(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y) {
    return Matrix({
        { 1, x_y, x_z, 0},
        { y_x, 1, y_z, 0},
        { z_x, z_y, 1, 0},
        { 0, 0, 0, 1}
    });
}

}
}
