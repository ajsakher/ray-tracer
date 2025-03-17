#pragma once

#include <ray-tracer/display/Color.hpp>

namespace RayTracer {
namespace Display {

struct Material {
    Color color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
    Material() :
        color(Color(1.0, 1.0, 1.0)),
        ambient(0.1),
        diffuse(0.9),
        specular(0.9),
        shininess(200.) {}
};

} // namespace Display
} // namespace RayTracer
