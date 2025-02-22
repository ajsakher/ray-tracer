#pragma once

#include <stdexcept>
#include <type_traits>
#include <vector>

#include <ray-tracer/spatial/Matrix.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {
namespace Spatial {

Matrix translate(double, double, double);
Matrix scale(double, double, double);
Matrix rotate_x(double);
Matrix rotate_y(double);
Matrix rotate_z(double);
Matrix shear(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);

}
}
